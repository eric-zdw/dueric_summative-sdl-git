#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "ProjectileSystem.h"

class Player
{
public:
	Player(SDL_Renderer*);
	void readInput(SDL_Event&, ProjectileSystem, SDL_Renderer*);
	void render(SDL_Renderer*, int, int);

	static const int PLAYER_WIDTH = 48;
	static const int PLAYER_HEIGHT = 48;
	static const int PLAYER_OFFSETX = -24;
	static const int PLAYER_OFFSETY = -24;

	static const int PLAYER_SPEED = 6;

	static const int CROSS_WIDTH = 24;
	static const int CROSS_HEIGHT = 24;
	static const int CROSS_OFFSETX = -12;
	static const int CROSS_OFFSETY = -12;

	static const int FIRE_RATE = 7;

	//declared in .cpp
	double PROJECTILE_SPEED;

	void move();
	void resetSpeed();

	void GetMousePosition(int, int);

	int getX();
	int getY();

	int getCrossX();
	int getCrossY();

	int cursorRotation;
	void cursorRotate();


	int ShootMechanism();
	bool Shooting();

private:
	int posX, posY;

	int dirX, dirY;
	int accX, accY;

	int mouseRenderX, mouseRenderY;
	int mousePosX, mousePosY;

	bool isShooting;

	int shootDelay;

	std::string path;
	SDL_Texture *crosshairTexture;
	SDL_Texture *playerTexture;
	SDL_Surface *surface;

	SDL_Rect crosshairSpace;
	SDL_Rect playerSpace;

};