/*
==============================================================
 Filename    :  Input.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.2
 License     :  none.
 Description :  This file handles the implementation of the Input.h memeber methods.
				Input.h handles the interpolation of the provided inputs for the drone.
				The frequency of the inputs does not match the integration frequency,
				for this reason, this interpolation is needed to figure out the inputs
				for the time steps inbetween new inputs. This file implements zeroth
				order interpolation.
==============================================================
*/

#include "Input.h"

/// <summary>
///  constructor for input class object. This class can be used to load in 2-d vectors from the ReadCSV class.
/// </summary>
/// <param name="inputVectorIn"> 2-d vector with input values (thrust and angular velocity) over time</param>
/// <param name="switchSearch"> search optimisation switch. Default state is on.</param>
Input::Input(std::vector<std::vector<double>> inputVectorIn, bool switchSearch = 1) {
	rowSizeInput = (unsigned) inputVectorIn[0].size();
	colSizeInput = (unsigned) inputVectorIn.size();
	inputVector = inputVectorIn;

	smartSearchMemory = (colSizeInput - 1 * switchSearch) * 0; // if swich is false, the smart search is turned off. Might be useful for debugging for future assignments.
}

///Destructor
Input::~Input()
{
	std::cout << "Destorying Input object.\n";
}

/// <summary>
/// getU finds the input values for the current time step. It uses zeroth-order interpolation to fill the descretization gaps.
/// </summary>
/// <param name="time">current time for which the input needs to be found.</param>
/// <returns>returns data of type Matrix with input values. 2 rows, 1 column. Thrust and angular velocity</returns>
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

			//if (time == inputVector[col - 1][0] && smartSearchMemory != 0) { smartSearchMemory--; }					
													// smartSearchMemory reduces the amount of loops we need to search by "remembering" where we left off in the previous loop.
													// it is reset to zero every time a new input object is made. It does add one additional if statement, when the condition of the first one is true
													// , but this should be well compensated for by the prevented loops.
			return u;
		}
	}
	std::cerr << "ERROR while getting U in Input.cpp";
	return u;
}

/// <summary>
/// returns entire 2-d vector saved inside input object
/// </summary>
/// <returns>2-d vector with all input values</returns>
std::vector<std::vector<double>> Input::getInputVector()
{
	return inputVector;
}