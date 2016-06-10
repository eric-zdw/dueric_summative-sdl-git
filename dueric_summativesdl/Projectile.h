#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Projectile {

private:
	int speedX;
	int speedY;

	int speed;
	int posX, posY;
	int endX, endY;
	int lifetime;

	int projWidth;
	int projHeight;

	SDL_Texture *texture;
	SDL_Surface *surface;
	SDL_Rect renderSpace;

	bool isActive;

public:
	Projectile(int x1, int y1, int xs, int ys, SDL_Renderer*);
	void render(SDL_Renderer *renderer);

	void Propogate();



};