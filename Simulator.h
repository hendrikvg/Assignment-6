/*
==============================================================
 Filename    :  Simulator.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.1
 License     :  none.
 Description :  Defines basic functionality needed for all types of future 
				simulations and integrations. Can save current states to a 
				member variable. Can export that member variable making 
				use of OutputCSV class.
==============================================================
*/
#ifndef SRC_SIMULATOR_H
#define SRC_SIMULATOR_H

#include <vector>
#include <string>
#include "StateSpace.h"
#include "OutputCSV.h"

/// <summary>
/// Defines basic functionality needed for all types of future simulations and integrations. Can save current states to a member variable. Can export that member variable making use of writeCSV class.
/// </summary>
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

	/// <summary>
	/// Constructor. Does not need to be called explicitly.
	/// </summary>
	Simulator() = default;

	~Simulator(); //destructor


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

#endif // !SRC_SIMULATOR_H