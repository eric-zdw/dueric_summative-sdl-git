#include "Player.h"

Player::Player(SDL_Renderer *renderer)
{
	posX = 0;
	posY = 0;
	velX = 0;
	velY = 0;
	accX = 0;
	accY = 0;

	crosshairPath = "crosshair.png";
	surface = IMG_Load(crosshairPath.c_str());
	crosshairTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	crosshairSpace.h = CROSS_HEIGHT;
	crosshairSpace.w = CROSS_WIDTH;
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

void Player::GetMousePosition()
{
	SDL_GetMouseState(&mousePosX, &mousePosY);
	crosshairSpace.x = mousePosX + CROSS_OFFSETX;
	crosshairSpace.y = mousePosY + CROSS_OFFSETY;
}

void Player::render(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, crosshairTexture, NULL, &crosshairSpace);
}

int Player::getCrossX()
{
	return mousePosX;
}