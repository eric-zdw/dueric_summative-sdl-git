#include "BounceEnemy.h"
#include <random>

//Bounce Enemy:
//Travels in a straight line (random direction);
//bounces off boundaries of playing area.

BounceEnemy::BounceEnemy(SDL_Renderer *renderer, int x, int y) : Enemy(renderer, x, y)
{
	path = "bounceenemy.png";
	surface = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	health = 45;
	speed = 8;

	double radians = ((double)rand() / RAND_MAX) * (2 * M_PI);
	speedX = abs(speed * cos(radians));
	speedY = abs(speed * sin(radians));

	xDirection = rand() % 2;
	yDirection = rand() % 2;
}

void BounceEnemy::move()
{
	if (posX >= (float)2048)
	{
		xDirection = 0;
	}
	if (posX <= (float)0)
	{
		xDirection = 1;
	}
	if (posY >= (float)1024)
	{
		yDirection = 0;
	}
	if (posY <= (float)0)
	{
		yDirection = 1;
	}

	if (xDirection == 0)
		posX -= speedX;
	else
		posX += speedX;

	if (yDirection == 0)
		posY -= speedY;
	else
		posY += speedY;

	collisionBox.x = posX - (ENEMY_WIDTH / 2);
	collisionBox.y = posY - (ENEMY_HEIGHT / 2);
}