#include "EnemySystem.h"
#include "ProjectileSystem.h"
#include "ParticleSystem.h"
#include <random>

extern int shakeIntensity;

EnemySystem::EnemySystem() {

	spawnTimer = SPAWN_DELAY;
}

void EnemySystem::SpawnEnemy(SDL_Renderer* renderer)
{
	if (spawnTimer > 0)
		spawnTimer -= 1;
	else
	{
		Enemy newEnemy(renderer, rand() % 2048, rand() % 1024);
		enemyList.push_back(newEnemy);
		spawnTimer = SPAWN_DELAY;
	}
}

void EnemySystem::moveEnemies(ProjectileSystem &ps, Player player, ParticleSystem &pas, SDL_Renderer *renderer)
{
	for (int x = 0; x < enemyList.size(); x++)
	{
		if (enemyList[x].getStatus() == true)
		{
			enemyList[x].getDirection(player);
			enemyList[x].move();
		}
		else
		{
			pas.CreateBurst(enemyList[x].getX(), enemyList[x].getY(), 10, renderer);
			enemyList.erase(enemyList.begin() + x);
			shakeIntensity += 50;
		}
	}


	for (int x = 0; x < enemyList.size(); x++)
	{
		for (int y = 0; y < ps.getList().size(); y++)
		{
			if (SDL_HasIntersection(&enemyList[x].getCollisionBox(), &ps.getList()[y].getCollisionBox()) == SDL_TRUE)
			{
				enemyList[x].loseHealth(ps.getList()[y].getDamage());
				ps.getList()[y].active = 0;
				shakeIntensity += 5;
			}
		}
	}
}

void EnemySystem::renderEnemies(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	for (int x = 0; x < enemyList.size(); x++)
	{
		enemyList[x].render(renderer, offsetX, offsetY);
	}
}

std::vector<Enemy> &EnemySystem::getList()
{
	return enemyList;
}