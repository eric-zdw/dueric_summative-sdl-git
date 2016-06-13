#include "Enemy.h"
#include <iostream>

Enemy::Enemy(SDL_Renderer *renderer)
{
	path = "enemy.png";
	surface = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	speed = 3;

	renderSpace.h = ENEMY_HEIGHT;
	renderSpace.w = ENEMY_WIDTH;
}

void Enemy::getDirection(Player player)
{
	vectorX = player.getX() - posX;
	vectorY = posY - player.getY();

	hyp = sqrt((vectorX * vectorX) + (vectorY * vectorY));
	if (player.getY() > posY)
	{
		radians = (2 * M_PI) - atan2(abs(player.getY() - posY), player.getX() - posX);
	}
	else
		radians = atan2(abs(player.getY() - posY), player.getX() - posX);

	speedX = (speed * cos(radians));
	speedY = -(speed * sin(radians));
	std::cout << radians << " " << vectorY << std::endl;
	//std::cout << radians * (180 / M_PI) << std::endl;
}

void Enemy::move()
{
	posX += speedX;
	posY += speedY;

	if (posX < 0)
		posX = 0;
	if (posX > 2048)
		posX = 2048;
	if (posY < 0)
		posY = 0;
	if (posY > 1024)
		posY = 1024;
}

void Enemy::render(SDL_Renderer *renderer, int offsetX, int offsetY)
{
	offPosX = posX + offsetX;
	offPosY = posY + offsetY;

	renderSpace.x = offPosX - (ENEMY_WIDTH / 2);
	renderSpace.y = offPosY - (ENEMY_HEIGHT / 2);

	SDL_RenderCopy(renderer, texture, NULL, &renderSpace);
}