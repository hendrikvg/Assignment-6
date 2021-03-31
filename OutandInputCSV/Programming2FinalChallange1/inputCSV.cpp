#include "inputCSV.h"




std::vector<std::vector<double>> InputCSV::readCSVHelper(std::string filename) {

	std::ifstream inputFile(filename); // create input filestream object from the filename document
	double currentDouble;			// helper variable 
	std::string currentRow;
	std::vector<std::vector<double>> inputSignal;

	inputSignal.resize(3);

	if (inputFile.is_open()) {

		while (std::getline(inputFile, currentRow)) {
			int currentColumnIndex = 0;

			std::stringstream stringStreamRow(currentRow);

			while (stringStreamRow >> currentDouble) {

				inputSignal.at(currentColumnIndex).push_back(currentDouble);


				if (stringStreamRow.peek() == ',') stringStreamRow.ignore();


				currentColumnIndex++;
			}

		}

		inputFile.close();
	}

	else {
		std::cout << "input file not found in directory.\n";
	}


	return inputSignal;
}