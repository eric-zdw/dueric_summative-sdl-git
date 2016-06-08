#pragma once
#include <SDL.h>

class Player
{
public:
	Player();
	void handleEvent(SDL_Event& e);
	void render();

	static const int PLAYER_WIDTH = 32;
	static const int PLAYER_HEIGHT = 32;

	void move();
private:
	int posX, posY;
	int velX, velY;
	int accX, accY;

};