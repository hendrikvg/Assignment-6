#include "Entry.h"

template<typename F>
Entry<F>::Entry(double)
{
}

template<typename F>
Entry<F>::Entry(F& lambda)
{
}

template<typename F>
double Entry<F>::calculate()
{
	return value;
}