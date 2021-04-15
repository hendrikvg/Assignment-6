#ifndef SRC_RUNGEKUTTA_H
#define SRC_RUNGEKUTTA_H

#include "Simulator.h"

class RungeKutta : public Simulator
{
public:
	RungeKutta() = default;

	RungeKutta(StateSpace* system, double t0, double td, double tEnd);

	void integrate (Matrix& x, Input u) override;

	void integrate (Matrix& x, Input u, Matrix x0) override;
};

#endif
