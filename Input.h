/*
==============================================================
 Filename    :  Input.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  Input.h handles the interpolation of the provided inputs for the drone.
				The frequency of the inputs does not match the integration frequency,
				for this reason, this interpolation is needed to figure out the inputs
				for the time steps inbetween new inputs. This file implements zeroth
				order interpolation.
==============================================================
*/

#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include "Matrix.h"
#include "SDL.h"
#include <vector>
#include "CommonInput.h"

/// <summary>
/// Handles inputs from 2-d vector and can return current input given the current time. Stores input data inside member variable inputVector.
/// Has search optimisation in case 2-d vector is very large to reduce latency.
/// </summary>
class Input: public CommonInput
{
private:
	unsigned rowSizeInput;
	unsigned colSizeInput;
	std::vector<std::vector<double>> inputVector;
	Matrix u;

public:
	Input() = default;

	/// <summary>
	///  constructor for input class object. This class can be used to load in 2-d vectors from the ReadCSV class.
	/// </summary>
	/// <param name="inputVectorIn"> 2-d vector with input values (thrust and angular velocity) over time</param>
	/// <param name="switchSearch"> search optimisation switch. Default state is on.</param>
	Input(std::vector<std::vector<double>>, bool);   

	~Input();

	/// <summary>
	/// getU finds the input values for the current time step. It uses zeroth-order interpolation to fill the descretization gaps.
	/// </summary>
	/// <param name="time">current time for which the input needs to be found.</param>
	/// <returns>returns data of type Matrix with input values. 2 rows, 1 column. Thrust and angular velocity</returns>
	Matrix getU(double time) override;


	/// <summary>
	/// returns entire 2-d vector saved inside input object
	/// </summary>
	/// <returns>2-d vector with all input values</returns>
	std::vector<std::vector<double>> getInputVector();

};

#endif /*SRC_INPUT_H*/