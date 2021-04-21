/*
==============================================================
 Filename    :  RungeKutta.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.4
 License     :  none.
 Description :  Implementation of the RungeKutta.h member methods.
                Runge Kutta integration scheme is handled by this class. It takes the state space,
                and other parameters and returns the state vector of the next time step. Inherits from
                Simulator class. The results are an improvement on the Forward Euler scheme, as it provides
                a better approximation of the exact solution.
==============================================================
*/

#include "RungeKutta.h"

/// <summary>
/// Constructor with all required parameters to integrate.
/// </summary>
/// <param name="system">statespace of the system</param>
/// <param name="t0">initial time</param>
/// <param name="td">time step</param>
/// <param name="tEnd">final time</param>
RungeKutta::RungeKutta(StateSpace* system, double t0, double dt, double tEnd = 0) {
    this->system = system;
    this->t0 = t0;
    this->dt = dt;
    this->tEnd = tEnd;
    this->t = t0;
}

RungeKutta::~RungeKutta()
{
    std::cout << "Destorying RungeKutta object. Also destorying parent object: ";
}

/// <summary>
/// Integrates this objects dynamic system from t to tEnd with stepsize dt.
/// </summary>
/// <param name="x">The current state of the dynamic system of type Matrix.</param>
/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
/// <param name="t">The current time.</param>
/// <param name="dt">The time step.</param>
/// <param name="tEnd">The end time for integration.</param>
void RungeKutta::integrate(Matrix& x, CommonInput& u, double t, double dt, double tEnd)
{
    if (tEnd - t < dt) /// If the time step is larger that the time between the start and
        /// end time...
    {
        dt = tEnd - t; /// Limit the time step to the time between the start and end time.
    }

    saveState(t, x, system->calculateY(x, u.getU(t))); /// Save initial state.

    for (t; t < tEnd; t += dt) {
        Matrix xOld(x); // Save current state.

        Matrix k1 = system->calculateXdot(x, u.getU(t));
        x = x + k1 * 0.5 * dt; /// Update A.

        Matrix k2 = system->calculateXdot(x, u.getU(t));
        x = x + k2 * 0.5 * dt; /// Update A.

        Matrix k3 = system->calculateXdot(x, u.getU(t));
        x = x + k3 * dt; /// Update A.

        Matrix k4 = system->calculateXdot(x, u.getU(t));

        x = xOld + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (dt / 6.0); /// Calculate new x.

        Matrix y = system->calculateY(x, u.getU(t));

        saveState(t + dt, x, y); /// Save after integration state.
    }
    this->t = t; /// Synchronise internal time with external time.
}

/// <summary>
/// Integrates this objects dynamic system from its predefined start to final time.
/// </summary>
/// <param name="x">The current state of the dynamic system of type Matrix.</param>
/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
void RungeKutta::integrate(Matrix& x, CommonInput& u)
{
    integrate(x, u, this->t, this->dt, this->tEnd);
}

/// This is a bit of a legacy function, should be reworked/removed
/// <summary>
/// Integrates this objects dynamic system from its predefined start to final time, while
/// resetting the current state to some initial state.
/// </summary>
/// <param name="x">The current state of the dynamic system of type Matrix.</param>
/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
/// <param name="x0">The initial state that should be integrated from.</param>
void RungeKutta::integrate(Matrix& x, CommonInput& u, Matrix x0)
{

    if (x.getRows() == x0.getRows() && x.getColumns() == x0.getColumns())
    {
        x = x0;
        integrate(x, u);
    }
}