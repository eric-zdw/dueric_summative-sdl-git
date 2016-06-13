#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "GridTile.h"
#include "Player.h"
#include "ProjectileSystem.h"

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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					ps.CreatePlayerProj(player.getX(), player.getY(), player.getCrossX(), player.getCrossY(), player.PROJECTILE_SPEED, gRenderer);
				}
			}
			
		}
		player.move();

		OffsetX = -(player.getX()) + (SCREEN_WIDTH / 2);
		OffsetY = -(player.getY()) + (SCREEN_HEIGHT / 2);


		ps.moveProjectiles();

		player.cursorRotate();


		//~~~~~~~~~~~~~render step~~~~~~~~~~~~~~~~~~~~
		SDL_RenderClear(gRenderer);
		for (int x = 0; x < 30; x++)
		{
			for (int y = 0; y < 15; y++)
			{
				grid.setPosX(x * 64 - 32);
				grid.setPosY(y * 64 - 32);
				grid.render(gRenderer, OffsetX, OffsetY);
			}
		}
		
		player.render(gRenderer, OffsetX, OffsetY);
		ps.renderProjectiles(gRenderer, OffsetX, OffsetY);


		SDL_RenderPresent(gRenderer);
	}


	close();

	return 0;
}