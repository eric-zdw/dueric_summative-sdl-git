#include "Projectile.h"

Projectile::Projectile(int x1, int y1, int x2, int y2, int speed)
{
	posX = x1;
	posY = y1;

	projHeight = 4;
	projWidth = 4;

	vectorX = x2 - x1;
	vectorY = y1 - y2;

	hyp = sqrt((vectorX * vectorX) + (vectorY * vectorY));
	radians = atan2(y1 - y2, x2 - x1);
	speedX = (speed * cos(radians));
	speedY = (speed * sin(radians));
}

void Projectile::render(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	offPosX = posX + offsetX;
	offPosY = posY + offsetY;

	renderSpace.x = offPosX;
	renderSpace.y = offPosY;

	SDL_RenderCopy(renderer, texture, NULL, &renderSpace);
}

void Projectile::Propogate()
{
	posX += speedX;
	posY += speedY;
}