#include "RungeKutta.h"


RungeKutta::RungeKutta(StateSpace* system, double t0, double dt, double tEnd = 0) {
    this->system = system;
    this->t0 = t0;
    this->dt = dt;
    this->tEnd = tEnd;
    this->t = 0;
}

void RungeKutta::integrate(Matrix& x, Input u)  
{
    if (t == 0)
    {
        for (t = t0; t < tEnd; t += dt) {
            // implementation Runge Kutta for t==0

            Matrix k1 = system->calculateXdot(x, u.getU(t));
            Matrix k2 = system->calculateXdot((x + k1 * 0.5 * dt), u.getU(t));
            Matrix k3 = system->calculateXdot((x + k2 * 0.5 * dt), u.getU(t));
            Matrix k4 = system->calculateXdot((x + k3 * dt), u.getU(t));

            Matrix k = (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (1.0 / 6.0) * dt;

            x = x + k;
            

            //nested version: 
            /*
            x = x + (system->calculateXdot(x, u.getU(t)) // old states + k1
                + system->calculateXdot((x + k1 * 0.5 * dt), u.getU(t)) * 2 // + k2
                + system->calculateXdot((x + k2 * 0.5 * dt), u.getU(t)) * 2 // + k3
                + system->calculateXdot((x + k3 * dt), u.getU(t))) // + k4
                * (1 / 6) * dt; // * scalar * timestep */

            Matrix y = system->calculateY(x, u.getU(t));

            saveState(t, x, y);
        }
    }
    else
    {
        for (t; t < tEnd; t += dt) {
            //implementation Runge Kutta for t!=0

            Matrix k1 = system->calculateXdot(x, u.getU(t));
            Matrix k2 = system->calculateXdot((x + k1 * 0.5 * dt), u.getU(t));
            Matrix k3 = system->calculateXdot((x + k2 * 0.5 * dt), u.getU(t));
            Matrix k4 = system->calculateXdot((x + k3 * dt), u.getU(t));

            Matrix k = (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (1.0 / 6.0) * dt;

            x = x + k;
            

            Matrix y = system->calculateY(x, u.getU(t));


            saveState(t, x, y);
        }
    }
}

void RungeKutta::integrate(Matrix& x, Input u, Matrix x0)  
{

    if (x.getRows() == x0.getRows() && x.getColumns() == x0.getColumns())
    {
        x = x0;
        integrate(x, u);
    }
}