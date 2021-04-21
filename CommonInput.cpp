/*
==============================================================
 Filename    :  CommonInput.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  Implementation for CommonInput class methods. 
				This class is the parent class of both input types, KeyboardInput and Input.
==============================================================
*/

#include "CommonInput.h"


///
CommonInput::~CommonInput() // destructor 
{
	std::cout << "Destroying CommonInput object.\n";
}
