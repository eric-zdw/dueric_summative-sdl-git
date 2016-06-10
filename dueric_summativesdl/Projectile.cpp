#include "Projectile.h"

Projectile::Projectile(int x, int y, int xs, int ys, SDL_Renderer *renderer)
{
	posX = x;
	posY = y;
	
	//speed is measured in pixels per second
	speedX = xs;
	speedY = ys;

	std::string path = "projectile.png";
	surface = IMG_Load(path.c_str());

	projWidth = 4;
	projHeight = 4;

	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void Projectile::render(SDL_Renderer* renderer)
{

}

void Projectile::Propogate()
{
	if (isActive == true)
	{
		
	}
}