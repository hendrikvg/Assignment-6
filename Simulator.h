#ifndef SRC_SIMULATOR_H
#define SRC_SIMULATOR_H

#include <vector>
#include "StateSpace.h"
#include "OutputCSV.h"

class Simulator
{
protected:
	StateSpace* system;
	Matrix x0;
	double dt;
	double t0;
	double tEnd;
	double t;
	std::vector<std::vector<double>> states;
public:
	Simulator() = default;
	void saveState(double t, Matrix x, Matrix y);
	void exportStates();
};

#endif // !SRC_SIMULATOR_H