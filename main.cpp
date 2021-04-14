#include <vector>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <string>
#include "Matrix.h"
#include "StateSpace.h"
#include "Simulator.h"
#include "Entry.h"
#include "EntryMatrix.h"
#include "ForwardEuler.h"
#include "RungeKutta.h"
#include "Functions.h"
#include "Input.h"
#include "ReadCSV.h"
#include "Functions.h"


int main(int /*argc*/, char** /*argv*/) {
    std::cout << "HELLO WORLD\n";

    // ***** INITIALISE ALL GLOBAL VARIABLES: *****
    double t0 = 0;
    double dt = 0.005;
    double tEnd = 8;

    double m_d = 3;
    double m_c = 2;
    double C_dd = 0.1;
    double C_dc = 0.1;
    double L_rope0 = 1.5;
    double K_rope = 40000;
    double D_rope = 50;
    double g = 9.81;

    // ***** TEST: *****

    bool test = true;
    Matrix x;
    Input input;
    EntryMatrix A;
    EntryMatrix B;
    EntryMatrix C;
    EntryMatrix D;
    EntryMatrix E;

    Simulator *systemSimulation;
    ReadCSV inCSV; //create object to prepare for csv import

    std::cout << "\nWelcome to Assignment 6, choose which system you want to model:\n";
    std::cout << "Enter 0 to quit the program\n";
    std::cout << "Enter 1 for the system of a drone\n";
    std::cout << "Enter 2 for the system of a drone with cargo\n";
    switch (getInteger(0, 2))
    {
    case 1:
        x = Matrix(5, 1, 0.0);

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

        input = Input(inCSV.importCSV("DroneInput.csv"), false); // import csv with input commands for drone and put it in an Input class object.
        break;

    case 2:
        x = Matrix(9, 1, 0.0);
        x(2, 1) = 1.5;

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

        input = Input(inCSV.importCSV("CargoDroneInput.csv"), false); // import csv with input commands for drone and put it in an Input class object.
        break;

    default:
        std::cout << "Quitting program...";
        exit(EXIT_SUCCESS); // exits the program with cleaning up.
    }

    std::cout << "System initialized with:\nx =";
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

    StateSpace system(A, B, C, D, E); // Initiate state space system
    ForwardEuler forwardEulerIntegrator(&system, t0, dt/20, tEnd); // Note: dt becomes 20 times as small to avoid instability.
    RungeKutta rungeKuttaIntegrator(&system, t0, dt, tEnd);

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
        systemSimulation = &rungeKuttaIntegrator;
        break;
    }
    default:
        std::cout << "Quitting program...";
        exit(EXIT_SUCCESS); // exits the program with cleaning up.
    }

    systemSimulation->integrate(x, input); // integrate system
    systemSimulation->exportStates("TEST.csv");

    return 0;
}