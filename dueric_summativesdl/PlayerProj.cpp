#include "PlayerProj.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

//Player Projectile;
//Travels to mouse position
//and disappears after 100 frames
//or hits an enemy.
//See Projectile base class.

PlayerProj::PlayerProj(int x1, int y1, int x2, int y2, double speed, SDL_Renderer *renderer) : Projectile(x1, y1, x2, y2, speed)
{
	projHeight = 16;
	projWidth = 6;

	damage = 15;

	renderSpace.h = projHeight;
	renderSpace.w = projWidth;

	path = "playerproj.png";
	surface = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	collisionBox.w = 4;
	collisionBox.h = 4;

	lifetime = 100;
}