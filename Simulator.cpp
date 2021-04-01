#include "Simulator.h"

void Simulator::saveState(double t, Matrix x, Matrix y)
{
	std::vector<double> state;
	state.push_back(t);
	for (unsigned row = 0; row < x.getRows(); row++)
	{
		state.push_back(x.getVector()[row]);
	}
	for (unsigned row = 0; row < y.getRows(); row++)
	{
		state.push_back(y.getVector()[row]);
	}
	this->states.push_back(state);
}
