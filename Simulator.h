/*
==============================================================
 Filename    :  Simulator.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  This class handles the implementation of Simulator member methods.
				Simulator
==============================================================
*/

#ifndef SRC_SIMULATOR_H
#pragma once
#define SRC_SIMULATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include "StateSpace.h"
#include "OutputCSV.h"
#include "CommonInput.h"

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
	Matrix xdot;
	Matrix y;
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

	// Destructor.
	~Simulator();

	/// <summary>
	/// Integrates this objects dynamic system from t to tEnd with stepsize dt.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
	/// <param name="t">The current time.</param>
	/// <param name="dt">The time step.</param>
	/// <param name="tEnd">The end time for integration.</param>
	virtual void integrate(Matrix& x, CommonInput& u, double t, double dt, double tEnd) = 0;

	/// <summary>
	/// Integrates this objects dynamic system from its predefined start to final time.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
	virtual void integrate(Matrix& x, CommonInput& u) = 0;

	/// This is a bit of a legacy function, should be reworked/removed
	/// <summary>
	/// Integrates this objects dynamic system from its predefined start to final time, while resetting the current state to some initial state.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
	/// <param name="x0">The initial state that should be integrated from.</param>
	virtual void integrate(Matrix& x, CommonInput& u, Matrix x0) = 0;

	/// <summary>
	/// Generates a thread, that runs on a frequency of 100Hz, that integrates this objects dynamic system from the current time to the time of the next frame.
	/// </summary>
	/// <param name="x">The current state of the dynamic system of type Matrix.</param>
	/// <param name="u">The current input for the dynamic system o ftype CommonInput.</param>
	/// <param name="t">The current time.</param>
	/// <param name="dt">The time step.</param>
	/// <param name="FPS">The FPS, which is needed to calculate the end time of integration.</param>
	/// <param name="mtx">Mutex object, needed to lock the state vector.</param>
	/// <param name="quit">Quit bool, needed to stop the thread from running.</param>
	/// <returns>A thread that integrates this objects dyamic system at a frequency of 100Hz.</returns>
	std::thread integrateThread(Matrix& x, CommonInput& u, double& t, double dt, int FPS, std::mutex &mtx, bool& quit);

	/// <summary>
	/// Saves current state of statespace to simulator object as [t; x; y].
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

#endif /*SRC_SIMULATOR_H*/