/// This entire class is heavily inspired by the tutorial of lazyfoo: https://lazyfoo.net/tutorials/SDL/
#ifndef SRC_GRAPHICS_H
#define SRC_GRAPHICS_H

#include <iostream>
#include <SDL.h>
#include <string>
#include "Matrix.h"

class Graphics
{
private:
	const unsigned int windowSizeX;
	const unsigned int windowSizeY;
	SDL_Window* window;
	SDL_Surface* screen;
	//SDL_Surface* drone;
	//SDL_Surface* cargo;
	SDL_Renderer* renderer;
	SDL_Texture* textureDrone;
	SDL_Texture* textureCargo;
	SDL_Rect rectDrone;
	SDL_Rect rectCargo;

public:
	Graphics(unsigned windowSizeX, unsigned windowSizeY);
	bool initialize();
	bool loadMedia();
	void close();
	void blitDrone();
	void updateWindow();
	void render(Matrix x);
	void clear();
};

#endif // SRC_GRAPHICS_H