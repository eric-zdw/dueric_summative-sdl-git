#include "FollowEnemy.h"

FollowEnemy::FollowEnemy(SDL_Renderer *renderer, int x, int y) : Enemy(renderer, x, y)
{
	path = "enemy.png";
	surface = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	health = 100;
	speed = 3;
}

void FollowEnemy::getDirection(Player player)
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
	//std::cout << radians * (180 / M_PI) << std::endl;
}

void FollowEnemy::move()
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

	collisionBox.x = posX - (ENEMY_WIDTH / 2);
	collisionBox.y = posY - (ENEMY_HEIGHT / 2);

}