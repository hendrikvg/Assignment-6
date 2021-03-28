#include "StateSpace.h"

// Empty Constructor
StateSpace::StateSpace() {};

// Constructor
StateSpace::StateSpace(Matrix A, Matrix B, Matrix C, Matrix D)
{
	this->A = A;
	this->B = B;
	this->C = C;
	this->D = D;
}

// Constructor
StateSpace::StateSpace(Matrix A, Matrix B, Matrix C, Matrix D, Matrix E = 0)
{
	this->A = A;
	this->B = B;
	this->C = C;
	this->D = D;
	this->E = E;
}

Matrix StateSpace::getA()
{
	return this->A;
}

Matrix StateSpace::getB()
{
	return this->B;
}

Matrix StateSpace::getC()
{
	return this->C;
}

Matrix StateSpace::getD()
{
	return this->D;
}

Matrix StateSpace::getE()
{
	return this->E;
}

//// Copy Constructor
//StateSpace::StateSpace(const StateSpace& B)
//{
//	this->A = B.getColumns();
//	this->A = B.getRows();
//	this->C = B.matrix;
//}

