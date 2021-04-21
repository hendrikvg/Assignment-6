/*
==============================================================
 Filename    :  StateSpace.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.3
 License     :  none.
 Description :  State-space operations are handled by this class. It takes at least four EntryMatrices as input
				and it can solve and return the results of the state-space equations:
				1. xdot = Ax + Bu (+ E)
				2. y = Cx + Du
==============================================================
*/
#ifndef SRC_STATESPACE_H
#define SRC_STATESPACE_H

#include "Matrix.h"
#include "EntryMatrix.h"


/// <summary>
/// Allows for creation of a (extended/nonlinear) statespace system.
/// Can calculate Xdot and Y of statespace with member functions. 
/// </summary>
class StateSpace
{
protected:
	EntryMatrix A;
	EntryMatrix B;
	EntryMatrix C;
	EntryMatrix D;
	EntryMatrix E;
	//Matrix x;
	//Matrix u;
	//Matrix x0;
	//Matrix y;
	//Matrix xdot;

public:
	/// <summary>
	/// Default constructor
	/// </summary>
	StateSpace() = default;

	/// <summary>
	/// Constructor for traditional state-space.
	/// </summary>
	/// <param name="A">A matrix.</param>
	/// <param name="B">B matrix.</param>
	/// <param name="C">C matrix.</param>
	/// <param name="D">D matrix.</param>
	StateSpace(EntryMatrix A, EntryMatrix B, EntryMatrix C, EntryMatrix D);

	/// <summary>
	/// Constructor for modified state-space (xdot = Ax + Bu + E).
	/// </summary>
	/// <param name="A">A matrix.</param>
	/// <param name="B">B matrix.</param>
	/// <param name="C">C matrix.</param>
	/// <param name="D">D matrix.</param>
	/// <param name="E">E matrix.</param>
	StateSpace(EntryMatrix A, EntryMatrix B, EntryMatrix C, EntryMatrix D, EntryMatrix E);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="">State-space that should be copied.</param>
	StateSpace(const StateSpace&); // copy

	~StateSpace(); // destructor

	// Get & set member functions:
	EntryMatrix getA() const;
	EntryMatrix getB() const;
	EntryMatrix getC() const;
	EntryMatrix getD() const;
	EntryMatrix getE() const;

	void setA(EntryMatrix);
	void setB(EntryMatrix);
	void setC(EntryMatrix);
	void setD(EntryMatrix);
	void setE(EntryMatrix E);


	// Calculate functions:


	/// <summary>
	/// Solves the first state-space equation and returns the resulting xdot.
	/// </summary>
	/// <param name="x">Current state.</param>
	/// <param name="u">Current input.</param>
	/// <returns>Time derivative of the current state (xdot).</returns>
	Matrix calculateXdot(Matrix x, Matrix u);

	/// <summary>
	/// Solves the second state-space equation and returns the resulting y.
	/// </summary>
	/// <param name="x">Current state.</param>
	/// <param name="u">Current input.</param>
	/// <returns>The measurement of the current state (y).</returns>
	Matrix calculateY(Matrix x, Matrix u);
};

#endif /*SRC_STATESPACE_H*/