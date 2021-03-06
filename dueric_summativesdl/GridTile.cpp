#include "GridTile.h"
#include <string>

//Grid Tile:
//Purple grid tile used to show playing area.
//A 16x8 grid is rendered with a for loop in main().

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

void GridTile::render(SDL_Renderer* renderer, int offsetX, int offsetY)
{

	offPosX = posX + offsetX + 32;
	offPosY = posY + offsetY + 32;

	renderSpace.x = offPosX;
	renderSpace.y = offPosY;

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
