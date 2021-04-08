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
    double dt = 0.01;
    double tEnd = 20;

    double C_dd = 0.1;
    //double C_dc = 1;
    double m_d = 3;
    //double m_c = 1;
    //double Fx = 1;
    //double Fy = 1;
    double g = 9.81;


    // ***** INITIALISE MATRICES X, U, A, B, C, D, E FOR STATESPACE: *****

    Matrix x(5, 1, 0.0);

    //Matrix u(2, 1, 0.0);
    //u(1, 1) = 1;

    EntryMatrix A(5, 5, 0.0);
    A(1, 4) = 1.0;
    A(2, 5) = 1.0;
    A(4, 4) = Entry([&x, m_d, C_dd]() {return (1 / m_d) * (-C_dd * sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });
    //A(5, 1) = Entry([&x, g]() {return (x(1, 1) == 0.0) ? -g : -g / x(1, 1); }); // bool ? this : that (conditional ternary operator)
    A(5, 5) = Entry([&x, m_d, C_dd]() {return (1 / m_d) * (-C_dd * sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });
    ////A(6, 8) = 1;
    ////A(7, 9) = 1;
    ////A(8, 8) = (1 / m_c) * (-C_dc * sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2)));
    ////A(9, 9) = (1 / m_c) * (-C_dc * sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2)));

    EntryMatrix B(5, 2, 0.0);
    B(3, 2) = 1.0;
    B(4, 1) = Entry([&x, m_d]() {return (1 / m_d) * (-sin(x(3, 1))); });
    B(5, 1) = Entry([&x, m_d]() {return (1 / m_d) * (cos(x(3, 1))); });

    EntryMatrix C(5, 5, 0.0);
    C.diag(1);

    EntryMatrix D(5, 2, 0.0);

    Matrix E(5, 1, 0.0);
    E(5, 1) = -g;

    
    // ***** INITIALISE STATESPACE WITH PREVIOUSLY MADE MATRICES: *****

    StateSpace drone(A, B, C, D, E);


    // ***** PREPARE INPUT SIGNAL BY IMPORTING A CSV DOCUMENT TO AN INPUT OBJECT: *****


    ReadCSV inCSV; //create object to prepare for csv import
    Input input(inCSV.importCSV("InputMatrix.csv"), false); // import csv with input commands for drone and put it in an Input class object.

        

    // ***** INTEGRATE CURRENT STATESPACE FROM t0 TO tEnd AND SAVE TO A CSV FILE: *****

    x.print(); //print current state vector to terminal
    ForwardEuler droneSimulation(&drone, t0, dt, tEnd); // create ForwardEuler object in preperation for integration
    droneSimulation.integrate(x, input); // integrate system 
    x.print(); //print current (last) states to terminal

    droneSimulation.exportStates("ExportFiel.csv"); 



    //OutputCSV output;
    //output.writeCSV(input.getInputVector(), "spaghettiCodeMuch.csv");
    

    return 0;
}



