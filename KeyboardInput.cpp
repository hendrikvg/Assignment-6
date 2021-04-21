/*
==============================================================
 Filename    :  KeyboardInput.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.4
 License     :  none.
 Description :  This file handles the implementation of the member methods of KeyboardInput.
                This class handles all processes needed to poll the keyboard for
                its inputs. These inputs are then set to our matrix u, which is then
                passed on to the integrator as the input values for the drone. The
                implementation can handle more than one input at a time.
==============================================================
*/

#include "KeyboardInput.h"

// constructor with all needed initializations.
KeyboardInput::KeyboardInput() {
    u = Matrix(2, 1, 0.0);
    keystates = SDL_GetKeyboardState(NULL); // Argument is the number of keys available, since we don't care it's set to NULL.
}


KeyboardInput::~KeyboardInput()
{
    std::cout << "Destorying KeyboardInput object. Also destorying parent object: ";
}


/// <summary>
/// Returns the current input vector U. Is called by the integrator.
/// </summary>
/// <param name="t">The current time. This is done to ensure compatibility with the other function so we keep our code DRY</param>
/// <returns>Matrix u, the vector with drone inputs.</returns>
Matrix KeyboardInput::getU(double time) {
    //time = NULL;
    return this->u;
}

/// <summary>
/// Sets the thrust in matrix u to parameter value.
/// </summary>
/// <param name="thrust">Desired thrust.</param>
void KeyboardInput::setThrust(double thrust) {
    this->u(1, 1) = thrust;
}

/// <summary>
/// Sets the angular vecocity in matrix u to parameter value.
/// </summary>
/// <param name="angularVelocity">Desired Angular vecocity</param>
void KeyboardInput::setAngularVelocity(double angularVelocity) {
    this->u(2, 1) = angularVelocity;
}

/// <summary>
/// Can be used to poll the entire keyboard for input commands for the drone. Should be polled every FPS. 
/// Looks for arrow up, arrow right, arrow left, space and escape.
/// </summary>
/// <param name="t">Current time</param>
/// <param name="tEnd">End time of interval</param>
/// <param name="quit">Quit switch for SDL</param>
/// <param name="inputAngularVelocity">Desired angular velocity when pressing left or right key</param>
/// <param name="inputThrust">Desidered thrust when pressing up key</param>
/// <param name="x0">initial states of drone, used for resetting the drone location </param>
/// <param name="x">current states</param>
/// <param name="event">SDL_Event event name</param>
void KeyboardInput::scanKeys(bool& quit, double inputAngularVelocity, double inputThrust, Matrix x0, Matrix& x, SDL_Event event) {
    setThrust(0);
    setAngularVelocity(0);

    if (keystates[SDL_SCANCODE_ESCAPE])     // if espace is pressed
    {
        quit = true;                        // set quit to true
    }

    if (keystates[SDL_SCANCODE_LEFT])       // if left
    {
        setAngularVelocity(inputAngularVelocity); // set angular velocity
    }

    if (keystates[SDL_SCANCODE_RIGHT])      // if right
    {
        setAngularVelocity(-inputAngularVelocity); // set -angular velocity
    }

    if (keystates[SDL_SCANCODE_UP])         // if up
    {
        setThrust(inputThrust);             // thrusters on
    }
    if (keystates[SDL_SCANCODE_SPACE])      // if space
    {
        x = x0;                             // reset drone and cargo locations
    }
}