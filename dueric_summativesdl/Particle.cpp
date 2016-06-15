#include "Particle.h"
#include <cmath>

//Particles created when the player
//or an enemy is destroyed.

Particle::Particle(int x, int y, int speed, double radians, int time, SDL_Renderer *renderer)
{
	posX = x;
	posY = y;
	pSpeed = speed;
	lifetime = time;

	angle = radians;

	active = true;

	path = "particle.png";
	surface = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	renderSpace.h = PARTICLE_HEIGHT;
	renderSpace.w = PARTICLE_WIDTH;
}

void Particle::Propogate()
{
	posX += pSpeed * cos(angle);
	posY += -(pSpeed * sin(angle));

	pSpeed *= 0.99;
	if (pSpeed <= 0)
		active = false;

	if (lifetime > 0)
		lifetime--;
	else
		active = false;
}

void Particle::render(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	offPosX = posX + offsetX;
	offPosY = posY + offsetY;

	renderSpace.x = offPosX - (PARTICLE_HEIGHT / 2);
	renderSpace.y = offPosY - (PARTICLE_WIDTH / 2);

	SDL_RenderCopy(renderer, texture, NULL, &renderSpace);

}

bool Particle::isActive()
{
	return active;
}