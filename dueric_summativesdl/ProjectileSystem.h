#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Projectile.h"
#include "PlayerProj.h"

class ProjectileSystem {
private:
	std::vector<PlayerProj> ppList;

public:
	ProjectileSystem(SDL_Renderer*);
	void CreatePlayerProj(int, int, int, int, double, SDL_Renderer*);
	void moveProjectiles();
	void renderProjectiles(SDL_Renderer*, int, int);
	int getSize();

	std::vector<PlayerProj> getList();


};