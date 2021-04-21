/*
==============================================================
 Filename    :  StateSpace.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.1
 License     :  none.
 Description :  State-space operations are handled by this class. It takes at least four EntryMatrices as input
				and it can solve and return the results of the state-space equations:
				1. xdot = Ax + Bu (+ E)
				2. y = Cx + Du
==============================================================
*/
#include "StateSpace.h"

// Constructor
StateSpace::StateSpace(EntryMatrix A, EntryMatrix B, EntryMatrix C, EntryMatrix D) : 
	A(A), B(B), C(C), D(D)
{
	Matrix E(A.getRows(), 1, 0.0);
	this->E = E;
}

StateSpace::StateSpace(EntryMatrix A, EntryMatrix B, EntryMatrix C, EntryMatrix D, Matrix E) :
	A(A), B(B), C(C), D(D), E(E)
{
}

// Copy Constructor
StateSpace::StateSpace(const StateSpace& stateSpace)
{
	this->A = stateSpace.getA();
	this->B = stateSpace.getB();
	this->C = stateSpace.getC();
	this->D = stateSpace.getD();
}

StateSpace::~StateSpace()
{

}

EntryMatrix StateSpace::getA() const
{
	return this->A;
}

EntryMatrix StateSpace::getB() const
{
	return this->B;
}

EntryMatrix StateSpace::getC() const
{
	return this->C;
}

EntryMatrix StateSpace::getD() const
{
	return this->D;
}

Matrix StateSpace::getE() const
{
	return this->E;
}

void StateSpace::setA(EntryMatrix A)
{
	this->A = A;
}

void StateSpace::setB(EntryMatrix B)
{
	this->B = B;
}

void StateSpace::setC(EntryMatrix C)
{
	this->C = C;
}

void StateSpace::setD(EntryMatrix D)
{
	this->D = D;
}

void StateSpace::setE(Matrix E)
{
	this->E = E;
}

Matrix StateSpace::calculateXdot(Matrix x, Matrix u)
{
	return A * x + B * u + E;
}

Matrix StateSpace::calculateY(Matrix x, Matrix u)
{
	return C * x + D * u;
}