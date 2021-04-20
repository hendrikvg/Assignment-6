#include "RungeKutta.h"


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

void RungeKutta::integrate(Matrix& x, CommonInput& u, double t, double dt, double tEnd)
{
    if (tEnd - t < dt)
    {
        dt = tEnd - t;
    }

    saveState(t, x, system->calculateY(x, u.getU(t)));

    for (t; t < tEnd; t += dt) {
        Matrix xOld(x);

        Matrix k1 = system->calculateXdot(x, u.getU(t));
        x = x + k1 * 0.5 * dt;

        Matrix k2 = system->calculateXdot(x, u.getU(t));
        x = x + k2 * 0.5 * dt;

        Matrix k3 = system->calculateXdot(x, u.getU(t));
        x = x + k3 * dt;

        Matrix k4 = system->calculateXdot(x, u.getU(t));

        x = xOld + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (dt / 6.0);

        Matrix y = system->calculateY(x, u.getU(t));

        saveState(t + dt, x, y);
    }
    this->t = t;
}

void RungeKutta::integrate(Matrix& x, CommonInput& u)
{
    integrate(x, u, this->t, this->dt, this->tEnd);
}

void RungeKutta::integrate(Matrix& x, CommonInput& u, Matrix x0)
{

    if (x.getRows() == x0.getRows() && x.getColumns() == x0.getColumns())
    {
        x = x0;
        integrate(x, u);
    }
}

std::thread RungeKutta::integrateThread(Matrix& x, CommonInput& u, double t, 
    double dt, double tEnd)
{
    return std::thread([&] {integrate(x, u, t, dt, tEnd); });
}
