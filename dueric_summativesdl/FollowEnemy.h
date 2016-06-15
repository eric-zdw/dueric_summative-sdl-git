#pragma once
#include "Enemy.h"

class FollowEnemy : public Enemy {
private:
	int vectorX, vectorY;

public:
	FollowEnemy(SDL_Renderer*, int, int);
	void getDirection(Player);
	void move(Player);

};