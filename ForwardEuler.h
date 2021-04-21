/*
==============================================================
 Filename    :  ForwardEuler.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  Forwad Euler integration scheme is handled by this class. It takes the state space,
				and other parameters and returns the state vector of the next time step. Inherits from
				Simulator class.
==============================================================
*/
#ifndef SRC_FORWARDEULER_H
#define SRC_FORWARDEULER_H

#include "Simulator.h" // for inheritance

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
	ForwardEuler(StateSpace *system, double t0, double dt, double tEnd);

	~ForwardEuler();
	

	/// <summary>
	/// Integrates this objects dynamic system from t to tEnd with stepsize dt.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
	/// <param name="t">The current time.</param>
	/// <param name="dt">The time step.</param>
	/// <param name="tEnd">The end time for integration.</param>
	void integrate(Matrix& x, CommonInput& u, double t, double dt, double tEnd) override;


	/// <summary>
	/// Integrates this objects dynamic system from its predefined start to final time.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
	void integrate(Matrix& x, CommonInput& u) override;

	/// This is a bit of a legacy function, should be reworked/removed
	/// <summary>
	/// Integrates this objects dynamic system from its predefined start to final time, while resetting the current state to some initial state.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
	/// <param name="x0">The initial state that should be integrated from.</param>
	void integrate(Matrix& x, CommonInput& u, Matrix x0) override;

};

#endif /*SRC_FORWARDEULER_H*/