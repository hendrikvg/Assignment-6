#ifndef SRC_RUNGEKUTTA_H
#define SRC_RUNGEKUTTA_H

#include "Simulator.h"

class RungeKutta : public Simulator
{
private:
	Matrix xdot;
	Matrix y;

public:
	RungeKutta() = default;

	RungeKutta(StateSpace* system, double t0, double dt, double tEnd);

	void integrate (Matrix& x, Input u) override;
	void integrate(Matrix& x, Input u, double dt) override;
	void integrate (Matrix& x, Input u, Matrix x0) override;
};

#endif
