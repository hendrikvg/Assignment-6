#ifndef SRC_STATESPACE_H
#define SRC_STATESPACE_H

#include "Matrix.h"
#include "EntryMatrix.h"

class StateSpace
{
protected:
	EntryMatrix A;
	EntryMatrix B;
	EntryMatrix C;
	EntryMatrix D;
	//Matrix x;
	//Matrix u;
	//Matrix x0;
	//Matrix y;
	//Matrix xdot;

public:
	StateSpace() = default;
	StateSpace(EntryMatrix A, EntryMatrix B, EntryMatrix C, EntryMatrix D);
	StateSpace(const StateSpace&); // copy
	~StateSpace(); // destructor

	// Get & set member functions:
	EntryMatrix getA() const;
	EntryMatrix getB() const;
	EntryMatrix getC() const;
	EntryMatrix getD() const;
	//Matrix getX() const;
	//Matrix getU() const;
	//Matrix getX0() const;
	//Matrix getY() const;
	//Matrix getXdot() const;
	void setA(EntryMatrix);
	void setB(EntryMatrix);
	void setC(EntryMatrix);
	void setD(EntryMatrix);
	//void setX(Matrix);
	//void setU(Matrix);
	//void setX0(Matrix);
	//void setY(Matrix);
	//void setXdot(Matrix);

	// Calculate functions:
	Matrix calculateXdot(Matrix x, Matrix u);
	Matrix calculateY(Matrix x, Matrix u);
};

#endif /*SRC_STATESPACE_H*/