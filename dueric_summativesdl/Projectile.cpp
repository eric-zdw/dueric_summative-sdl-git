#include "Projectile.h"

Projectile::Projectile(int x1, int y1, int x2, int y2, int xs, int ys, SDL_Renderer *renderer)
{
	posX = x1;
	posY = y1;
	
	//speed is measured in pixels per second
	speedX = xs;
	speedY = ys;

	std::string path = "projectile.png";
	surface = IMG_Load(path.c_str());

	projHeight = 4;
	projWidth = 4;

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	speed = (cos(radians));

	hyp = sqrt(())

	radians = atan2(y1 - y2, x2 - x1);
	
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

void Projectile::setSize(int x, int y)
{
	projHeight = y;
	projWidth = x;
}