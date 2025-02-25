/*
==============================================================
 Filename    :  Graphics.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  This file handles the implementation of the Graphics memeber methods.
                Graphics.h handles all rendering a drawing tasks of the program.
                It can be considered a wrapper class of the SDL library.
==============================================================
*/

#include "Graphics.h"

/// <summary>
/// Constructor which initializes all SDL windows, surfaces, textures and renderers to NULL. It also sets the locations of the drone and
/// cargo to the middle of the screen by iniitializion of rectCargo and rectDrone.
/// </summary>
/// <param name="windowSizeX">Desired window size in x-dimension</param>
/// <param name="windowSizeY">Desired window size in y-dimension</param>
Graphics::Graphics(unsigned windowSizeX, unsigned windowSizeY) :
    windowSizeX(windowSizeX), windowSizeY(windowSizeY)
{
    this->window = NULL;
    this->screen = NULL;
    this->textureDrone = NULL;
    this->textureCargo = NULL;
    this->renderer = NULL;
    this->rectDrone = {
        (int)((double)windowSizeX / 2.0 - 280.0 / 2.0 / 2.8),
        (int)((double)windowSizeY / 2.0 - 73.0 / 2.0 / 2.8 - 150.0),
        (int)(280.0 / 2.8),
        (int)(73.0 / 2.8) };

    this->rectCargo = {
        (int)((double)windowSizeX / 2.0 - 102.0 / 2.0 / 2.8),
        (int)((double)windowSizeY / 2.0 - 91.0 / 2.0 / 2.8),
        (int)(108.0 / 2.8),
        (int)(91.0 / 2.8) };

}

/// Destructor
Graphics::~Graphics()
{
    std::cout << "Destroying Graphics object...";
    close();
    std::cout << "\nGraphics object destroyed.";
}


/// <summary>
/// initializes window, renderer, and screen. Also sets the draw color to black.
/// </summary>
/// <returns>bool, true for success, false for error/fail</returns>
bool Graphics::initialize()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("Programming 2 Assignment 6.5", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, windowSizeX, windowSizeY, 0/*SDL_WINDOW_SHOWN*/);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

            }
            //Get window surface
            screen = SDL_GetWindowSurface(window);
        }
    }

    return success;
}


/// <summary>
/// loads bitmaps into the textures. Drone.bmp and Cargo.bmp must be placed inside the root directory. 
/// </summary>
/// <param name="">drawCargo bool. Set to true if you want to draw cargo.</param>
/// <returns>success state</returns>
bool Graphics::loadMedia(bool drawCargo)
{
    // Loading success flag
    bool success = true;

    // Load texture of drone and cargo
    textureDrone = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("drone.bmp"));
    if (drawCargo)
    {
        textureCargo = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("cargo.bmp"));

        if (textureDrone == NULL) //print error to console in case bitmaps are missing from directory
        {
            printf("Unable to load all images %s! SDL Error: %s\n", "drone.bmp", SDL_GetError());
            success = false;
        }

        if (textureCargo == NULL) //print error and return false if bitmaps are missing
        {
            printf("Unable to load all images %s! SDL Error: %s\n", "cargo.bmp", SDL_GetError());
            success = false;
        }
    }

    return success;
}

/// <summary>
/// Does the cleanup needed before quitting. Deallocating surfaces and textures
/// destroys windows and quits SDL subsystem.
/// </summary>
void Graphics::close()
{
    // Deallocate surfaces
    //SDL_FreeSurface(screen); // Should be taken care of by SDL_DestroyWindow
    screen = NULL;

    // Deallocate Textures:
    SDL_DestroyTexture(textureDrone);
    SDL_DestroyTexture(textureCargo);
    textureDrone = NULL;
    textureCargo = NULL;

    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

/// <summary>
/// updates the renderer so show the new positions of the drone.
/// </summary>
void Graphics::updateWindow()
{
    SDL_RenderPresent(renderer); //Update renderer to newest states of drone
    return;
}


/// <summary>
/// Takes care of all the code needed to place the drone and cargo in the desired
/// position. Also sets the desired colors and creates a line to represent the rope
/// inbeween the drone and cargo.
/// </summary>
/// <param name="x">State vector</param>
void Graphics::render(Matrix x)
{
    if (textureCargo != NULL) // If cargo texture is loaded, also draw a line inbetween drone and cargo to represent rope
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); //set line color to white
        SDL_RenderDrawLine(renderer,
            (int)(100.0 * x(1, 1) + (double)windowSizeX / 2.0),
            (int)(-100.0 * x(2, 1) + (double)windowSizeY / 2.0),
            (int)(100.0 * x(6, 1) + (double)windowSizeX / 2.0),
            (int)(-100.0 * x(7, 1) + (double)windowSizeY / 2.0));       // Vectors representing the line
        rectCargo.x = int(100.0 * x(6, 1) + (double)windowSizeX / 2.0 - 102.0 / 2.0 / 2.8);
        rectCargo.y = int(-100.0 * x(7, 1) + (double)windowSizeY / 2.0 - 91.0 / 2.0 / 2.8);
        SDL_RenderCopy(renderer, textureCargo, NULL, &rectCargo);
    }

    rectDrone.x = int(100.0 * x(1, 1) + (double)windowSizeX / 2.0 - 280.0 / 2.0 / 2.8);
    rectDrone.y = int(-100.0 * x(2, 1) + (double)windowSizeY / 2.0 - 73.0 / 2.0 / 2.8);
    SDL_RenderCopyEx(renderer, textureDrone, NULL, &rectDrone, -x(3, 1) * 180 / pi, NULL, SDL_FLIP_NONE);
}

/// <summary>
/// clears renderer of current drawings. Can be used inbetween frames to clear the canvas.
/// </summary>
void Graphics::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

/// <summary>
/// Combines clear(), render(x) and updateWindow() to one callable function.
/// </summary>
/// <param name="x">Matrix x to be put in render(x)</param>
void Graphics::clearRenderUpdate(Matrix x)
{
    clear();
    render(x);
    updateWindow();
}

/// <summary>
/// A version of clearRenderUpdate which also creates a separate thread to run 
/// all of those functions on seperately.
/// </summary>
/// <param name="x">State vector</param>
/// <param name="mtx">Mutual exclusivity to ensure safe data transfer</param>
/// <param name="quit">Quit parameter, can be used to tell the thread to quit</param>
/// <returns>Thread that can be joined inside main</returns>
std::thread Graphics::clearRenderUpdateThread(Matrix& x, std::mutex& mtx, bool& quit)
{
    return std::thread([&] {
        while (!quit)
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            mtx.lock();
            clearRenderUpdate(x);
            mtx.unlock();
            auto t2 = std::chrono::high_resolution_clock::now();
            std::chrono::nanoseconds remaining(16666667 - std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()); // 60Hz --> 1/60*1e9 = 16666667
            if (remaining.count() <= 0) continue;
            std::this_thread::sleep_for(remaining);
        }
    });
}
