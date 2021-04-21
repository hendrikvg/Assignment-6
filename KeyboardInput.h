/*
==============================================================
 Filename    :  KeyboardInput.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  This class handles all processes needed to poll the keyboard for
				its inputs. These inputs are then set to our matrix u, which is then
				passed on to the integrator as the input values for the drone. The
				implementation can handle more than one input at a time.
==============================================================
*/

#ifndef SRC_KEYBOARDINPUT_H
#define SRC_KEYBOARDINPUT_H

#include "Matrix.h"
#include <vector>
#include "SDL.h"
#include "CommonInput.h"


/// <summary>
///	KeyboardInput inherits from CommonInput. See class description above for further information.
/// </summary>
class KeyboardInput : public CommonInput
{
private:
	Matrix u;
	const Uint8* keystates;

public:
	KeyboardInput(); //constructor

	~KeyboardInput(); //destructor

	/// <summary>
	/// Returns the current input vector U. Is called by the integrator.
	/// </summary>
	/// <param name="t">The current time. This is done to ensure compatibility with the other function so we keep our code DRY</param>
	/// <returns>Matrix u, the vector with drone inputs.</returns>
	Matrix getU(double time) override;

	/// <summary>
	/// Sets the thrust in matrix u to parameter value.
	/// </summary>
	/// <param name="thrust">Desired thrust.</param>
	void setThrust(double thrust);

	/// <summary>
	/// Sets the angular vecocity in matrix u to parameter value.
	/// </summary>
	/// <param name="angularVelocity">Desired Angular vecocity</param>
	void setAngularVelocity(double angularVelocity);


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
	void scanKeys(bool& quit, double inputAngularVelocity, double inputThrust, Matrix x0, Matrix& x, SDL_Event event);
};

#endif