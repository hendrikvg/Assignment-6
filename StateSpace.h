#ifndef SRC_STATESPACE_H_
#define SRC_STATESPACE_H_

#include "Matrix.h"

class StateSpace
{
protected:
	Matrix A;
	Matrix B;
	Matrix C;
	Matrix D;
	Matrix x;
	Matrix u;
	Matrix x0;
	Matrix E;
	Matrix y;
	Matrix xdot;

public:
	StateSpace();
	StateSpace(Matrix A, Matrix B, Matrix C, Matrix D);
	StateSpace(Matrix A, Matrix B, Matrix C, Matrix D, Matrix E);
	// copy
	// destructor

	// Get & set member functions:
	Matrix getA();
	Matrix getB();
	Matrix getC();
	Matrix getD();
	Matrix getE();


};

#endif /*SRC_STATESPACE_H_*/