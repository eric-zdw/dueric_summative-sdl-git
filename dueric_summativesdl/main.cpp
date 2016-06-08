#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>


SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;

//Screen rendering constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_FPS = 60;
extern const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Looping flag
bool running = true;

//Event handler
SDL_Event e;

//Text stuff

//Initialize function
void close();
bool start();

//Texture loading function
SDL_Texture* loadTexture(std::string path);

int main(int argc, char* argv[])
{
	if (start() == false)
	{
		printf("Startup failed!");
	}
	else
	{
		while (running == true)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					running = false;
				}
				//TODO code
			}
		}
	}

	close();
	return 0;
}