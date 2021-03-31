#ifndef INPUTCSV_H
#define INPUTCSV_H



#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class InputCSV {
public:
	InputCSV() {}
	~InputCSV() {}


	//This function takes a filename and returns a vector<vector<double>> of the input commands
	//@param insert filename of csv file.
	std::vector<std::vector<double>> readCSV(std::string filename) {

		return readCSVHelper(filename);
	}

private:

	//implementation heavily influenced by blog post: https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/ 
	//@param insert filename of csv file
	std::vector<std::vector<double>> readCSVHelper(std::string filename);

};


#endif