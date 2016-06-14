#include "Enemy.h"
#include <iostream>

Enemy::Enemy(SDL_Renderer *renderer, int x, int y)
{
	posX = x;
	posY = y;

	renderSpace.h = ENEMY_HEIGHT;
	renderSpace.w = ENEMY_WIDTH;

	collisionBox.h = ENEMY_HEIGHT;
	collisionBox.w = ENEMY_WIDTH;

	isActive = true;
}

void Enemy::render(SDL_Renderer *renderer, int offsetX, int offsetY)
{
	offPosX = posX + offsetX;
	offPosY = posY + offsetY;

	renderSpace.x = offPosX - (ENEMY_WIDTH / 2);
	renderSpace.y = offPosY - (ENEMY_HEIGHT / 2);

	SDL_RenderCopy(renderer, texture, NULL, &renderSpace);
}

SDL_Rect Enemy::getCollisionBox()
{
	return collisionBox;
}

void Enemy::loseHealth(int damage)
{
	Enemy::health -= damage;
	if (Enemy::health <= 0)
	{
		isActive = false;
	}
}

bool Enemy::getStatus()
{
	return isActive;
}

int Enemy::getHealth()
{
	return health;
}

double Enemy::getX()
{
	return posX;
}

double Enemy::getY()
{
	return posY;
}