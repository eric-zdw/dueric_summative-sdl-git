#include "ProjectileSystem.h"
#include "PlayerProj.h"
#include "Player.h"
#include <iostream>

ProjectileSystem::ProjectileSystem(SDL_Renderer* renderer)
{
}

void ProjectileSystem::CreatePlayerProj(int x1, int y1, int x2, int y2, int speed, SDL_Renderer *renderer)
{
	PlayerProj proj(x1, y1, x2, y2, speed, renderer);
	ppList.push_back(proj);

}

void ProjectileSystem::moveProjectiles()
{
	for (int x = 0; x < ppList.size(); x++)
	{
		ppList[x].Propogate();
		std::cout << "propogating " << x << std::endl;
	}
}

void ProjectileSystem::renderProjectiles(SDL_Renderer *renderer, int offsetX, int offsetY)
{
	for (int x = 0; x < ppList.size(); x++)
	{
		ppList[x].render(renderer, offsetX, offsetY);
	}
}

int ProjectileSystem::getSize()
{
	return ppList.size();
}