#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "GridTile.h"
#include "TTFTexture.h"

extern const int SCREEN_WIDTH = 1280;
extern const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gCurrentSurface = NULL;
SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;

//bool init(SDL_Window* window, SDL_Surface* screenSurface, SDL_Renderer* renderer);

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("you suck lol");
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		gScreenSurface = SDL_GetWindowSurface(gWindow);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		int imgFlags = IMG_INIT_PNG;

		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}


	}

	return success;

}

SDL_Texture* loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);

	return newTexture;

}

SDL_Surface* loadSurface(std::string path)
{

	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());

	optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
	SDL_FreeSurface(loadedSurface);

	return optimizedSurface;
}




bool loadMedia()
{
	bool success = true;



	return success;
}

void close()
{
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;
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

	GridTile grid(gRenderer);
	TTFTexture text(16);



	bool quit = false;
	SDL_Event e;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_RenderClear(gRenderer);
		grid.render(50, 50, gRenderer);
		text.CreateText(200, 50, "ohhhh", gRenderer);
		SDL_RenderPresent(gRenderer);
	}





	close();

	return 0;
}