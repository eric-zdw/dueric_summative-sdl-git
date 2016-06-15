//METROSCOPE - Created by Eric Du
//An attempt at making (a proof of)
//a 2D top-down shooter using SDL
//libraries.
//
//WASD to move, mouse to aim and shoot
//Survive as long as possible against red and
//orange dots
//It gets harder and harder, but infinite lives

#include "GridTile.h"
#include "Player.h"
#include "Enemy.h"
#include "ProjectileSystem.h"
#include "EnemySystem.h"
#include "ParticleSystem.h"
#include <time.h>

//window resolution
extern const int SCREEN_WIDTH = 1280;
extern const int SCREEN_HEIGHT = 720;

//variable determining screen shaking intensity
extern int shakeIntensity = 0;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//offset that determines where objects are
//rendered on the screen (since the camera
//follows the player); determined by where the
//player is relative to the origin
int OffsetX = 0;
int OffsetY = 0;

//initialize all renderers (and the random number generator)
bool init()
{
	srand(time(NULL));
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

//run when closing the game
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

	//create all essential objects;
	//all systems such as projectile/enemy handlers,
	//keyboard input
	ProjectileSystem ps(gRenderer);
	EnemySystem es;
	ParticleSystem pas;
	GridTile grid(gRenderer);
	SDL_Event e;
	Player player(gRenderer);

	SDL_ShowCursor(SDL_DISABLE);

	bool quit = false;
	while (!quit)
	{
		//~~~~~~~~~~~~~logic step~~~~~~~~~~~~~~~~~~~~
		//all object movement, collision detection,
		//keyboard input events run in this section
		
		player.GetMousePosition(OffsetX, OffsetY);

		//player speed is reset if no keys are being pressed;
		//this prevents unwanted movement after respawning
		if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W] == 0 &&
			SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S] == 0 &&
			SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A] == 0 &&
			SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D] == 0)
		{
			player.resetSpeed();
		}

		//while input events are still in the queue
		while (SDL_PollEvent(&e) != 0)
		{
			//quit when X button on the window is pressed
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//gets key information and sets movement flags for player.move();
			//see Player.cpp
			player.readInput(e, ps, gRenderer);
		}

		//i.e. while the player is alive
		if (player.getActive() == true)
		{
			player.move();

			if (player.Shooting() == true)
			{
				if (player.ShootMechanism() == 1)
				{
					ps.CreatePlayerProj(player.getX(), player.getY(), player.getCrossX(), player.getCrossY(), player.PROJECTILE_SPEED, gRenderer);
					shakeIntensity += 2;
				}
			}
		}
		//i.e. while the player is dead
		else
		{
			player.countTimer();
		}

		//these functions are run every frame;
		//see EnemySystem.cpp, ProjectileSystem.cpp,
		//ParticleSystem.cpp
		es.SpawnEnemy(gRenderer, player);
		es.moveEnemies(ps, player, pas, gRenderer);
		ps.moveProjectiles();	
		pas.moveParticles();

		//Rotate the crosshair :)
		player.cursorRotate();
		

		//~~~~~~~~~~~~~render step~~~~~~~~~~~~~~~~~~~~
		SDL_RenderClear(gRenderer);

		//Game will crash when dividing by zero
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

		//renders a 32x16 grid
		for (int x = 0; x < 32; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				grid.setPosX(x * 64 - 32);
				grid.setPosY(y * 64 - 32);
				grid.render(gRenderer, OffsetX, OffsetY);
			}
		}
		
		if (player.getActive() == true)
		{
			player.render(gRenderer, OffsetX, OffsetY);
		}


		ps.renderProjectiles(gRenderer, OffsetX, OffsetY);
		es.renderEnemies(gRenderer, OffsetX, OffsetY);
		pas.renderParticles(gRenderer, OffsetX, OffsetY);

		SDL_RenderPresent(gRenderer);

		//~~~~~~~~~~~~~post-render logic~~~~~~~~~~~~~~~~~~~
		if (shakeIntensity != 0)
			shakeIntensity *= 0.9;
	}


	close();

	return 0;
}