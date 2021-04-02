#include "ReadCSV.h"

std::vector<std::vector<double>> ReadCSV::importCSVHelper(std::string filename) {		
	std::ifstream inputFile(filename);	// create input filestream object from the filename document
	double currentDouble;				// helper variable 
	std::string currentRow;				
	std::vector<double> temporaryVector;
	std::vector<std::vector<double>> inputSignal;

	if (inputFile.is_open()) { // File is connected and

		while (std::getline(inputFile, currentRow)) {		// Reads characters from inputFile and puts them in currentRow as string
			
			std::stringstream stringStreamRow(currentRow);	// Create stringstream stringStreamRow and initiate with currentRow

			while (stringStreamRow >> currentDouble) {		// While stingStreamRow can be cast to currentDouble, do that and ...
				
				temporaryVector.push_back(currentDouble);

				if (stringStreamRow.peek() == ',')
				{
					stringStreamRow.ignore();	// If the next character is 'c', ignore that character
				}
			}

			inputSignal.push_back(temporaryVector);
			temporaryVector.clear();

		}

		inputFile.close();														// Close file
	}

	else 
	{
		std::cout << "input file not found in directory.\n";
		return inputSignal;
	}
	
	input = inputSignal;
	return inputSignal;
}

std::vector<double> ReadCSV::calculateInputSignalHelper(double currentTime) {

	for (int i = 0; i < input.size() - 1; i++)
	{
		if (currentTime >= input[0][i] && currentTime > input[0][i + 1])
		{
			double timeZero = input[0][i];
			double timeOne = input[0][i + 1];

			double thrustZero = input[1][i];
			double thrustOne = input[1][i + 1];

			double angularVelocityZero = input[2][i];
			double angularVelocityOne = input[2][i + 1];

			double deltaTime = timeOne - timeZero;
			double deltaThrust = thrustOne - thrustZero;
			double deltaAngularVelocity = angularVelocityOne - angularVelocityZero;

			double fraction = deltaTime / (currentTime - timeZero);

			double interpolatedThrust = thrustZero + deltaThrust * fraction;
			double interpolatedAngularVelocity = angularVelocityZero + deltaAngularVelocity * fraction;


			return std::vector<double> {currentTime, interpolatedThrust, interpolatedAngularVelocity};
		}
	}
}