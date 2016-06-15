#include "Player.h"
#include <iostream>

//Player class;
//controlled with WASD and mouse.
//Can shoot projectiles by holding mouse button.
//When destroyed, respawns in a random location after
//100 frames. Enemies spawn slower after death.
//Player class also contains code for the mouse
//crosshair (and crosshair rotation).

Player::Player(SDL_Renderer *renderer)
{
	posX = rand() % 2048;
	posY = rand() % 1024;
	dirX = 0;
	dirY = 0;
	accX = 0;
	accY = 0;

	cursorRotation = 0;

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

	PROJECTILE_SPEED = 32.f;

	isShooting = false;
	shootDelay = 0;

	collisionBox.h = PLAYER_HEIGHT;
	collisionBox.w = PLAYER_WIDTH;

	isActive = true;
	deathTimer = DEATH_TIMER;
}

void Player::readInput(SDL_Event& e, ProjectileSystem ps, SDL_Renderer *renderer)
{
	if (isActive == true)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				dirY += -1;
				break;
			case SDLK_s:
				dirY += 1;
				break;
			case SDLK_a:
				dirX += -1;
				break;
			case SDLK_d:
				dirX += 1;
				break;
			}
		}

		if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				dirY -= -1;
				break;
			case SDLK_s:
				dirY -= 1;
				break;
			case SDLK_a:
				dirX -= -1;
				break;
			case SDLK_d:
				dirX -= 1;
				break;
			}
		}

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				isShooting = true;
			}
		}

		if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				isShooting = false;
				shootDelay = 0;
			}
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
	SDL_RenderCopyEx(renderer, crosshairTexture, NULL, &crosshairSpace, cursorRotation, NULL, SDL_FLIP_NONE);
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

	if (posX < 0)
		posX = 0;
	if (posX > 2048)
		posX = 2048;
	if (posY < 0)
		posY = 0;
	if (posY > 1024)
		posY = 1024;

	collisionBox.x = posX - (PLAYER_WIDTH / 2);
	collisionBox.y = posY - (PLAYER_HEIGHT / 2);
}

void Player::resetSpeed()
{
	dirX = 0;
	dirY = 0;
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

void Player::cursorRotate()
{
	if (cursorRotation >= 360)
		cursorRotation = 0;
	cursorRotation += 3;
}

//Run every frame when mouse is held.
int Player::ShootMechanism()
{
	if (shootDelay != 0)
	{
		shootDelay -= 1;
		return -1;
	}
	else if (shootDelay <= 0)
	{
		shootDelay = FIRE_RATE;
		return 1;
	}
}

bool Player::Shooting()
{
	return isShooting;
}

SDL_Rect Player::getCollision()
{
	return collisionBox;
}

bool &Player::getActive()
{
	return isActive;
}

//Run every frame when player is inactive.
void Player::countTimer()
{
	if(deathTimer > 0)
		deathTimer--;
	else
	{
		posX = rand() % 2048;
		posY = rand() % 1024;
		isActive = true;
		deathTimer = DEATH_TIMER;
	}
	
}