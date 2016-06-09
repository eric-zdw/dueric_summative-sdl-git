#include "TTFTexture.h"

TTFTexture::TTFTexture(int size)
{
	font = TTF_OpenFont("Muli_Regular.ttf", size);
	if (font == NULL)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
	textColor = { 255, 255, 255 };
}

void TTFTexture::CreateText(int x, int y, std::string text, SDL_Renderer* renderer)
{
	surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	renderSpace.x = x;
	renderSpace.y = y;

	SDL_RenderCopy(renderer, texture, NULL, &renderSpace);
}

void TTFTexture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	textColor = { r, g, b };
}