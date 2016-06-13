#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Enemy.h"
#include "Player.h"

class EnemySystem {
private:
	std::vector<Enemy> enemyList;

public:
	EnemySystem();
	void SpawnEnemy(SDL_Renderer*);

	void moveEnemies(ProjectileSystem, Player);
	void renderEnemies(SDL_Renderer*, int, int);

};

