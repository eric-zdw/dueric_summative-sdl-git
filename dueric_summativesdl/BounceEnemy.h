#pragma once
#include "Enemy.h"

class BounceEnemy : public Enemy {

public:
	BounceEnemy(SDL_Renderer*, int, int);
	void move();

	int xDirection, yDirection;
};