#include "Input.h"




Input::Input(std::vector<std::vector<double>> inputVectorIn, bool switchSearch = 1) {
	rowSizeInput = (unsigned) inputVectorIn[0].size();
	colSizeInput = (unsigned) inputVectorIn.size();
	inputVector = inputVectorIn;
	u = Matrix(2, 1, 0.0);
	keystates = SDL_GetKeyboardState(NULL); // Argument is the number of keys available, since we don't care it's set to NULL.
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



Matrix Input::getKey() {
	return this->u;
}

void Input::setThrust(double thrust) {
	this->u(1, 1) = thrust;
}

void Input::setAngularVelocity(double angularVelocity) {
	this->u(2, 1) = angularVelocity;
}


void Input::keyboardInput(double t, double tEnd, bool& quit, double inputAngularVelocity, double inputThrust, Matrix x0, Matrix& x, SDL_Event event, Input input) {
	setThrust(0);
	setAngularVelocity(0);


    if (keystates[SDL_SCANCODE_ESCAPE] || t > tEnd)
    {
        quit = true;
    }

    if (keystates[SDL_SCANCODE_LEFT])
    {
        setAngularVelocity(inputAngularVelocity);
    }

    if (keystates[SDL_SCANCODE_RIGHT])
    {
        setAngularVelocity(-inputAngularVelocity);
    }

    if (keystates[SDL_SCANCODE_UP])
    {
        setThrust(inputThrust);
    }
    if (keystates[SDL_SCANCODE_SPACE])
    {
        x = x0;
    }
}