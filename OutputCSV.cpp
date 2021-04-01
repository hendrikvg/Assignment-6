#include "OutputCSV.h"

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