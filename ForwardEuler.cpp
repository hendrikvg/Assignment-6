#include "ForwardEuler.h"

ForwardEuler::ForwardEuler(StateSpace *system, double t0, double dt, double tEnd = 0)
{
    this->system = system;
    this->t0 = t0;
    this->dt = dt;
    this->tEnd = tEnd;
    this->t = t0;
}

void ForwardEuler::integrate(Matrix& x, Input u, double t, double dt, double tEnd)
{
    saveState(t, x, system->calculateY(x, u.getU(t)));

    for (t; t < tEnd; t += dt)
    {
        x = x + system->calculateXdot(x, u.getU(t)) * dt;

        Matrix y = system->calculateY(x, u.getU(t));

        saveState(t + dt, x, y);
    }
    this->t = t;
}

void ForwardEuler::integrate(Matrix& x, Input u)
{
    integrate(x, u, this->t, this->dt, this->tEnd);
}

void ForwardEuler::integrate(Matrix& x, Input u, Matrix x0)
{
    if (x.getRows() == x0.getRows() && x.getColumns() == x0.getColumns())
    {
        x = x0;
        integrate(x, u);
    }
}

void ForwardEuler::integrateThis(Matrix& x, Input u, SDL_Event &event, double& time) {

    x = x + system->calculateXdot(x, u.getKey(event)) * dt;
    Matrix y = system->calculateY(x, u.getKey(event)) * dt;

    

    saveState(time, x, y);
    time += dt;
}