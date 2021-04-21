/*
==============================================================
 Filename    :  Input.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.4
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
	rowSizeInput = (unsigned)inputVectorIn[0].size(); // set rowSize
	colSizeInput = (unsigned)inputVectorIn.size();		// set colSize
	inputVector = inputVectorIn;					//set inputvector
	u = Matrix(2, 1, 0.0);							// create u, 2x1 matrix with initial value 0.
}

///Destructor
Input::~Input()
{
	std::cout << "Destorying Input object. Also destroying parent object: ";
}


/// <summary>
/// getU finds the input values for the current time step. It uses zeroth-order interpolation to fill the descretization gaps.
/// </summary>
/// <param name="time">current time for which the input needs to be found.</param>
/// <returns>returns data of type Matrix with input values. 2 rows, 1 column. Thrust and angular velocity</returns>
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


/// <summary>
/// returns entire 2-d vector saved inside input object
/// </summary>
/// <returns>2-d vector with all input values</returns>
std::vector<std::vector<double>> Input::getInputVector()
{
	return inputVector; //return full inputVector (2D)
}
