#include <iostream>
#include <fstream>
#include <vector>
#include "inputcsv.h"
#include "outputCSV.h"


int main() {


	InputCSV csvIn;
	std::vector<std::vector<double>> inputSignal = csvIn.readCSV("inputmatrix.csv");

	//for (int i = 0; i < 2001; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		std::cout << inputSignal[j][i] << " ";
	//	}
	//	std::cout << "\n";

	//
	//}
	
	outputCSV csvOut;
	csvOut.writeCSV(inputSignal);



	system("pause");
	return 0;
}