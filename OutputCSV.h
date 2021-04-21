/*
==============================================================
 Filename    :  OutputCSV.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  Output csv makes use of sstream and fstream to create an output file. This
				funcitonality is used to export the states of the drone after integration.
==============================================================
*/

#ifndef SRC_OUTPUTCSV_H
#pragma once
#define SRC_OUTPUTCSV_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


/// <summary>
/// Handles writing a 2-d vector to a csv file. Name can be specified. 
/// Size of vector is arbitrary. 
/// </summary>
class OutputCSV
{
public:
	OutputCSV() = default;

	~OutputCSV();

	/// Output 2-d vector to a CSV file
	/// @param Name of 2-d vector
	/// @param Desired name of filename. Must end in ".csv"
	void writeCSV(std::vector<std::vector<double>> outputSignal, std::string filename = "outputFile.csv") {
		writeCSVHelper(outputSignal, filename);
	}

private:
	/// <summary>
	/// Helper function that does all the work for writeCSV
	/// </summary>
	/// <param name="outputSignal">Name of 2-d vector</param>
	/// <param name="filename">Desired name of filename. Must end in ".csv"</param>
	void writeCSVHelper(std::vector<std::vector<double>> outputSignal, std::string filename);

};

#endif