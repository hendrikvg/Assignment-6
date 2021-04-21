/*
==============================================================
 Filename    :  StateSpace.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.5
 License     :  none.
 Description :  State-space operations are handled by this class. It takes at least four EntryMatrices as input
				and it can solve and return the results of the state-space equations:
				1. xdot = Ax + Bu (+ E)
				2. y = Cx + Du
==============================================================
*/

#include "StateSpace.h"

// Constructors:

/// <summary>
/// Constructor for traditional state-space.
/// </summary>
/// <param name="A">A matrix.</param>
/// <param name="B">B matrix.</param>
/// <param name="C">C matrix.</param>
/// <param name="D">D matrix.</param>
StateSpace::StateSpace(EntryMatrix A, EntryMatrix B, EntryMatrix C, EntryMatrix D) : 
	A(A), B(B), C(C), D(D)
{
	EntryMatrix E(A.getRows(), 1, 0.0);
	this->E = E;
}

/// <summary>
/// Constructor for modified state-space (xdot = Ax + Bu + E).
/// </summary>
/// <param name="A">A matrix.</param>
/// <param name="B">B matrix.</param>
/// <param name="C">C matrix.</param>
/// <param name="D">D matrix.</param>
/// <param name="E">E matrix.</param>
StateSpace::StateSpace(EntryMatrix A, EntryMatrix B, EntryMatrix C, EntryMatrix D, EntryMatrix E) :
	A(A), B(B), C(C), D(D), E(E)
{
}

/// <summary>
/// Copy constructor
/// </summary>
/// <param name="">State-space that should be copied.</param>
StateSpace::StateSpace(const StateSpace& stateSpace)
{
	this->A = stateSpace.getA();
	this->B = stateSpace.getB();
	this->C = stateSpace.getC();
	this->D = stateSpace.getD();
}

StateSpace::~StateSpace()
{
	std::cout << "Destorying StateSpace object.\n";
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

EntryMatrix StateSpace::getE() const
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

void StateSpace::setE(EntryMatrix E)
{
	this->E = E;
}

/// <summary>
/// Solves the first state-space equation and returns the resulting xdot.
/// </summary>
/// <param name="x">Current state.</param>
/// <param name="u">Current input.</param>
/// <returns>Time derivative of the current state (xdot).</returns>
Matrix StateSpace::calculateXdot(Matrix x, Matrix u)
{
	return A * x + B * u + E;
}

/// <summary>
/// Solves the second state-space equation and returns the resulting y.
/// </summary>
/// <param name="x">Current state.</param>
/// <param name="u">Current input.</param>
/// <returns>The measurement of the current state (y).</returns>
Matrix StateSpace::calculateY(Matrix x, Matrix u)
{
	return C * x + D * u;
}