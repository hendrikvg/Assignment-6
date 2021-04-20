/// This entire class is heavily inspired by the tutorial of lazyfoo: https://lazyfoo.net/tutorials/SDL/
#ifndef SRC_GRAPHICS_H
#define SRC_GRAPHICS_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <thread>
#include <mutex>
#include "Matrix.h"

class Graphics
{
private:
	const double pi = 3.1415926535897932384626433;
	const unsigned int windowSizeX;
	const unsigned int windowSizeY;
	SDL_Window* window;
	SDL_Surface* screen;
	SDL_Renderer* renderer;
	SDL_Texture* textureDrone;
	SDL_Texture* textureCargo;
	SDL_Rect rectDrone;
	SDL_Rect rectCargo;
public:
	Graphics(unsigned windowSizeX, unsigned windowSizeY);
	~Graphics();
	bool initialize();
	bool loadMedia(bool);
	void close();
	void updateWindow();
	void render(Matrix x);
	void clear();
	void clearRenderUpdate(Matrix x);
	std::thread clearRenderUpdateThread(Matrix& x, std::mutex& mtx, bool& quit);
};

#endif // SRC_GRAPHICS_H