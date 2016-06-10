#include "GridTile.h"
#include <string>

GridTile::GridTile(SDL_Renderer* renderer)
{
	std::string path = "purpledrank.png";
	surface = IMG_Load(path.c_str());

	gridTexture = SDL_CreateTextureFromSurface(renderer, surface);

	renderSpace.h = GRID_HEIGHT;
	renderSpace.w = GRID_WIDTH;
	posX = 0;
	posY = 0;
}

void GridTile::render(SDL_Renderer* renderer)
{
	renderSpace.x = posX;
	renderSpace.y = posY;

	SDL_RenderCopy(renderer, gridTexture, NULL, &renderSpace);
}

void GridTile::setPosX(int x)
{
	posX = x;
}

void GridTile::setPosY(int y)
{
	posY = y;
}
