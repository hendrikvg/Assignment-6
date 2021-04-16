#include "Graphics.h"

Graphics::Graphics(unsigned windowSizeX, unsigned windowSizeY) : 
    windowSizeX(windowSizeX), windowSizeY(windowSizeY)
{
    this->window = NULL;
    this->screen = NULL;
    //this->drone = NULL;
    //this->cargo = NULL;
    this->textureDrone = NULL;
    this->textureCargo = NULL;
    this->rectDrone = { (int)(windowSizeX / 2 - 140.0/2.0), (int)(windowSizeY / 2 - 37), (int)(280.0/2.8), (int)(73.0/2.8) };
    this->rectCargo = { (int)windowSizeX / 2 - 54, (int)windowSizeY / 2 + 280 - 46, 108, 91 };
    
}

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
        window = SDL_CreateWindow("Programming 2 Assignment 6.3", SDL_WINDOWPOS_UNDEFINED, 
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

bool Graphics::loadMedia(bool drawCargo)
{
    // Loading success flag
    bool success = true;

    // Load texture of drone and cargo
    textureDrone = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("drone.bmp"));
    if (drawCargo)
    {
        textureCargo = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("cargo.bmp"));

        if (textureDrone == NULL)
        {
            printf("Unable to load all images %s! SDL Error: %s\n", "drone.bmp", SDL_GetError());
            success = false;
        }

        if (textureCargo == NULL)
        {
            printf("Unable to load all images %s! SDL Error: %s\n", "cargo.bmp", SDL_GetError());
            success = false;
        }
    }

    return success;
}

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

void Graphics::updateWindow()
{
    SDL_RenderPresent(renderer);
    return;
}

void Graphics::render(Matrix x)
{
    rectDrone.x = int(100.0 * x(1, 1) + (double)windowSizeX / 2.0 - 140.0 / 2.0);
    rectDrone.y = int(-100.0 * x(2, 1) + (double)windowSizeY / 2.0 - 37.0);
    SDL_RenderCopyEx(renderer, textureDrone, NULL, &rectDrone, -x(3, 1) * 180 / pi, NULL, SDL_FLIP_NONE);

    if (textureCargo != NULL)
    {
        rectCargo.x = int(100.0 * x(6, 1) + (double)windowSizeX / 2.0 - 54.0);
        rectCargo.y = int(-100.0 * x(7, 1) + (double)windowSizeY / 2.0 + 280.0 - 46.0);
    }
    //SDL_RenderCopy(renderer, textureDrone, NULL, &rectDrone);
    //SDL_RenderCopy(renderer, textureCargo, NULL, &rectCargo);
    
}

void Graphics::clear()
{
    SDL_RenderClear(renderer);
}
