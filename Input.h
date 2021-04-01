#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include "Matrix.h"
#include <vector>


class Input
{
private:
	std::vector<std::vector<double>> inputVector;

public:
	Input(std::vector<std::vector<double>>);     
	//Input(Matrix);
	Matrix getU(double);
};

#endif