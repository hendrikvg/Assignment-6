/*
==============================================================
 Filename    :  CommonInput.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.4
 License     :  none.
 Description :  This class is the parent class of both input types, KeyboardInput and Input.
==============================================================
*/

#ifndef SRC_COMMONINPUT_H
#define SRC_COMMONINPUT_H

#include "Matrix.h"

/// <summary>
/// CommonInput is the parent class for both input methods. It defines a matrix u, and one virtual function for returning the current input values.
///</summmary>
class CommonInput
{
protected:
	Matrix u; //input matrix for the state space.

public:
	CommonInput() = default;
	~CommonInput(); // destructor

	/// <summary>
	/// getU is a virtual function that has no implementation in this parent class.
	/// </summary>
	/// <param name="time">the current time for which the input value has to be returned.</param>
	virtual Matrix getU(double time) = 0;

};

#endif