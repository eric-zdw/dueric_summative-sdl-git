#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Particle {
private:
	int pSpeed;
	double angle;
	double posX;
	double posY;

	static const int PARTICLE_WIDTH = 4;
	static const int PARTICLE_HEIGHT = 4;

	int lifetime;
	bool active;
	
	std::string path;
	SDL_Texture *texture;
	SDL_Surface *surface;
	
	SDL_Rect renderSpace;

	double offPosX;
	double offPosY;


public:
	Particle(int, int, int, double, int, SDL_Renderer*);
	void Propogate();
	void render(SDL_Renderer*, int, int);

	bool isActive();

};