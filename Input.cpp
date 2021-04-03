#include "Input.h"


Input::Input(std::vector<std::vector<double>> inputVectorIn, bool switchSearch = 1) {
	rowSizeInput = inputVectorIn[0].size();
	colSizeInput = inputVectorIn.size();
    inputVector = inputVectorIn;
	smartSearchMemory = colSizeInput - 1 * switchSearch; // if swich is false, the smart search is turned off. Might be useful for debugging for future assignments.
}



Matrix Input::getU(double time)
{
    Matrix u(rowSizeInput - 1, 1, 0.0); // Initiate u

	for (unsigned col = colSizeInput - smartSearchMemory; col > 0; col--)		// Check all predefined times back to front
	{
		if (time >= inputVector[col - 1][0])	// If current time < predefined time
		{
			for (unsigned row = 1; row < rowSizeInput; row++)
			{
				u(row, 1) = inputVector[col - 1][row];		// add thrust and angular velocity to matrix u, making use of zeroth order interpolation.
			}

			if (time == inputVector[col - 1][0] && smartSearchMemory != 0) { smartSearchMemory--; }					
													// smartSearchMemory reduces the amount of loops we need to search by "remembering" where we left off in the previous loop.
													// it is reset to zero every time a new input object is made. It does add one additional if statement, when the condition of the first one is true
													// , but this should be well compensated for by the prevented loops.
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

