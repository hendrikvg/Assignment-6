#ifndef SRC_RUNGEKUTTA_H
#define SRC_RUNGEKUTTA_H

#include "Simulator.h"
#include "Input.h"


class RungeKutta : public Simulator
{
private:
	Matrix xdot;
	Matrix x;
	Matrix u;
	Matrix y;

public:
	RungeKutta() = default;

	RungeKutta(StateSpace* system, double t0, double td, double tEnd);

	void integrate(Matrix& x, Input u);

	void integrate(Matrix& x, Input u, Matrix x0);



};

#endif
