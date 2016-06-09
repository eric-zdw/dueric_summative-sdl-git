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

public:
	TTFTexture();
	~TTFTexture();
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	bool loadFile(std::string path);
	bool loadText(std::string text, SDL_Color textColor);

	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);

	int getWidth();
	int getHeight();


};