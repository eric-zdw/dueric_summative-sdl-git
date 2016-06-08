#include "Player.h"

Player::Player()
{
	posX = 200;
	posY = 200;
	velX = 0;
	velY = 0;
	accX = 0;
	accY = 0;
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		//case SDLK_w: velX
		}
	}
}

void Player::move()
{

}
