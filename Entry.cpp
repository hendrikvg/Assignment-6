#include "Entry.h"
template<typename T>
Entry<T>::Entry(T entryFunc) : entryFunction(entryFunc) {
    isConstant = false;
}

template<typename T>
Entry<T>::Entry(double constant) : constant(constant) {
    isConstant = true;
}

template<typename T>
double Entry<T>::calculate() {
    return isConstant ? constant : entryFunction();
}