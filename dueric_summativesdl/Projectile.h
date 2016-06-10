#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <math.h>

class Projectile {

private:
	int speedX;
	int speedY;

	bool isActive;

protected:
	int projWidth;
	int projHeight;

	int posX, posY;
	int endX, endY;

	double speed;
	int lifetime;

	SDL_Texture *texture;
	SDL_Surface *surface;
	SDL_Rect renderSpace;
	
	double radians;
	double hyp;

public:
	Projectile(int x1, int y1, int x2, int y2, int xs, int ys, SDL_Renderer*);
	void render(SDL_Renderer *renderer);

	void Propogate();

	void setSize(int, int);


};