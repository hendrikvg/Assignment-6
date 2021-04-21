/*
==============================================================
 Filename    :  ReadCSV.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.2
 License     :  none.
 Description :  This class handles the implementation of ReadCSV member methods.
				ReadCSV makes use of sstream to put data from an input CSV file into a sstream.
				This funcitonality is used to import inputs for the drone. The function returns
				a 2D vector with inputs to input.h class, where interpolation can take place.
				The implementation influenced by blog post:
				https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
==============================================================
*/

#include "ReadCSV.h"

ReadCSV::~ReadCSV()
{
	std::cout << "Destorying ReadCSV object.\n";
}

/// <summary>
/// Reads a CSV file and formats it as a 2D vector.
/// </summary>
/// <param name="filename">Filename.</param>
/// <returns>2D vector of the CSV file.</returns>
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


