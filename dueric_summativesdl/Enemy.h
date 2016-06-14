#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Player.h"

class Enemy {
protected:
	int health;
	double direction;
	double speed;

	static const int ENEMY_WIDTH = 32;
	static const int ENEMY_HEIGHT = 32;

	SDL_Texture *texture;
	SDL_Surface *surface;
	
	SDL_Rect renderSpace;

	double radians;
	double hyp;

	std::string path;

	double posX, posY;
	int offPosX, offPosY;

	double speedX, speedY;

	SDL_Rect collisionBox;

	bool isActive;

public:
	Enemy(SDL_Renderer*, int, int);
	void render(SDL_Renderer*, int, int);

	SDL_Rect getCollisionBox();

	void loseHealth(int);

	int getHealth();

	bool getStatus();

	double getX();
	double getY();

};