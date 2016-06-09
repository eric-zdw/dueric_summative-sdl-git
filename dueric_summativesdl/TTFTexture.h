#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class TTFTexture {
private:
	SDL_Texture* texture;
	int width;
	int height;
	TTF_Font *font = NULL;
	SDL_Color textColor;
	SDL_Surface *surface;
	SDL_Rect renderSpace;
public:
	TTFTexture(int);

	void CreateText(int, int, std::string, SDL_Renderer*);
	void setColor(Uint8, Uint8, Uint8);


};