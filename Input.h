#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include "Matrix.h"
#include <vector>


class Input
{
private:
	unsigned rowSizeInput;
	unsigned colSizeInput;
	std::vector<std::vector<double>> inputVector;
	Matrix u;

public:
	Input(std::vector<std::vector<double>>);     
	Matrix getU(double);
	//Input(Matrix); // test
	//Matrix getU(); // test
	std::vector<std::vector<double>> getInputVector();
};

#endif