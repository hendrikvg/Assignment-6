#ifndef SRC_RUNGEKUTTA_H
#define SRC_RUNGEKUTTA_H

#include "Simulator.h"

class RungeKutta : public Simulator
{
public:
	RungeKutta() = default;

	RungeKutta(StateSpace* system, double t0, double dt, double tEnd);

	~RungeKutta();

	void integrate(Matrix& x, CommonInput& u, double t, double dt, double tEnd) override;
	void integrate(Matrix& x, CommonInput& u) override;
	void integrate(Matrix& x, CommonInput& u, Matrix x0) override;
};

#endif
