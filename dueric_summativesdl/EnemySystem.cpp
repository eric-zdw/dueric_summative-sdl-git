#include "EnemySystem.h"
#include "FollowEnemy.h"
#include "BounceEnemy.h"
#include "ProjectileSystem.h"
#include "ParticleSystem.h"
#include <random>
#include <time.h>

extern int shakeIntensity;

EnemySystem::EnemySystem() {
	spawnReset = SPAWN_DELAY;
	spawnTimer = SPAWN_DELAY;

	reduceDelay = 150;
}

void EnemySystem::SpawnEnemy(SDL_Renderer* renderer)
{
	chooseEnemy = rand() % 2;

	if (spawnTimer > 0)
		spawnTimer -= 1;
	else
	{
		if (chooseEnemy == 0)
		{
			FollowEnemy newEnemy(renderer, rand() % 2048, rand() % 1024);
			fEnemyList.push_back(newEnemy);
		}
		else
		{
			BounceEnemy newEnemy(renderer, rand() % 2048, rand() % 1024);
			bEnemyList.push_back(newEnemy);
		}
		spawnTimer = spawnReset;
	}
}

void EnemySystem::moveEnemies(ProjectileSystem &ps, Player player, ParticleSystem &pas, SDL_Renderer *renderer)
{
	for (int x = 0; x < fEnemyList.size(); x++)
	{
		if (fEnemyList[x].getStatus() == true)
		{
			fEnemyList[x].getDirection(player);
			fEnemyList[x].move();
		}
		else
		{
			pas.CreateBurst(fEnemyList[x].getX(), fEnemyList[x].getY(), 25, renderer);
			fEnemyList.erase(fEnemyList.begin() + x);
			shakeIntensity += 25;
		}
	}
	for (int x = 0; x < bEnemyList.size(); x++)
	{
		if (bEnemyList[x].getStatus() == true)
		{
			bEnemyList[x].move();
		}
		else
		{
			pas.CreateBurst(bEnemyList[x].getX(), bEnemyList[x].getY(), 25, renderer);
			bEnemyList.erase(bEnemyList.begin() + x);
			shakeIntensity += 25;
		}
	}


	for (int x = 0; x < fEnemyList.size(); x++)
	{
		for (int y = 0; y < ps.getList().size(); y++)
		{
			if (SDL_HasIntersection(&fEnemyList[x].getCollisionBox(), &ps.getList()[y].getCollisionBox()) == SDL_TRUE)
			{
				fEnemyList[x].loseHealth(ps.getList()[y].getDamage());
				ps.getList()[y].active = 0;
				shakeIntensity += 5;
				pas.CreateBurst(ps.getList()[y].getX(), ps.getList()[y].getY(), 3, renderer);
			}
		}
	}
	for (int x = 0; x < bEnemyList.size(); x++)
	{
		for (int y = 0; y < ps.getList().size(); y++)
		{
			if (SDL_HasIntersection(&bEnemyList[x].getCollisionBox(), &ps.getList()[y].getCollisionBox()) == SDL_TRUE)
			{
				bEnemyList[x].loseHealth(ps.getList()[y].getDamage());
				ps.getList()[y].active = 0;
				shakeIntensity += 5;
				pas.CreateBurst(ps.getList()[y].getX(), ps.getList()[y].getY(), 3, renderer);
			}
		}
	}

	reduceDelay--;
	if (spawnReset > 40 && reduceDelay <= 0)
	{
		spawnReset -= 2;
		reduceDelay = 150;
		std::cout << spawnReset << std::endl;
	}

}

void EnemySystem::renderEnemies(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	for (int x = 0; x < fEnemyList.size(); x++)
	{
		fEnemyList[x].render(renderer, offsetX, offsetY);
	}
	for (int x = 0; x < bEnemyList.size(); x++)
	{
		bEnemyList[x].render(renderer, offsetX, offsetY);
	}
}