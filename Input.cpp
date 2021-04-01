#include "Input.h"

Input::Input(std::vector<std::vector<double>> inputVectorIn) {
    inputVector = inputVectorIn;
}


Input::Input(Matrix u) : u(u)
{
}

Matrix Input::getU(double time)
{
    Matrix u(2,1,0.0);


	for (int i = 0; i < inputVector.size() - 1; i++)
	{
		if (time == inputVector[0][i]) {
			u(1, 1) = inputVector[1][i];
			u(2, 1) = inputVector[2][i];	
			return u;
		}
			
		else if (time >= inputVector[0][i] && time > inputVector[0][i + 1])
		{
			//else if the time is inbetween values do linear interpolation to find the right input values to output.
			double timeZero = inputVector[0][i];
			double timeOne = inputVector[0][i + 1];

			double thrustZero = inputVector[1][i];
			double thrustOne = inputVector[1][i + 1];

			double angularVelocityZero = inputVector[2][i];
			double angularVelocityOne = inputVector[2][i + 1];

			double deltaTime = timeOne - timeZero;
			double deltaThrust = thrustOne - thrustZero;
			double deltaAngularVelocity = angularVelocityOne - angularVelocityZero;

			double fraction = deltaTime / (time - timeZero);

			double interpolatedThrust = thrustZero + deltaThrust * fraction;
			double interpolatedAngularVelocity = angularVelocityZero + deltaAngularVelocity * fraction;

			u(1, 1) = interpolatedThrust;
			u(2, 1) = interpolatedAngularVelocity;

			return u;
		}

		else {
			// If time exceeds prespecified inputVector, return default value of [1;0] as input.
			std::cout << "simulation time is out of bounds of input values. Returning u = [1;0] as input. \n";
			u(1, 1) = 1;
			u(2, 1) = 0;

			return u;
		}
	}

}

Matrix Input::getU()
{
	return u;
}
