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
#include "Functions.h"
#include "Input.h"
#include "ReadCSV.h"
#include "Test.h"

int main(int /*argc*/, char** /*argv*/) {
    std::cout << "HELLO WORLD\n";

    //int nThreads = SDL_GetCPUCount();  //number of threads available on current system for future multithreading implementation


    // ***** INITIALISE ALL GLOBAL VARIABLES: *****

    double t0 = 0;
    double dt = 0.0005;
    double tEnd = 8;

    double m_d = 3;
    double m_c = 2;
    double C_dd = 0.1;
    double C_dc = 0.1;
    double L_rope0 = 1.5;
    double K_rope = 40000;
    double D_rope = 50;
    //double Fx{0};
    //double Fy{0};
    double g = 9.81;


    // ***** INITIALISE MATRICES X, U, A, B, C, D, E FOR STATESPACE: *****

    Matrix x(9, 1, 0.0);
    x(7, 1) = -1.5;
    Matrix u(2, 1, 0.0);

    EntryMatrix A(9, 9, 0.0);
    A(1, 4) = 1.0;
    A(2, 5) = 1.0;
    A(4, 4) = Entry([&x, m_d, C_dd]() {return (1 / m_d) * (-C_dd * sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });
    A(5, 5) = Entry([&x, m_d, C_dd]() {return (1 / m_d) * (-C_dd * sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });
    A(6, 8) = 1;
    A(7, 9) = 1;
    A(8, 8) = Entry([&x, m_c, C_dc]() {return (1 / m_c) * (-C_dc * sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2))); });
    A(9, 9) = Entry([&x, m_c, C_dc]() {return (1 / m_c) * (-C_dc * sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2))); });

    EntryMatrix B(9, 2, 0.0);
    B(3, 2) = 1.0;
    B(4, 1) = Entry([&x, m_d]() {return (1 / m_d) * (-sin(x(3, 1))); });
    B(5, 1) = Entry([&x, m_d]() {return (1 / m_d) * (cos(x(3, 1))); });

    EntryMatrix C(9, 9, 0.0);
    C.diag(1.0);

    EntryMatrix D(9, 2, 0.0);

    EntryMatrix E(9, 1, 0.0);
    E(4, 1) = Entry([&x, m_d, L_rope0, K_rope, D_rope]() {return (K_rope * (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)) - L_rope0) + D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1))) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)))) > 0) ?
        (-1 / m_d) * ((K_rope * (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)) - L_rope0) + D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1))) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2))))) *
            ((x(1, 1) - x(6, 1)) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2))))) : (0); }); // bool ? this : that (conditional ternary operator)
    E(5, 1) = Entry([&x, g, m_d, L_rope0, K_rope, D_rope]() {return (K_rope * (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)) - L_rope0) + D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1))) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)))) > 0) ?
        -g - (1 / m_d) * ((K_rope * (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)) - L_rope0) + D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1))) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2))))) *
            ((x(2, 1) - x(7, 1)) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2))))) : (-g); }); // bool ? this : that (conditional ternary operator)
    E(8, 1) = Entry([&x, m_c, L_rope0, K_rope, D_rope]() {return (K_rope * (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)) - L_rope0) + D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1))) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)))) > 0) ?
        (1 / m_c) * ((K_rope * (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)) - L_rope0) + D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1))) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2))))) *
            ((x(1, 1) - x(6, 1)) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2))))) : (0); }); // bool ? this : that (conditional ternary operator)
    E(9, 1) = Entry([&x, g, m_c, L_rope0, K_rope, D_rope]() {return (K_rope * (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)) - L_rope0) + D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1))) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)))) > 0) ?
        -g + (1 / m_c) * ((K_rope * (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2)) - L_rope0) + D_rope * (((x(1, 1) - x(6, 1)) * (x(4, 1) - x(8, 1)) + (x(2, 1) - x(7, 1)) * (x(5, 1) - x(9, 1))) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2))))) *
            ((x(2, 1) - x(7, 1)) / (sqrt(pow((x(1, 1) - x(6, 1)), 2) + pow(x(2, 1) - x(7, 1), 2))))) : (-g); }); // bool ? this : that (conditional ternary operator)


     //***** INITIALISE STATESPACE WITH PREVIOUSLY MADE MATRICES: *****

    StateSpace drone(A, B, C, D, E);

    // ***** PREPARE INPUT SIGNAL BY IMPORTING A CSV DOCUMENT TO AN INPUT OBJECT: *****


    ReadCSV inCSV; //create object to prepare for csv import
    Input input(inCSV.importCSV("NietOnnodigIngewikkeld.csv"), true); // import csv with input commands for drone and put it in an Input class object.


    // ***** INTEGRATE CURRENT STATESPACE FROM t0 TO tEnd AND SAVE TO A CSV FILE: *****

    x.print(); //print current state vector to terminal
    ForwardEuler droneSimulation(&drone, t0, dt, tEnd); // create ForwardEuler object in preperation for integration
    droneSimulation.integrate(x, input); // integrate system 
    x.print(); //print current (last) states to terminal

    droneSimulation.exportStates("TEST.csv"); 



    //OutputCSV output;
    //output.writeCSV(input.getInputVector(), "spaghettiCodeMuch.csv");


    return 0;
}



