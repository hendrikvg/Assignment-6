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
	Matrix y;
	Matrix xdot;

public:
	StateSpace();
	StateSpace(Matrix A, Matrix B, Matrix C, Matrix D);
	StateSpace(const StateSpace&); // copy
	~StateSpace(); // destructor

	// Get & set member functions:
	Matrix getA() const;
	Matrix getB() const;
	Matrix getC() const;
	Matrix getD() const;
	Matrix getX() const;
	Matrix getU() const;
	Matrix getX0() const;
	Matrix getY() const;
	Matrix getXdot() const;
	void setA(Matrix);
	void setB(Matrix);
	void setC(Matrix);
	void setD(Matrix);
	void setX(Matrix);
	void setU(Matrix);
	void setX0(Matrix);
	void setY(Matrix);
	void setXdot(Matrix);

	// Calculate functions:
	Matrix calculateXdot();
	Matrix calculateY();
};

#endif /*SRC_STATESPACE_H_*/