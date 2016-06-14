#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Particle.h"

class ParticleSystem
{
private:
	std::vector<Particle> pList;

public:
	ParticleSystem();
	void CreateBurst(int, int, int, SDL_Renderer*);

	void moveParticles();
	void renderParticles(SDL_Renderer*, int, int);
	int getSize();

};