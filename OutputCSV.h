#ifndef SRC_OUTPUTCSV_H
#define SRC_OUTPUTCSV_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class OutputCSV
{
public:
	OutputCSV() = default;
	~OutputCSV() {}; // not sure if curly brackets are allowed here.


	/// Output signal to a CSV file
	/// @param Name of output signal 
	/// @param Desired name of filename. Must end in ".csv"
	void writeCSV(std::vector<std::vector<double>> outputSignal, std::string filename = "outputFile.csv") {
		writeCSVHelper(outputSignal, filename);
	}

private:
	void writeCSVHelper(std::vector<std::vector<double>> outputSignal, std::string filename);

};

#endif