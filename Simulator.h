#ifndef SRC_SIMULATOR_H
#define SRC_SIMULATOR_H

#include <vector>
#include <string>
#include "StateSpace.h"
#include "OutputCSV.h"
#include "Input.h"

/// <summary>
/// Defines basic functionality needed for all types of future simulations and integrations. Can save current states to a member variable. Can export that member variable making use of writeCSV class.
/// </summary>
class Simulator
{
protected:
	StateSpace* system;
	Matrix x0;
	Matrix x;
	Matrix u;
	double dt;
	double t0;
	double tEnd;
	double t;
	std::vector<std::vector<double>> states;

public:

	/// <summary>
	/// Constructor. Does not need to be called explicitly.
	/// </summary>
	Simulator() = default;


	//virtual void integrate(Matrix& x, Input u, double tEnd, Matrix x0) = 0;

	//virtual void integrateThis(Matrix& x, Input u, SDL_Event& event, double& time) = 0;

	virtual void integrate(Matrix& x, Input u) = 0;
	virtual void integrate(Matrix& x, Input u, double dt) = 0;
	virtual void integrate(Matrix& x, Input u, Matrix x0) = 0;

	/// <summary>
	/// Saves current state of statespace to simulator object. 
	/// </summary>
	/// <param name="t">time</param>
	/// <param name="x">states</param>
	/// <param name="y">output</param>
	void saveState(double t, Matrix x, Matrix y);

	/// <summary>
	/// Exports states to a csv file with specified name. Makes use of OutputCSV class to do this.
	/// </summary>
	/// <param name="">Desired name of csv file to be exported.</param>
	void exportStates(std::string);
};

#endif // !SRC_SIMULATOR_H