#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <math.h>

class Projectile {

private:
	double speedX;
	double speedY;



	int vectorX, vectorY;

protected:
	int projWidth;
	int projHeight;

	double posX, posY;
	int endX, endY;

	double speed;
	int lifetime;

	int damage;

	std::string path;

	SDL_Texture *texture;
	SDL_Surface *surface;
	SDL_Rect renderSpace;

	int offPosX, offPosY;
	
	double radians;
	double hyp;

	SDL_Rect collisionBox;
public:
	Projectile(int x1, int y1, int x2, int y2, double speed);
	void render(SDL_Renderer *renderer, int, int);

	bool active;

	void Propogate();

	bool isActive();
	void setActive(bool x);

	SDL_Rect getCollisionBox();

	int getDamage();
};