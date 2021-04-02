#include "ForwardEuler.h"

ForwardEuler::ForwardEuler(StateSpace *system, double t0, double dt, double tEnd = 0)
{
    this->system = system;
    this->t0 = t0;
    this->dt = dt;
    this->tEnd = tEnd;
    this->t = 0;
}

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
    exportStates();
}

// Allow for setting initial state x0
void ForwardEuler::integrate(Matrix& x, Input u, Matrix x0)
{
    if (x.getRows() == x0.getRows() && x.getColumns() == x0.getColumns())
    {
        x = x0;
        integrate(x, u);
    }
}