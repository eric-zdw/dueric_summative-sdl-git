#pragma once

#include "Projectile.h"
#include <SDL.h>
#include <SDL_image.h>

class PlayerProj : public Projectile {

private:



public:
	PlayerProj(int x1, int y1, int x2, int y2, double speed, SDL_Renderer *renderer);



};