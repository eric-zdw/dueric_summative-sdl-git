#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "ParticleSystem.h"
#include "FollowEnemy.h"
#include "BounceEnemy.h"

class EnemySystem {
private:
	std::vector<BounceEnemy> bEnemyList;
	std::vector<FollowEnemy> fEnemyList;
	static const int SPAWN_DELAY = 200;
	int spawnReset;
	int spawnTimer;

	int reduceDelay;
	int chooseEnemy;

public:
	EnemySystem();
	void SpawnEnemy(SDL_Renderer*, Player);

	void moveEnemies(ProjectileSystem&, Player&, ParticleSystem&, SDL_Renderer*);
	void renderEnemies(SDL_Renderer*, int, int);

	void resetEnemies(SDL_Renderer*, Player&, ParticleSystem&);

};

