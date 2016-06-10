#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Player
{
public:
	Player(SDL_Renderer*);
	void handleEvent(SDL_Event& e);
	void render(SDL_Renderer*);

	static const int PLAYER_WIDTH = 32;
	static const int PLAYER_HEIGHT = 32;
	static const int CROSS_WIDTH = 24;
	static const int CROSS_HEIGHT = 24;
	static const int CROSS_OFFSETX = -12;
	static const int CROSS_OFFSETY = -12;

	void move();
	void GetMousePosition();

	int getCrossX();

private:
	int posX, posY;
	int velX, velY;
	int accX, accY;

	int mousePosX, mousePosY;

	std::string crosshairPath;
	SDL_Texture *crosshairTexture;
	SDL_Surface *surface;

	SDL_Rect crosshairSpace;

};