#include "ParticleSystem.h"
#include <random>
#include <cmath>
#include <iostream>

//Handles particle creation, movement and rendering.
//Includes function that creates a "burst" of
//particles with random direction.

ParticleSystem::ParticleSystem()
{
	
}

void ParticleSystem::CreateBurst(int x, int y, int quantity, SDL_Renderer* renderer)
{
	double radians;

	for (int i = 0; i < quantity; i++)
	{
		radians = ((double)rand() / RAND_MAX) * (2 * M_PI);
		Particle newParticle(x, y, rand() % 45 + 5, radians, 80, renderer);
		pList.push_back(newParticle);
	}
}

void ParticleSystem::moveParticles()
{
	for (int x = 0; x < pList.size(); x++)
	{
		if (pList[x].isActive() == true)
		{
			pList[x].Propogate();
		}
		else
		{
			pList.erase(pList.begin() + x);
		}
	}
}

void ParticleSystem::renderParticles(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	for (int x = 0; x < pList.size(); x++)
	{
		pList[x].render(renderer, offsetX, offsetY);
	}
}

int ParticleSystem::getSize()
{
	return pList.size();
}