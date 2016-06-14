#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "GridTile.h"
#include "Player.h"
#include "Enemy.h"
#include "ProjectileSystem.h"
#include "EnemySystem.h"
#include "ParticleSystem.h"


extern const int SCREEN_WIDTH = 1280;
extern const int SCREEN_HEIGHT = 720;

extern int shakeIntensity = 0;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int OffsetX = 0;
int OffsetY = 0;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL initialization failed!");
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("METROSCOPE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		int imgFlags = IMG_INIT_PNG;

		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}


	}

	return success;
}

bool loadMedia()
{
	bool success = true;



	return success;
}

void close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {

	init();
	loadMedia();

	ProjectileSystem ps(gRenderer);
	EnemySystem es;
	ParticleSystem pas;

	es.SpawnEnemy(gRenderer);

	GridTile grid(gRenderer);


	bool quit = false;
	SDL_Event e;

	Player player(gRenderer);

	SDL_ShowCursor(SDL_DISABLE);

	while (!quit)
	{
		//~~~~~~~~~~~~~logic step~~~~~~~~~~~~~~~~~~~~
		
		player.GetMousePosition(OffsetX, OffsetY);

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			player.readInput(e, ps, gRenderer);
		}
		player.move();

		if (player.Shooting() == true)
		{
			if (player.ShootMechanism() == 1)
			{
				ps.CreatePlayerProj(player.getX(), player.getY(), player.getCrossX(), player.getCrossY(), player.PROJECTILE_SPEED, gRenderer);
				shakeIntensity += 2;
			}
		}

		es.SpawnEnemy(gRenderer);
		es.moveEnemies(ps, player, pas, gRenderer);

		ps.moveProjectiles();	
		pas.moveParticles();

		player.cursorRotate();
		

		//~~~~~~~~~~~~~render step~~~~~~~~~~~~~~~~~~~~
		SDL_RenderClear(gRenderer);

		if (shakeIntensity != 0)
		{
			OffsetX = -(player.getX()) + (SCREEN_WIDTH / 2) + (rand() % (2 * shakeIntensity) - shakeIntensity);
			OffsetY = -(player.getY()) + (SCREEN_HEIGHT / 2) + (rand() % (2 * shakeIntensity) - shakeIntensity);
		}
		else
		{
			OffsetX = -(player.getX()) + (SCREEN_WIDTH / 2);
			OffsetY = -(player.getY()) + (SCREEN_HEIGHT / 2);
		}


		for (int x = 0; x < 32; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				grid.setPosX(x * 64 - 32);
				grid.setPosY(y * 64 - 32);
				grid.render(gRenderer, OffsetX, OffsetY);
			}
		}
		
		player.render(gRenderer, OffsetX, OffsetY);
		ps.renderProjectiles(gRenderer, OffsetX, OffsetY);
		es.renderEnemies(gRenderer, OffsetX, OffsetY);
		pas.renderParticles(gRenderer, OffsetX, OffsetY);
		std::cout << pas.getSize() << std::endl;

		SDL_RenderPresent(gRenderer);

		//~~~~~~~~~~~~~post-render logic~~~~~~~~~~~~~~~~~~~
		if (shakeIntensity != 0)
			shakeIntensity *= 0.9;
	}


	close();

	return 0;
}