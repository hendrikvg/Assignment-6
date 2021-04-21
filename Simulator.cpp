/*
==============================================================
 Filename    :  Simulator.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.2
 License     :  none.
 Description :  This class handles the implementation of Simulator member methods.
				Simulator
==============================================================
*/

#include "Simulator.h"

Simulator::~Simulator()
{
	std::cout << "Destroying Simulator object.\n";
}

/// <summary>
/// Saves current state of statespace to simulator object as [t; x; y].
/// </summary>
/// <param name="t">time</param>
/// <param name="x">states</param>
/// <param name="y">output</param>
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

/// <summary>
/// Exports states to a csv file with specified name. Makes use of OutputCSV 
/// class to do this.
/// </summary>
/// <param name="">Desired name of csv file to be exported.</param>
void Simulator::exportStates(std::string nameCSV = "StatesExport.csv")
{
	OutputCSV output;
	output.writeCSV(this->states, nameCSV);
}
