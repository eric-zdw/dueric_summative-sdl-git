#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class GridTile {
private:
	const int GRID_WIDTH = 64;
	const int GRID_HEIGHT = 64;
	SDL_Texture* gridTexture;
	SDL_Surface* surface;
	std::string path;

	SDL_Rect renderSpace;

	int posX, posY;
	int offPosX, offPosY;

public:
	GridTile(SDL_Renderer*);
	void render(SDL_Renderer*, int, int);

	void setPosX(int);
	void setPosY(int);

};