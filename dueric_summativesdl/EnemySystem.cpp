#include "EnemySystem.h"
#include "FollowEnemy.h"
#include "BounceEnemy.h"
#include "ProjectileSystem.h"
#include "ParticleSystem.h"
#include <random>
#include <time.h>

//Handles enemy creation, movement and rendering.
//Spawns a random enemy at a random position.
//The rate at which enemies spawn increases
//as time passes; spawn rate decreases
//when the player is destroyed.
//
//Several events shake the screen,
//including enemy damage and enemy
//destruction.

extern int shakeIntensity;

EnemySystem::EnemySystem() {
	spawnReset = SPAWN_DELAY;
	spawnTimer = SPAWN_DELAY;

	reduceDelay = 150;
}

//vector lists are used to hold enemy references
//enemies do not spawn while the player is respawning
void EnemySystem::SpawnEnemy(SDL_Renderer* renderer, Player player)
{
	chooseEnemy = rand() % 2;

	if (player.getActive() == true)
	{
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
}

//moves every enemy in the enemy lists;
//if the enemy is "inactive" (usually zero health)
//the enemy is taken out of the list
//and particles are created;
//touching players will destroy the player.
void EnemySystem::moveEnemies(ProjectileSystem &ps, Player &player, ParticleSystem &pas, SDL_Renderer *renderer)
{
	for (int x = 0; x < fEnemyList.size(); x++)
	{
		if (fEnemyList[x].getStatus() == true)
		{
			fEnemyList[x].getDirection(player);
			fEnemyList[x].move(player);
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
			//SDL built-in rectangle collision detection
			if (SDL_HasIntersection(&fEnemyList[x].getCollisionBox(), &ps.getList()[y].getCollisionBox()) == SDL_TRUE)
			{
				fEnemyList[x].loseHealth(ps.getList()[y].getDamage());
				ps.getList()[y].active = 0;
				shakeIntensity += 5;
				pas.CreateBurst(ps.getList()[y].getX(), ps.getList()[y].getY(), 3, renderer);
			}
		}
		if (SDL_HasIntersection(&fEnemyList[x].getCollisionBox(), &player.getCollision()) == SDL_TRUE && player.getActive() == true)
		{
			//destroy player, destroy all enemies and increase enemy spawn timer
			resetEnemies(renderer, player, pas);
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
		if (SDL_HasIntersection(&bEnemyList[x].getCollisionBox(), &player.getCollision()) == SDL_TRUE && player.getActive() == true)
		{
			resetEnemies(renderer, player, pas);
		}
	}

	reduceDelay--;
	if (spawnReset > 40 && reduceDelay <= 0)
	{
		spawnReset -= 4;
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

void EnemySystem::resetEnemies(SDL_Renderer* renderer, Player &player, ParticleSystem &pas)
{
	pas.CreateBurst(player.getX(), player.getY(), 60, renderer);
	player.getActive() = false;
	player.resetSpeed();
	shakeIntensity += 250;
	spawnReset += (300 - spawnReset) / 4;

	for (int x = 0; x < fEnemyList.size(); x++)
	{
		pas.CreateBurst(fEnemyList[x].getX(), fEnemyList[x].getY(), 25, renderer);
		fEnemyList.erase(fEnemyList.begin() + x);
		shakeIntensity += 10;
	}
	for (int x = 0; x < bEnemyList.size(); x++)
	{
		pas.CreateBurst(bEnemyList[x].getX(), bEnemyList[x].getY(), 25, renderer);
		bEnemyList.erase(bEnemyList.begin() + x);
		shakeIntensity += 10;
	}
}