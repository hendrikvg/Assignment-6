#include "Entry.h"

Entry::Entry(std::function<double()> entryFunc) : entryFunction(entryFunc) {
    isConstant = false;
}

Entry::Entry(double constant) : constant(constant) {
    isConstant = true;
}

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