#include <vector>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <string>
#include "Matrix.h"

int main(int /*argc*/, char** /*argv*/) {
    std::cout << "HELLO WORLD\n";

    double C_dd = 1;
    double C_dc = 1;
    double m_d = 1;
    double m_c = 1;
    double Fx = 1;
    double Fy = 1;
    double g = 9.81;

    Matrix x(9, 1, 0);
    Matrix xdot(9, 1, 0);
    Matrix u(2, 1, 0);
    
    Matrix A(9, 9, 0);
    A(1, 4) = 1;
    A(2, 5) = 1;
    A(4, 4) = (1 / m_d) * (-C_dd * sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2)));
    A(5, 5) = (1 / m_d) * (-C_dd * sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2)));
    A(6, 8) = 1;
    A(7, 9) = 1;
    A(8, 8) = (1 / m_c) * (-C_dc * sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2)));
    A(9, 9) = (1 / m_c) * (-C_dc * sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2)));

    Matrix B(9, 2, 0);
    B(3, 2) = 1;
    B(4, 1) = (1 / m_d) * (-sin(x(3, 1)));
    B(5, 1) = (1 / m_d) * (cos(x(3, 1)));

    Matrix E(9, 1, 0);
    E(4, 1) = (1 / m_d) * -Fx;
    E(5, 1) = (1 / m_d) * -Fy - g;
    E(8, 1) = (1 / m_c) * Fx;
    E(9, 1) = (1 / m_c) * Fy - g;

    xdot = (A * x) + (B * u) + E;
    xdot.print();

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