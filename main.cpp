#include <vector>
#include <iostream>
#include <SDL.h>
#include <string>
#include "Matrix.h"

int main(int /*argc*/, char** /*argv*/) {
    unsigned rows{ 2 };
    unsigned columns{ 2 };
    std::cout << "HELLO WORLD\n";
    Matrix A(rows, columns, (double)1);
    Matrix B(rows, columns, (double)2);
    Matrix C(rows, columns, (double)0);
    A(0, 0) = 1;
    A(0, 1) = 3;
    A(1, 0) = 4;
    A(1, 1) = 2;
    C = A * A;
    C.showMatrix();


    //SDL_Window* window = nullptr;
    //SDL_Renderer* renderer = nullptr;

    //SDL_Init(SDL_INIT_EVERYTHING);

    //// Create a Window in the middle of the screen
    //window = SDL_CreateWindow("Drone Simulation", SDL_WINDOWPOS_CENTERED,
    //    SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);

    //renderer = SDL_CreateRenderer(window, -1,
    //    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //system("pause");
    //SDL_Quit();
    return 0;
}