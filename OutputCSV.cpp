/*
==============================================================
 Filename    :  OutputCSV.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  This class handles the implementation of OutputCSV member methods.
				Output csv makes use of sstream to create an output file. This
				funcitonality is used to export the states of the drone after integration.
==============================================================
*/

#include "OutputCSV.h"

OutputCSV::~OutputCSV()
{
	std::cout << "\nDestorying OutputCSV object.\n";
}

/// <summary>
/// Helper function that does all the work for writeCSV
/// </summary>
/// <param name="outputSignal">Name of 2-d vector</param>
/// <param name="filename">Desired name of filename. Must end in ".csv"</param>
void OutputCSV::writeCSVHelper(std::vector<std::vector<double>> outputSignal, std::string filename) {

	std::ofstream outputFile(filename);

	for (int col = 0; col < outputSignal.at(1).size(); col++) {
		for (int row = 0; row < outputSignal.size(); row++) {
			outputFile << outputSignal[row][col] << ",";
		}
		outputFile << "\n";
	}
	outputFile.close();
}