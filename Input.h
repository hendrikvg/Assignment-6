#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include "Matrix.h"
#include "SDL.h"
#include <vector>

/// <summary>
/// Handles inputs from 2-d vector and can return current input given the current time. Stores input data inside member variable inputVector.
/// Has search optimisation in case 2-d vector is very large to reduce latency.
/// </summary>
class Input
{
private:
	unsigned rowSizeInput;
	unsigned colSizeInput;
	std::vector<std::vector<double>> inputVector;
	Matrix u;
	const Uint8* keystates;

public:
	Input() = default;

	/// <summary>
	///  constructor for input class object. This class can be used to load in 2-d vectors from the ReadCSV class.
	/// </summary>
	/// <param name="inputVectorIn"> 2-d vector with input values (thrust and angular velocity) over time</param>
	/// <param name="switchSearch"> search optimisation switch. Default state is on.</param>
	Input(std::vector<std::vector<double>>, bool);     

	/// <summary>
	/// getU finds the input values for the current time step. It uses zeroth-order interpolation to fill the descretization gaps.
	/// </summary>
	/// <param name="time">current time for which the input needs to be found.</param>
	/// <returns>returns data of type Matrix with input values. 2 rows, 1 column. Thrust and angular velocity</returns>
	Matrix getU(double);


	/// <summary>
	/// returns entire 2-d vector saved inside input object
	/// </summary>
	/// <returns>2-d vector with all input values</returns>
	std::vector<std::vector<double>> getInputVector();


	Matrix getKey();
	void setThrust(double thrust);
	void setAngularVelocity(double angularVelocity);

	void keyboardInput(double t, double tEnd, bool& quit, double inputAngularVelocity, double inputThrust, Matrix x0, Matrix& x, SDL_Event event, Input input);

};

#endif /*SRC_INPUT_H*/