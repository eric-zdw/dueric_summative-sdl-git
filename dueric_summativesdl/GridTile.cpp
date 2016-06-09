#include "GridTile.h"
#include <string>

GridTile::GridTile(SDL_Renderer* renderer)
{
	std::string path = "purpledrank.png";
	surface = IMG_Load(path.c_str());

	gridTexture = SDL_CreateTextureFromSurface(renderer, surface);

	renderSpace.h = GRID_HEIGHT;
	renderSpace.w = GRID_WIDTH;
}

void GridTile::render(int x, int y, SDL_Renderer* renderer)
{
	renderSpace.x = x;
	renderSpace.y = y;

	SDL_RenderCopy(renderer, gridTexture, NULL, &renderSpace);
}
