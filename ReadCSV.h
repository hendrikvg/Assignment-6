#ifndef SRC_READCSV_H
#define SRC_READCSV_H



#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


/// <summary>
/// Handles reading a csv file and putting it inside a 2-d vector. Filename of the csv can be specified. Put csv inside root of project.
/// </summary>
class ReadCSV {
public:
	ReadCSV() = default;


	//This function takes a filename and returns a vector<vector<double>> of the input commands
	//@param insert filename of csv file.
	std::vector<std::vector<double>> importCSV(std::string filename) {

		return importCSVHelper(filename);
	}

private:
	std::vector<std::vector<double>> input;
	int rowSize;
	int colSize;


	//implementation heavily influenced by blog post: https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/ 
	//@param insert filename of csv file
	std::vector<std::vector<double>> importCSVHelper(std::string filename);

};


#endif