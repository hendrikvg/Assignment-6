#ifndef SRC_SIMULATOR_H
#define SRC_SIMULATOR_H

#include "StateSpace.h"

class Simulator
{
protected:
	StateSpace *system;
	Matrix x0;
	double dt;
	double t0;
	double tEnd;
	double t;
public:
	Simulator() = default;
	//Simulator(double t0, double tEnd, double dt, Matrix x0);
};

#endif // !SRC_SIMULATOR_H