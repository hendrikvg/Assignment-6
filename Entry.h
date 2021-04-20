/*
==============================================================
 Filename    :  Entry.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  none.
 Description :  The aim of this file is to create a wrapper class that can be either
                a constant or a lambda function.
==============================================================
*/

#ifndef SRC_ENTRY_H
#pragma once
#define SRC_ENTRY_H

#include <functional> // For functions as inputs.

/// <summary>
/// This class is needed since we want to be able to fill in variables and constants 
/// into our matrix class. This cannot be done without a wrapper class that checks 
/// whether the input is a variable or constant.
/// </summary>
class Entry {
private:

    double constant;
    std::function<double()> entryFunction;
    bool isConstant; // Tells whether it should return a function or constant.

public:

    /// <summary>
    /// Constructor that takes lambda function.
    /// </summary>
    /// <param name="entryFunc">Enter lambda function.</param>
    Entry(std::function<double()> entryFunc);

    /// <summary>
    /// Constructor that takes constants.
    /// </summary>
    /// <param name="constant">Constants of type double.</param>
    Entry(double constant);

    /// <summary>
    /// Returns the values inside object, by first checking wether it is constant or 
    /// variable.
    /// </summary>
    double calculate();

    /// Operator overrides that enable adding and subtracting with other Entry
    /// objects and numbers of type double.
    double operator-(Entry B);
    double operator-(double B);
    double operator+(Entry B);
    double operator+(double B);
};


#endif //SRC_ENTRY_H