#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Player
{
public:
	Player(SDL_Renderer*);
	void readInput(SDL_Event& e);
	void render(SDL_Renderer*);

	static const int PLAYER_WIDTH = 48;
	static const int PLAYER_HEIGHT = 48;

	static const int PLAYER_SPEED = 4;

	static const int CROSS_WIDTH = 24;
	static const int CROSS_HEIGHT = 24;
	static const int CROSS_OFFSETX = -12;
	static const int CROSS_OFFSETY = -12;

	void move();
	void resetSpeed();

	void GetMousePosition();

private:
	int posX, posY;
	int dirX, dirY;
	int accX, accY;

	int mousePosX, mousePosY;

	std::string path;
	SDL_Texture *crosshairTexture;
	SDL_Texture *playerTexture;
	SDL_Surface *surface;

	SDL_Rect crosshairSpace;
	SDL_Rect playerSpace;

};