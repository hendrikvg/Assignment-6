#ifndef SRC_MATRIX_H
#pragma once
#define SRC_MATRIX_H

#include <iostream>
//#include <algorithm>
#include <vector>
#include "EntryMatrix.h"

class EntryMatrix; // Forward declare EntryMatrix

/// <summary>
/// Allows creation of Matrices and defines matrix operations for linear algebra needed for statespace dynamics and control.
/// </summary>
class Matrix
{
private:
	unsigned rowSize;
	unsigned colSize;
	std::vector<std::vector<double>> matrix;

public:
	Matrix() = default;
	Matrix(unsigned rows, unsigned columns, double initialValue);
	Matrix(const Matrix&);
	~Matrix();

	// Matrix operations
	Matrix operator+(Matrix);
	Matrix operator+(EntryMatrix B);
	Matrix operator-(Matrix);
	Matrix operator*(Matrix);
	//Matrix transpose(); // Not yet implemented

	//// Scalar Operations
	//Matrix operator+(double); // Not yet implemented
	//Matrix operator-(double); // Not yet implemented
	Matrix operator*(double); // Not yet implemented
	//Matrix operator/(double); // Not yet implemented

	// Other member functions
	double& operator()(const unsigned&, const unsigned&);
	unsigned getRows() const;
	unsigned getColumns() const;
	std::vector<double> getVector() const;
	void print() const;
	void diag(int);
};

#endif /*SRC_MATRIX_H*/