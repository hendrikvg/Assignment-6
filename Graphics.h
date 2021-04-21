/*
==============================================================
 Filename    :  Graphics.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.4
 License     :  none.
 Description :  Graphics.h handles all rendering a drawing tasks of the program.
				It can be considered a wrapper class of the SDL library.
				This entire class is heavily inspired by the tutorial of lazyfoo:
				https://lazyfoo.net/tutorials/SDL/
==============================================================
*/

#ifndef SRC_GRAPHICS_H
#define SRC_GRAPHICS_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
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
	/// <summary>
	/// Constructor which initializes all SDL windows, surfaces, textures and renderers to NULL. It also sets the locations of the drone and
	/// cargo to the middle of the screen by iniitializion of rectCargo and rectDrone.
	/// </summary>
	/// <param name="windowSizeX">Desired window size in x-dimension</param>
	/// <param name="windowSizeY">Desired window size in y-dimension</param>
	Graphics(unsigned windowSizeX, unsigned windowSizeY);

	/// Destructor
	~Graphics();

	/// <summary>
	/// initializes window, renderer, and screen. Also sets the draw color to black.
	/// </summary>
	/// <returns>bool, true for success, false for error/fail</returns>
	bool initialize();

	/// <summary>
	/// loads bitmaps into the textures. Drone.bmp and Cargo.bmp must be placed inside the root directory. 
	/// </summary>
	/// <param name="">drawCargo bool. Set to true if you want to draw cargo.</param>
	/// <returns>success state</returns>
	bool loadMedia(bool);

	/// <summary>
	/// Does the cleanup needed before quitting. Deallocating surfaces and textures
	/// destroys windows and quits SDL subsystem.
	/// </summary>
	void close();

	/// <summary>
	/// updates the renderer so show the new positions of the drone.
	/// </summary>
	void updateWindow();

	/// <summary>
	/// Takes care of all the code needed to place the drone and cargo in the desired
	/// position. Also sets the desired colors and creates a line to represent the rope
	/// inbeween the drone and cargo.
	/// </summary>
	/// <param name="x">State vector</param>
	void render(Matrix x);

	/// <summary>
	/// clears renderer of current drawings. Can be used inbetween frames to clear the canvas.
	/// </summary>
	void clear();
};

#endif // SRC_GRAPHICS_H