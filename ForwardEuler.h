#ifndef SRC_FORWARDEULER_H
#define SRC_FORWARDEULER_H

#include "Simulator.h"
#include "Input.h"		// Input class


/// <summary>
/// Forward Euler integrator class. Handles all integration tasks, inherits from simulator (public). Uses member functions from Input class to retrieve inputs for current time.
/// Saves all data inside object, which can be exported to csv using its member functions.
/// </summary>
class ForwardEuler :
	public Simulator
{
public:

	/// <summary>
	/// Default constructor
	/// </summary>
	ForwardEuler() = default;

	/// <summary>
	/// Constructor with all required parameters to integrate.
	/// </summary>
	/// <param name="system">statespace of the system</param>
	/// <param name="t0">initial time</param>
	/// <param name="td">time step</param>
	/// <param name="tEnd">final time</param>
	ForwardEuler(StateSpace *system, double t0, double td, double tEnd);

	/// <summary>
	/// Integrate system inside current object, without specifying initial states.
	/// </summary>
	/// <param name="x">states matrix</param>
	/// <param name="u">object of type Input with inputs for the system</param>
	void integrate(Matrix& x, Input u);

	/// <summary>
	/// Integrate system inside current object, with specifying initial states.
	/// </summary>
	/// <param name="x">states matrix</param>
	/// <param name="u">object of type Input with inputs for the system</param>
	/// <param name="x0"> initial states matrix</param>
	void integrate(Matrix& x, Input u, Matrix x0);
};

#endif /*SRC_FORWARDEULER_H*/