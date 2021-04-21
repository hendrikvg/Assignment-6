/*
==============================================================
 Filename    :  Graphics.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
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
#include <thread>
#include <mutex>
#include "Matrix.h"

class Graphics
{
private:
	const double pi = 3.1415926535897932384626433;	//defining PI for later usage inside this class.
	const unsigned int windowSizeX;					//Size of SDL window in X direction.
	const unsigned int windowSizeY;					//Size of SDL window in Y direction.
	SDL_Window* window;								//SDL window reference object
	SDL_Surface* screen;							//SDL surface reference object, stores bitmap close to cpu
	SDL_Renderer* renderer;							//SDL renderer will take care of the rendering inside the window
	SDL_Texture* textureDrone;						//SDL texture stores the bitmap close to the GPU
	SDL_Texture* textureCargo;						//SDL texture stores the bitmap close to the GPU
	SDL_Rect rectDrone;								//SDL rect stores information on location and size of bitmap render
	SDL_Rect rectCargo;								//SDL rect stores information on location and size of bitmap render
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

	/// <summary>
	/// Combines clear(), render(x) and updateWindow() to one callable function.
	/// </summary>
	/// <param name="x">Matrix x to be put in render(x)</param>
	void clearRenderUpdate(Matrix x);

	/// <summary>
	/// A version of clearRenderUpdate which also creates a separate thread to run 
	/// all of those functions on seperately.
	/// </summary>
	/// <param name="x">State vector</param>
	/// <param name="mtx">Mutual exclusivity to ensure safe data transfer</param>
	/// <param name="quit">Quit parameter, can be used to tell the thread to quit</param>
	/// <returns>Thread that can be joined inside main</returns>
	std::thread clearRenderUpdateThread(Matrix& x, std::mutex& mtx, bool& quit);
};

#endif // SRC_GRAPHICS_H