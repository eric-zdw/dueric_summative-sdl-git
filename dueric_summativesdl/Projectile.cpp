#include "Projectile.h"
#include <iostream>

Projectile::Projectile(int x1, int y1, int x2, int y2, double speed)
{
	posX = (float)x1;
	posY = (float)y1;

	projHeight = 4;
	projWidth = 4;

	vectorX = x2 - x1;
	vectorY = y1 - y2;

	hyp = sqrt((vectorX * vectorX) + (vectorY * vectorY));
	if (y2 > y1)
	{
		radians = (2 * M_PI) - atan2(abs(y2 - y1), x2 - x1);
	}
	else
		radians = atan2(abs(y2 - y1), x2 - x1);

	speedX = (speed * cos(radians));
	speedY = -(speed * sin(radians));
	//std::cout << radians * (180 / M_PI) << std::endl;

	active = true;
}

void Projectile::render(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	offPosX = posX + offsetX;
	offPosY = posY + offsetY;

	renderSpace.x = offPosX - (projWidth / 2);
	renderSpace.y = offPosY - (projHeight / 2);

	//SDL_RenderCopy(renderer, texture, NULL, &renderSpace);
	SDL_RenderCopyEx(renderer, texture, NULL, &renderSpace, -(radians * (180 / M_PI)) - 90, NULL, SDL_FLIP_NONE);
}

void Projectile::Propogate()	
{
	posX += speedX;
	posY += speedY;

	collisionBox.x = posX - (collisionBox.w / 2);
	collisionBox.y = posY - (collisionBox.h / 2);

	lifetime--;
	if (lifetime <= 0)
		active = false;

//	if (posX > 2048 || posX < 0 || posY > 1024 || posY < 0)
//		active = false;
}

bool Projectile::isActive()
{
	return active;
}

void Projectile::setActive(bool x)
{
	active = x;
}

int Projectile::getDamage()
{
	return damage;
}

SDL_Rect Projectile::getCollisionBox()
{
	return collisionBox;
}