#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "ParticleSystem.h"

class EnemySystem {
private:
	std::vector<Enemy> enemyList;
	static const int SPAWN_DELAY = 150;
	int spawnTimer;

public:
	EnemySystem();
	void SpawnEnemy(SDL_Renderer*);

	void moveEnemies(ProjectileSystem&, Player, ParticleSystem&, SDL_Renderer*);
	void renderEnemies(SDL_Renderer*, int, int);
	std::vector<Enemy> &getList();

};

