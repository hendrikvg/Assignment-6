#include "ReadCSV.h"




std::vector<std::vector<double>> ReadCSV::importCSVHelper(std::string filename) {

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



	input = inputSignal;

	return inputSignal;
}

std::vector<double> ReadCSV::calculateInputSignalHelper(double currentTime) {


	for (int i = 0; i < input.size()-1; i++)
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