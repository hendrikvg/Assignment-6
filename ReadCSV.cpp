#include "ReadCSV.h"

std::vector<std::vector<double>> ReadCSV::importCSVHelper(std::string filename) {		
	std::ifstream inputFile(filename);	// create input filestream object from the filename document
	double currentDouble;				// helper variable 
	std::string currentRow;				// helper variable 
	std::vector<double> temporaryVector;// helper variable 

	std::vector<std::vector<double>> inputSignal; // to be returned once we have filled it with data

	if (inputFile.is_open()) { // if file is open

		while (std::getline(inputFile, currentRow)) {		// Reads characters from inputFile and puts them in currentRow as string
			
			std::stringstream stringStreamRow(currentRow);	// Create stringstream stringStreamRow and initiate with currentRow

			while (stringStreamRow >> currentDouble) {		// While stingStreamRow can be cast to currentDouble, do that and ...
				
				temporaryVector.push_back(currentDouble);	// puts data inside our temp vector

				if (stringStreamRow.peek() == ',')			// if the next char in string is a comma
				{
					stringStreamRow.ignore();	// If the next character is ',' ignore that character
				}
			}

			inputSignal.push_back(temporaryVector);		// put data that is inside temp vector in our return vector
			temporaryVector.clear();					// clear vector for use in next loop

		}

		inputFile.close();								// Close file
	}

	else 
	{
		std::cerr << "input file not found in directory.\n";
		return inputSignal;
	}
	
	input = inputSignal; // set member variable to our new data as well in case its needed later.
	return inputSignal;
}


