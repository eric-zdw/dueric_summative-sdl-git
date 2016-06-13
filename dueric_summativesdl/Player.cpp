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

void Player::readInput(SDL_Event& e, ProjectileSystem ps, SDL_Renderer *renderer)
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

	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			Shoot(ps, renderer);
		}
	}
}

void Player::GetMousePosition(int offsetX, int offsetY)
{
	SDL_GetMouseState(&mouseRenderX, &mouseRenderY);

	mousePosX = mouseRenderX - offsetX;
	mousePosY = mouseRenderY - offsetY;
}

void Player::render(SDL_Renderer *renderer, int offsetX, int offsetY)
{
	playerSpace.x = posX + offsetX + PLAYER_OFFSETX;
	playerSpace.y = posY + offsetY + PLAYER_OFFSETY;
	crosshairSpace.x = mouseRenderX + CROSS_OFFSETX;
	crosshairSpace.y = mouseRenderY + CROSS_OFFSETY;

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
}

void Player::resetSpeed()
{
	//dirX = 0;
	//dirY = 0;
}

int Player::getX()
{
	return posX;
}

int Player::getY()
{
	return posY;
}

int Player::getCrossX()
{
	return mousePosX;
}

int Player::getCrossY()
{
	return mousePosY;
}

void Player::Shoot(ProjectileSystem ps, SDL_Renderer *renderer)
{
	ps.CreatePlayerProj(posX, posY, mousePosX, mousePosY, PROJECTILE_SPEED, renderer);
}