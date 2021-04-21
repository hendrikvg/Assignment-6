/*
==============================================================
 Filename    :  ForwardEuler.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.4
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
ForwardEuler::ForwardEuler(StateSpace* system, double t0, double dt, double tEnd = 0)
{
    this->system = system;
    this->t0 = t0;
    this->dt = dt;
    this->tEnd = tEnd;
    this->t = t0;
}

///Destructor
ForwardEuler::~ForwardEuler()
{
    std::cout << "Destorying ForwardEuler object. Also destorying parent object: ";
}


/// <summary>
/// Integrates this objects dynamic system from t to tEnd with stepsize dt.
/// </summary>
/// <param name="x">The current state of the dynamic system of type Matrix.</param>
/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
/// <param name="t">The current time.</param>
/// <param name="dt">The time step.</param>
/// <param name="tEnd">The end time for integration.</param>
void ForwardEuler::integrate(Matrix& x, CommonInput& u, double t, double dt, double tEnd)
{
    if (tEnd - t < dt)
    {
        dt = tEnd - t;
    }

    saveState(t, x, system->calculateY(x, u.getU(t)));

    for (t; t < tEnd; t += dt)
    {
        x = x + system->calculateXdot(x, u.getU(t)) * dt;

        Matrix y = system->calculateY(x, u.getU(t));

        saveState(t + dt, x, y);
    }
    this->t = t;
}


/// <summary>
/// Integrates this objects dynamic system from its predefined start to final time.
/// </summary>
/// <param name="x">The current state of the dynamic system of type Matrix.</param>
/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
void ForwardEuler::integrate(Matrix& x, CommonInput& u)
{
    integrate(x, u, this->t, this->dt, this->tEnd);
}


/// This is a bit of a legacy function, should be reworked/removed
/// <summary>
/// Integrates this objects dynamic system from its predefined start to final time, while resetting the current state to some initial state.
/// </summary>
/// <param name="x">The current state of the dynamic system of type Matrix.</param>
/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
/// <param name="x0">The initial state that should be integrated from.</param>
void ForwardEuler::integrate(Matrix& x, CommonInput& u, Matrix x0)
{
    if (x.getRows() == x0.getRows() && x.getColumns() == x0.getColumns())
    {
        x = x0;
        integrate(x, u);
    }
}