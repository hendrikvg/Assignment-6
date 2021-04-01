#ifndef SRC_READCSV_H
#define SRC_READCSV_H



#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class ReadCSV {
public:
	ReadCSV() {}
	~ReadCSV() {}


	//This function takes a filename and returns a vector<vector<double>> of the input commands
	//@param insert filename of csv file.
	std::vector<std::vector<double>> importCSV(std::string filename) {

		return importCSVHelper(filename);
	}

	std::vector<double> calculateInputSignal(double currentTime) {
		return calculateInputSignalHelper(currentTime);
	}



private:
	std::vector<std::vector<double>> input;


	//implementation heavily influenced by blog post: https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/ 
	//@param insert filename of csv file
	std::vector<std::vector<double>> importCSVHelper(std::string filename);

	std::vector<double> calculateInputSignalHelper(double currentTime);

};


#endif