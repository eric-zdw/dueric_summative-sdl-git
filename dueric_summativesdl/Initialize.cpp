#include "Initialize.h"

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Renderer* gRenderer;

extern const int SCREEN_WIDTH = 1280;
extern const int SCREEN_HEIGHT = 720;


bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not initialize!");
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("METROSCOPE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window failed!");
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer failed!");
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("Image initialization failed!");
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	//TODO

	return success;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

bool start()
{
	bool success = true;
	if (init() == false)
	{
		success = false;
	}
	else if (loadMedia() == false)
	{
		success = false;
	}
		
	return success;
}

SDL_Texture* loadTexture(std::string path)
{
	SDL_Texture* finalTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("loading image failed!");
	}
	else
	{
		finalTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (finalTexture == NULL)
		{
			printf("Texture creation failed!");
		}
		SDL_FreeSurface(loadedSurface);
	}

	return finalTexture;
}