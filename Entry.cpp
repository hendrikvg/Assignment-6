/*
==============================================================
 Filename    :  Entry.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  This is a file with the implementation of the code for Entry.h.
                The aim of this class is to create a wrapper class that can be either
                a constant or a lambda function.
==============================================================
*/

#include "Entry.h"

/// <summary>
/// constructor that takes variables
/// </summary>
/// <param name="entryFunc">enter variable</param>
Entry::Entry(std::function<double()> entryFunc) : entryFunction(entryFunc) {
    isConstant = false;
}

/// <summary>
/// constructor that takes constants
/// </summary>
/// <param name="constant">constants</param>
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
/// returns the values inside object, by first checking wether it is constant or variable
/// </summary>
double Entry::calculate() {
    return isConstant ? constant : entryFunction();
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