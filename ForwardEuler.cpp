/*
==============================================================
 Filename    :  ForwardEuler.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.1
 License     :  none.
 Description :  Implementation of the ForwardEuler.h member methods.
                Forwad Euler integration scheme is handled by this class. It takes the state space,
                and other parameters and returns the state vector of the next time step. Inherits from
                Simulator class.
==============================================================
*/

#include "ForwardEuler.h"


/// <summary>
/// Constructor with all required parameters to integrate.
/// </summary>
/// <param name="system">statespace of the system</param>
/// <param name="t0">initial time</param>
/// <param name="td">time step</param>
/// <param name="tEnd">final time</param>
ForwardEuler::ForwardEuler(StateSpace *system, double t0, double dt, double tEnd = 0)
{
    this->system = system;
    this->t0 = t0;
    this->dt = dt;
    this->tEnd = tEnd;
    this->t = 0;
}

ForwardEuler::~ForwardEuler(){ //destructor
}

/// <summary>
/// Integrates this objects dynamic system from t to tEnd with stepsize dt.
/// </summary>
/// <param name="x">The current state of the dynamic system of type Matrix.</param>
/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
void ForwardEuler::integrate(Matrix& x, Input u)
{
    if (t == 0)
    {
        for (t = t0; t < tEnd; t += dt)
        {
            x = x + system->calculateXdot(x, u.getU(t)) * dt;
            Matrix y = system->calculateY(x, u.getU(t));
            saveState(t, x, y);
        }
    }
    else
    {
        for (t; t < tEnd; t += dt)
        {
            x = x + system->calculateXdot(x, u.getU(t)) * dt;
            Matrix y = system->calculateY(x, u.getU(t));
            saveState(t, x, y);
        }
    }
    // exportStates();  // done inside main
}

/// This is a bit of a legacy function, should be reworked/removed
/// <summary>
/// Integrates this objects dynamic system from its predefined start to final time, while resetting the current state to some initial state.
/// </summary>
/// <param name="x">The current state of the dynamic system of type Matrix.</param>
/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
/// <param name="x0">The initial state that should be integrated from.</param>
void ForwardEuler::integrate(Matrix& x, Input u, Matrix x0)
{
    if (x.getRows() == x0.getRows() && x.getColumns() == x0.getColumns())
    {
        x = x0;
        integrate(x, u);
    }
}