#include "StateSpace.h"

// Constructor
StateSpace::StateSpace(EntryMatrix A, EntryMatrix B, EntryMatrix C, EntryMatrix D) : 
	A(A), B(B), C(C), D(D)
{
	//Matrix x(A.getRows(), 1, 1.0);
	//Matrix u(B.getColumns(), 1, 0.0);
	//Matrix y(C.getRows(), 1, 0.0);
	//this->x = x;
	//this->u = u;
	//this->x0 = x;
	//this->y = y;
	//this->xdot = x;
}

// Copy Constructor
StateSpace::StateSpace(const StateSpace& stateSpace)
{
	this->A = stateSpace.getA();
	this->B = stateSpace.getB();
	this->C = stateSpace.getC();
	this->D = stateSpace.getD();
	//this->x = stateSpace.getX();
	//this->u = stateSpace.getU();
	//this->x0 = stateSpace.getX0();
	//this->y = stateSpace.getY();
	//this->xdot = stateSpace.getXdot();
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

//Matrix StateSpace::getX() const
//{
//	return this->x;
//}
//
//Matrix StateSpace::getU() const
//{
//	return this->u;
//}
//
//Matrix StateSpace::getX0() const
//{
//	return this->x0;
//}
//
//Matrix StateSpace::getY() const
//{
//	return this->y;
//}
//
//Matrix StateSpace::getXdot() const
//{
//	return this->xdot;
//}

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

//void StateSpace::setX(Matrix x)
//{
//	this->x = x;
//}
//
//void StateSpace::setU(Matrix u)
//{
//	this->u = u;
//}
//
//void StateSpace::setX0(Matrix x0)
//{
//	this->x0 = x0;
//}
//
//void StateSpace::setY(Matrix y)
//{
//	this->y = y;
//}
//
//void StateSpace::setXdot(Matrix xdot)
//{
//	this->xdot = xdot;
//}

Matrix StateSpace::calculateXdot(Matrix x, Matrix u)
{
	return A * x + B * u;
}

Matrix StateSpace::calculateY(Matrix x, Matrix u)
{
	return C * x + D * u;
}