/*
==============================================================
 Filename    :  Simulator.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
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
std::thread Simulator::integrateThread(Matrix& x, CommonInput& u, double& t, double dt, int FPS, std::mutex& mtx, bool& quit)
{
	return std::thread([&, dt, FPS] {	// Lambda function that returns a thread.
		while (!quit) {					// The thread runs until the bool that it is called with changes to true.
			auto t1 = std::chrono::high_resolution_clock::now(); // Start timing computation time.
			double end = t + 1.0 / FPS;							// Calculate the end of the integration time.
			mtx.lock();											// Lock variables.
			integrate(x, u, t, dt, end);						// Integrate.
			mtx.unlock();										// Unlock variables.
			auto t2 = std::chrono::high_resolution_clock::now();// Stop timing computation time.
			std::chrono::milliseconds remaining(10 - std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()); // Calculate remaining period of 100Hz:
			/// T = 1/f, f = 100Hz --> T = 1/100s --> 10ms. Time that should be waited until the thread should run again is 10ms - runtime(ms).
			if (remaining.count() <= 0) continue; // If the remaining time is negative, do not let this thread sleep but continue the loop.
			std::this_thread::sleep_for(remaining);
		}
	});
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
