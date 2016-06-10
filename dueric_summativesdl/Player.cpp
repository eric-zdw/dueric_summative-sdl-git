#include "Player.h"
#include <iostream>

Player::Player(SDL_Renderer *renderer)
{
	posX = 0;
	posY = 0;
	dirX = 0;
	dirY = 0;
	accX = 0;
	accY = 0;

	path = "crosshair.png";
	surface = IMG_Load(path.c_str());
	crosshairTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	path = "player.png";
	surface = IMG_Load(path.c_str());
	playerTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	crosshairSpace.h = CROSS_HEIGHT;
	crosshairSpace.w = CROSS_WIDTH;
	playerSpace.h = PLAYER_HEIGHT;
	playerSpace.w = PLAYER_WIDTH;
}

void Player::readInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			dirY += -1;
			std::cout << "up";
			break;
		case SDLK_s:
			dirY += 1;
			std::cout << "up";
			break;
		case SDLK_a:
			dirX += -1;
			std::cout << "up";
			break;
		case SDLK_d:
			dirX += 1;
			std::cout << "up";
			break;
		}
	}
	
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			dirY -= -1;
			std::cout << "up";
			break;
		case SDLK_s:
			dirY -= 1;
			std::cout << "up";
			break;
		case SDLK_a:
			dirX -= -1;
			std::cout << "up";
			break;
		case SDLK_d:
			dirX -= 1;
			std::cout << "up";
			break;
		}
	}
}

void Player::GetMousePosition()
{
	SDL_GetMouseState(&mousePosX, &mousePosY);
	crosshairSpace.x = mousePosX + CROSS_OFFSETX;
	crosshairSpace.y = mousePosY + CROSS_OFFSETY;
}

void Player::render(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, playerTexture, NULL, &playerSpace);
	SDL_RenderCopy(renderer, crosshairTexture, NULL, &crosshairSpace);
}

void Player::move()
{
	if (dirX >= 1)
	{
		posX += PLAYER_SPEED;
	}
	if (dirX <= -1)
	{
		posX -= PLAYER_SPEED;
	}
	if (dirY >= 1)
	{
		posY += PLAYER_SPEED;
	}
	if (dirY <= -1)
	{
		posY -= PLAYER_SPEED;
	}

	playerSpace.x = posX;
	playerSpace.y = posY;
}

void Player::resetSpeed()
{
	//dirX = 0;
	//dirY = 0;
}