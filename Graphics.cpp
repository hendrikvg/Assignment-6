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
    //this->rectKeyHelp = { 0 , 0, windowSizeX / 10, windowSizeY / 10 };
    //this->white = { 255, 255, 255 };
    
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

bool Graphics::loadMedia()
{
    // Loading success flag
    bool success = true;

    //// Load bitmap of drone and cargo
    //drone = SDL_LoadBMP("drone.bmp");
    //cargo = SDL_LoadBMP("cargo.bmp");

    // Load texture of drone and cargo
    textureDrone = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("drone.bmp"));
    textureCargo = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("cargo.bmp"));

    if (textureDrone == NULL || textureCargo == NULL)
    {
        printf("Unable to load all images %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void Graphics::close()
{
    // Deallocate surfaces
    //SDL_FreeSurface(screen); // Should be taken care of by SDL_DestroyWindow
    //SDL_FreeSurface(drone);
    //SDL_FreeSurface(cargo);
    screen = NULL;
    //drone = NULL;
    //cargo = NULL;

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

void Graphics::blitDrone()
{
    //SDL_BlitSurface(drone, NULL, screen, NULL);
    return;
}

void Graphics::updateWindow()
{
    //SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(renderer);
    return;
}

void Graphics::render(Matrix x)
{
    rectDrone.x = int(100*x(1, 1) + (double)windowSizeX / 2.0 - 140.0/2.0);
    rectDrone.y = int(-100*x(2, 1) + (double)windowSizeY / 2.0 - 37.0);
    //  cargoDestinationRect.x = /*x(6, 1)*/0.0 + (int)windowSizeX / 2 - 54;
    //  cargoDestinationRect.y = /*x(7, 1)*/0.0 + (int)windowSizeY / 2 + 280 - 46;
    //SDL_RenderCopy(renderer, textureDrone, NULL, &rectDrone);
    //SDL_RenderCopy(renderer, textureCargo, NULL, &rectCargo);
    SDL_RenderCopyEx(renderer, textureDrone, NULL, &rectDrone, -x(3, 1)*180/pi, NULL, SDL_FLIP_NONE);
}

void Graphics::clear()
{
    SDL_RenderClear(renderer);
}
