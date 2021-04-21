/*
==============================================================
 Filename    :  Functions.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  getInteger() implementation. Comes from assignment 1 of week 1. 
                It is used for retrieving integers from the user in the system menus.
==============================================================
*/
#ifndef SRC_FUNCTIONS_H
#define SRC_FUNCTIONS_H

#include <iostream>
#include <string>
#include <sstream>

/*
The function getInteger() makes sure the input string is an integer the minimum and the maximum input.
If it isn't then the user will be asked to correct their input.
If it is then the input string will be converted to an integer and returned.

@param minimum The minimum value of the integer that will be recieved
@param maximum The maximum value of the integer that will be recieved
@returns An integer from user input between the minimum and maximum
*/
int getInteger(int minimum, int maximum)
{
    int outputInteger;
    std::string inputString;

    while (1)
    {
        std::getline(std::cin, inputString);                                                                                             // gets user input as a string
        std::stringstream convert(inputString);                                                                                     // makes string into a stream
        if (convert >> outputInteger && !(convert >> inputString) && (outputInteger >= minimum) && (outputInteger <= maximum)) // checking for valid conversion and any rejects if any unconverted input left
        {
            return outputInteger;
        }
        else
        {
            std::cin.clear(); // clear the input
            std::cout << "ERROR!\nwrong input\nPlease enter an INTEGER between " << minimum << " and " << maximum << "\n";
        }
    }
}

#endif // !SRC_FUNCTIONS_H