/*
==============================================================
 Filename    :  Main.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  This is the main file from which all code is initiated. This version has code satisfying the requirements of assignments 6.1 to 6.5. 
==============================================================
*/

#include <vector>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
//#include <chrono>
#include <thread>
#include <mutex>
#include "Matrix.h"
#include "StateSpace.h"
#include "Simulator.h"
#include "Entry.h"
#include "EntryMatrix.h"
#include "ForwardEuler.h"
#include "RungeKutta.h"
#include "Functions.h"
#include "Input.h"
#include "CommonInput.h"
#include "KeyboardInput.h"
#include "ReadCSV.h"
#include "Functions.h"
#include "Graphics.h"

int main(int /*argc*/, char** /*argv*/) {
    std::cout << "HELLO WORLD\n";

    // ***** INITIALISE ALL GLOBAL VARIABLES: *****
    double dt = 0.01; /// Time step for integration [s], note that this gets modified for...
    /// different integration methods and dynamical systems.
    const double m_d = 3; // Mass of drone [kg]
    const double m_c = 2; // Mass of cargo [kg]
    const double C_dd = 0.1; // Drag constant of drone [Ns^2/m^2]
    const double C_dc = 0.1; // Drag constant of cargo [Ns^2/m^2]
    const double L_rope0 = 1.5; // Length of the rope [m]
    const double K_rope = 40000; // Stiffness of the rope [N/m]
    const double D_rope = 50; // Damping of the rope [Ns/m]
    const double g = 9.81; // Gravitational acceleration
    const int windowSizeX = 1000; // Horizontal resolution
    const int windowSizeY = 800; // Vertical resolution
    const int FPS = 60; // 60 FPS, as running less on a PC should be a crime.
    const Uint8* keystates = SDL_GetKeyboardState(NULL); // Argument is the number of keys available, since we don't care it's set to NULL.
    Graphics graphics(windowSizeX, windowSizeY);
    double inputAngularVelocity = 0.8;


    // ***** DECLARE REMAINING GLOBAL VARIABLES: *****

    double t0;
    double t;
    double tEnd;
    Matrix x;
    Matrix x0;
    Input input;
    KeyboardInput keyboardInput;
    EntryMatrix A;
    EntryMatrix B;
    EntryMatrix C;
    EntryMatrix D;
    EntryMatrix E;

    CommonInput* inputMethod;
    Simulator* systemSimulation;
    ReadCSV inCSV; //create object to prepare for csv import
    SDL_Event event;

    bool quit = false;
    bool visualization;
    bool drawCargo;
    double inputThrust;
    bool manualControl;

    std::mutex mtx;

    std::cout << "\nWelcome to Assignment 6, do you want a visual simulation?:\n";
    std::cout << "Enter 0 to quit the program\n";
    std::cout << "Enter 1 for visual simulation\n";
    std::cout << "Enter 2 for only CSV output\n";

    switch (getInteger(0, 2))
    {
    case 1:
    {
        visualization = true;
        break;
    }
    case 2:
    {
        visualization = false;
        break;
    }
    default:
        std::cout << "Quitting program...";
        exit(EXIT_SUCCESS); // exits the program with cleaning up.
    }

    std::cout << "\nWelcome to Assignment 6, choose which system you want to model:\n";
    std::cout << "Enter 0 to quit the program\n";
    std::cout << "Enter 1 for the system of a drone\n";
    std::cout << "Enter 2 for the system of a drone with cargo\n";

    switch (getInteger(0, 2))
    {
    case 1:
        drawCargo = false;
        t0 = 0;
        t = t0;
        tEnd = 14;
        x = Matrix(5, 1, 0.0);
        x0 = x;

        A = EntryMatrix(5, 5, 0.0);
        A(1, 4) = 1.0;
        A(2, 5) = 1.0;
        A(4, 4) = Entry([&x, m_d, C_dd]() {return (-C_dd / m_d) * (sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });
        A(5, 5) = Entry([&x, m_d, C_dd]() {return (-C_dd / m_d) * (sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });

        B = EntryMatrix(5, 2, 0.0);
        B(3, 2) = 1.0;
        B(4, 1) = Entry([&x, m_d]() {return ((-sin(x(3, 1))) / m_d); });
        B(5, 1) = Entry([&x, m_d]() {return ((cos(x(3, 1))) / m_d); });

        C = EntryMatrix(5, 5, 0.0);
        C.diag(1);

        D = EntryMatrix(5, 2, 0.0);

        E = EntryMatrix(5, 1, 0.0);
        E(5, 1) = -g;

        inputThrust = 50.0;

        input = Input(inCSV.importCSV("DroneInput.csv"), false); // import csv with input commands for drone and put it in an Input class object.
        break;

    case 2:
        drawCargo = true;
        t0 = 0;
        t = t0;
        tEnd = 16;
        dt /= 20; // Note: dt becomes 20 times as small to avoid instability.
        x = Matrix(9, 1, 0.0);
        x(2, 1) = 1.5;
        x0 = x;

        A = EntryMatrix(9, 9, 0.0);
        A(1, 4) = 1.0;
        A(2, 5) = 1.0;
        A(4, 4) = Entry([&x, m_d, C_dd]() {return (-C_dd / m_d) * (sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });
        A(5, 5) = Entry([&x, m_d, C_dd]() {return (-C_dd / m_d) * (sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });
        A(6, 8) = 1.0;
        A(7, 9) = 1.0;
        A(8, 8) = Entry([&x, m_c, C_dc]() {return (-C_dc / m_c) * (sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2))); });
        A(9, 9) = Entry([&x, m_c, C_dc]() {return (-C_dc / m_c) * (sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2))); });

        B = EntryMatrix(9, 2, 0.0);
        B(3, 2) = 1.0;
        B(4, 1) = Entry([&x, m_d]() {return ((-sin(x(3, 1))) / m_d); });
        B(5, 1) = Entry([&x, m_d]() {return ((cos(x(3, 1))) / m_d); });

        C = EntryMatrix(9, 9, 0.0);
        C.diag(1.0);

        D = EntryMatrix(9, 2, 0.0);

        E = EntryMatrix(9, 1, 0.0);
        E(4, 1) = Entry([&x, m_d, L_rope0, K_rope, D_rope]()
            {double L_rope = sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)); 
            double F_rope = K_rope * (L_rope - L_rope0) + 
            D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1)))
                / L_rope);
        return (F_rope > 0)
            ? (-F_rope * ((x(1, 1) - x(6, 1)) / L_rope) / m_d)
            : (0); }); // bool ? this : that (conditional ternary operator)

        E(5, 1) = Entry([&x, g, m_d, L_rope0, K_rope, D_rope]()
            {double L_rope = sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2));
            double F_rope = K_rope * (L_rope - L_rope0) +
            D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1)))
                / L_rope);
        return (F_rope > 0)
            ? ((-F_rope * ((x(2, 1) - x(7, 1)) / L_rope) / m_d) - g)
            : (-g); }); // bool ? this : that (conditional ternary operator)

        E(8, 1) = Entry([&x, m_c, L_rope0, K_rope, D_rope]()
            {double L_rope = sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2));
            double F_rope = K_rope * (L_rope - L_rope0) +
            D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1)))
                / L_rope);
        return (F_rope > 0)
            ? (F_rope * ((x(1, 1) - x(6, 1)) / L_rope) / m_c)
            : (0); }); // bool ? this : that (conditional ternary operator)

        E(9, 1) = Entry([&x, g, m_c, L_rope0, K_rope, D_rope]()
            {double L_rope = sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2));
            double F_rope = K_rope * (L_rope - L_rope0) +
            D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1)))
                / L_rope);
        return (F_rope > 0)
            ? ((F_rope * ((x(2, 1) - x(7, 1)) / L_rope) / m_c) - g)
            : (-g); }); // bool ? this : that (conditional ternary operator)

        inputThrust = 80.0;

        input = Input(inCSV.importCSV("CargoDroneInput.csv"), false); // import csv with input commands for drone and put it in an Input class object.
        break;

    default:
        std::cout << "Quitting program...";
        exit(EXIT_SUCCESS); // exits the program with cleaning up.
    }

    std::cout << "\nSystem equations: xDot = Ax + Bu + E and y = Cx + Du\n";
    std::cout << "System initialized with:\nx0 =";
    x.print();
    std::cout << "A =";
    A.print();
    std::cout << "B =";
    B.print();
    std::cout << "C =";
    C.print();
    std::cout << "D =";
    D.print();
    std::cout << "E =";
    E.print();
    std::cout << "Note that the matrix entries may be state dependent, and thus change during the simulation.";

    StateSpace dynamicSystem(A, B, C, D, E); // Initialize state-space system
    ForwardEuler forwardEulerIntegrator(&dynamicSystem, t0, dt, tEnd); 
    RungeKutta rungeKuttaIntegrator(&dynamicSystem, t0, dt*20, tEnd); // Note: dt becomes 20 times larger, as RungeKutta-4 is more stable.

    std::cout << "\nChoose which integrator you would like to simulate with:\n";
    std::cout << "Enter 0 to quit the program\n";
    std::cout << "Enter 1 for Euler forward\n";
    std::cout << "Enter 2 for Runge-Kutta 4\n";

    switch (getInteger(0, 2))
    {
    case 1:
    {
        systemSimulation = &forwardEulerIntegrator;
        break;
    }
    case 2:
    {
        dt *= 20; // Note: dt becomes 20 times larger.
        systemSimulation = &rungeKuttaIntegrator;
        break;
    }
    default:
        std::cout << "Quitting program...";
        exit(EXIT_SUCCESS); // exits the program with cleaning up.
    }

    std::cout << "\n\nCONTROL SCHEME:\n";
    std::cout << "ESCAPE: \t Quit simulation\n";
    std::cout << "ARROW UP: \t Thrusters On \n";
    std::cout << "ARROW RIGHT: \t Rotate right\n";
    std::cout << "ARROW LEFT: \t Rotate left\n";
    std::cout << "SPACE: \t\t Reset drone\n\n";

    std::cout << "\nChoose control input method:\n";
    std::cout << "Enter 0 to quit the program\n";
    std::cout << "Enter 1 for Prescribed Input (demo)\n";
    std::cout << "Enter 2 for Manual Input Control (visual mode only)\n";


    switch (getInteger(0, 2))
    {
    case 1:
    {
        inputMethod = &input;
        manualControl = false;
        std::cout << "\nDemo mode. Loading prescribed control input.\n";
        break;
    }
    case 2:
    {
        inputMethod = &keyboardInput;
        manualControl = true;

        std::cout << "\nManual control selected.\n\n";

        break;
    }
    default:
    {
        std::cout << "Quitting program...";
        exit(EXIT_SUCCESS); // exits the program with cleaning up.
    }
    }

        // ***** SDL WINDOW AND MACHINE: *****

    if (visualization)
    {
        if (graphics.initialize())
        {
            std::cout << "\nGraphics initialized.";
        }
        if (graphics.loadMedia(drawCargo))
        {
            std::cout << "\nMedia has been loaded.\n";
        }

        std::thread thread1 = systemSimulation->integrateThread(x, *inputMethod, t, dt, FPS, mtx, quit); // Create integration thread that runs at 100Hz.
        std::thread thread2 = graphics.clearRenderUpdateThread(x, mtx, quit); // Create graphics thread that runs at 60Hz.
        Uint32 timeout_ms = SDL_GetTicks() + 1000 / FPS;

        while (!quit)
        {
            t += 1.0 / FPS;
                     
            while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout_ms)) {
                while (SDL_PollEvent(&event) != 0)
                {   
                    if (manualControl == true) {
                        keyboardInput.scanKeys(quit, inputAngularVelocity, inputThrust, x0, x, event); // Register keyboard inputs.
                    }
                    if (event.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
            }
            if (t > tEnd && manualControl == false) {
                quit = true;
            }
            timeout_ms += 1000 / FPS;
        }
        // join threads...
        thread1.join();
        thread2.join();
    }
    else
    {
        std::cout << "Starting simulation with:\n";
        std::cout << "t0\t=\t" << t0;
        std::cout << "\ndt\t=\t" << dt;
        std::cout << "\ntEnd\t=\t" << tEnd;
        std::cout << "\nIntegrating... please be patient";
        systemSimulation->integrate(x, input, t0, dt, tEnd); // integrate system
    }

    std::cout << "\nExporting states as CSV file... ";

    systemSimulation->exportStates("TEST.csv");

    std::cout << "Exporting done! \nExiting program...";

    std::cout << "\n";

    return 0;
}