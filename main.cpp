/*
==============================================================
 Filename    :  Main.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.1
 License     :  none.
 Description :  This is the main file from which all code is initiated. This version has code satisfying the requirements of assignment 6.1.
==============================================================
*/
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
#include "Input.h"
#include "ReadCSV.h"


int main(int /*argc*/, char** /*argv*/) {
    std::cout << "HELLO WORLD\n";


    // ***** INITIALISE ALL GLOBAL VARIABLES: *****

    double t0 = 0;
    double dt = 0.01;
    double tEnd = 20;

    double C_dd = 0.1;
    double m_d = 3;
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
    Input input(inCSV.importCSV("InputMatrix.csv")); // import csv with input commands for drone and put it in an Input class object.

        

    // ***** INTEGRATE CURRENT STATESPACE FROM t0 TO tEnd AND SAVE TO A CSV FILE: *****

    x.print(); //print current state vector to terminal
    ForwardEuler droneSimulation(&drone, t0, dt, tEnd); // create ForwardEuler object in preperation for integration
    droneSimulation.integrate(x, input); // integrate system 
    x.print(); //print current (last) states to terminal

    droneSimulation.exportStates("ExportFile.csv"); 

    std::cout << "\n\nCheck root directory for ExportFile.CSV.\nThis file can be opened in in MATLAB using testOutput.m script.\n\n";


    

    return 0;
}



