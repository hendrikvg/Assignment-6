/*
==============================================================
 Filename    :  Entry.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  none.
 Description :  The aim of this file is to create a wrapper class that can be either
                a constant or a lambda function.
==============================================================
*/

#include "Entry.h"

/// <summary>
/// Constructor that initializes with a lambda function.
/// </summary>
/// <param name="entryFunc">Lambda function to initialize with.</param>
Entry::Entry(std::function<double()> entryFunc) : entryFunction(entryFunc) {
    isConstant = false;
}

/// <summary>
/// Constructor that initializes with a constant.
/// </summary>
/// <param name="constant">Constant to initialize with.</param>
Entry::Entry(double constant) : constant(constant) {
    isConstant = true;
}
/// <summary>
/// Destructor
/// </summary>
Entry::~Entry()
{
}

/// <summary>
/// Returns either a constant or the result of a lambda function.
/// </summary>
/// <returns></returns>
double Entry::calculate() {
    return isConstant ? constant : entryFunction(); // Conditional ternary operator..
}

double Entry::operator-(Entry B)
{
    return calculate() - B.calculate();
}

double Entry::operator-(double B)
{
    return calculate() - B;
}

double Entry::operator+(Entry B)
{
    return calculate() + B.calculate();
}

double Entry::operator+(double B)
{
    return calculate() - B;
}