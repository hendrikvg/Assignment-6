/*
==============================================================
 Filename    :  ReadCSV.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.3
 License     :  none.
 Description :  ReadCSV makes use of sstream to put data from an input CSV file into a sstream.
				This funcitonality is used to import inputs for the drone. The function returns
				a 2D vector with inputs to input.h class, where interpolation can take place.
				The implementation influenced by blog post:
				https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
==============================================================
*/

#ifndef SRC_READCSV_H
#define SRC_READCSV_H



#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


/// <summary>
/// Handles reading a csv file and putting it inside a 2-d vector. 
/// Filename of the csv can be specified. Put csv inside root of project.
/// </summary>
class ReadCSV {
public:
	ReadCSV() = default;


	/// Destructor.
	~ReadCSV();

	/// <summary>
	/// This function takes a filename and returns a 2D vector of
	/// the input commands
	/// </summary>
	/// <param name="filename">insert filename of csv file.</param>
	/// <returns>2D vector of the input commands.</returns>
	std::vector<std::vector<double>> importCSV(std::string filename) {

		return importCSVHelper(filename);
	}

private:
	std::vector<std::vector<double>> input;
	int rowSize;
	int colSize;


	/// <summary>
	/// Reads a CSV file and formats it as a 2D vector.
	/// </summary>
	/// <param name="filename">Filename.</param>
	/// <returns>2D vector of the CSV file.</returns>
	std::vector<std::vector<double>> importCSVHelper(std::string filename);

};


#endif