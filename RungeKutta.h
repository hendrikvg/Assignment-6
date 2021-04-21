/*
==============================================================
 Filename    :  RungeKutta.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.3
 License     :  none.
 Description :  Runge Kutta integration scheme is handled by this class. It takes the state space,
				and other parameters and returns the state vector of the next time step. Inherits from
				Simulator class. The results are an improvement on the Forward Euler scheme, as it provides
				a better approximation of the exact solution.
==============================================================
*/

#ifndef SRC_RUNGEKUTTA_H
#define SRC_RUNGEKUTTA_H

#include "Simulator.h"

class RungeKutta : public Simulator
{
public:
	RungeKutta() = default;


	/// <summary>
	/// Constructor with all required parameters to integrate.
	/// </summary>
	/// <param name="system">statespace of the system</param>
	/// <param name="t0">initial time</param>
	/// <param name="td">time step</param>
	/// <param name="tEnd">final time</param>
	RungeKutta(StateSpace* system, double t0, double dt, double tEnd);

	~RungeKutta(); // destructor

	/// <summary>
	/// Integrates this objects dynamic system from t to tEnd with stepsize dt.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype Input.</param>
	/// <param name="t">The current time.</param>
	/// <param name="dt">The time step.</param>
	/// <param name="tEnd">The end time for integration.</param>
	void integrate(Matrix& x, Input u, double t, double dt, double tEnd) override;

	/// <summary>
	/// Integrates this objects dynamic system from its predefined start to final time.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype Input.</param>
	void integrate (Matrix& x, Input u) override;


	/// This is a bit of a legacy function, should be reworked/removed
	/// <summary>
	/// Integrates this objects dynamic system from its predefined start to final time, while 
	/// resetting the current state to some initial state.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype Input.</param>
	/// <param name="x0">The initial state that should be integrated from.</param>
	void integrate (Matrix& x, Input u, Matrix x0) override;
};

#endif /*SRC_RUNGEKUTTA_H*/
