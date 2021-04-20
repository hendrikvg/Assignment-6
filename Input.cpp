#include "Input.h"




Input::Input(std::vector<std::vector<double>> inputVectorIn, bool switchSearch = 1) {
	rowSizeInput = (unsigned) inputVectorIn[0].size();
	colSizeInput = (unsigned) inputVectorIn.size();
	inputVector = inputVectorIn;
	u = Matrix(2, 1, 0.0);
}



Matrix Input::getU(double time)
{
	Matrix u(rowSizeInput - 1, 1, 0.0); // Initiate u

	for (unsigned col = colSizeInput; col > 0; col--)		// Check all predefined times back to front
	{
		if (time >= inputVector[col - 1][0])	// If current time < predefined time
		{
			for (unsigned row = 1; row < rowSizeInput; row++)
			{
				u(row, 1) = inputVector[col - 1][row];		// add thrust and angular velocity to matrix u, making use of zeroth order interpolation.
			}
			return u;
		}
	}
	std::cerr << "ERROR while getting U in Input.cpp";
	return u;
}


std::vector<std::vector<double>> Input::getInputVector()
{
	return inputVector;
}

