#ifndef SRC_ENTRY_H
#pragma once
#define SRC_ENTRY_H

#include <functional>




/// <summary>
/// This class is needed since we want to be able to fill in variables and constants into our matrix class. This cannot be done without a wrapper class that checks whether the input is
/// variable or constant.
/// </summary>
class Entry {

public:

    /// <summary>
    /// constructor that takes variables
    /// </summary>
    /// <param name="entryFunc">enter variable</param>
    Entry(std::function<double()> entryFunc);

    /// <summary>
    /// constructor that takes constants
    /// </summary>
    /// <param name="constant">constants</param>
    Entry(double constant);

    /// Destructor
    ~Entry();

    /// <summary>
    /// returns the values inside object, by first checking wether it is constant or variable
    /// </summary>
    double calculate();
    double operator-(Entry B);
    double operator-(double B);
    double operator+(Entry B);
    double operator+(double B);

private:
    double constant;
    std::function<double()> entryFunction;

    bool isConstant;
};


#endif //SRC_ENTRY_H