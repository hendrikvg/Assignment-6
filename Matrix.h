/*
==============================================================
 Filename    :  Matrix.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.3
 License     :  none.
 Description :  The aim of this file is to create a Matrix class that has operator
				overrides such that it behaves like a matrix.
==============================================================
*/
#ifndef SRC_MATRIX_H
#pragma once
#define SRC_MATRIX_H

#include <iostream>
//#include <algorithm>
#include <vector>
#include "EntryMatrix.h"

class EntryMatrix; // Forward declare EntryMatrix

/// <summary>
/// Allows creation of Matrices and defines matrix operations for linear 
/// algebra needed for statespace dynamics and control.
/// </summary>
class Matrix
{
private:
	unsigned rowSize;
	unsigned colSize;
	std::vector<std::vector<double>> matrix;

public:

	Matrix() = default;

	/// <summary>
	/// Matrix constructor that initializes a Matrix with rows and colums and
	/// an initial value for all entries.
	/// </summary>
	/// <param name="rows">The number of rows that the Matrix should have.</param>
	/// <param name="columns">The number of columns the Matrix should have.</param>
	/// <param name="initialValue">The value ever entry should have.</param>
	Matrix(unsigned rows, unsigned columns, double initialValue);

	/// <summary>
	/// Copy constructor that initializes a Matrix with the properties of another Matrix.
	/// </summary>
	/// <param name="B">The other matrix that gets copied.</param>
	Matrix(const Matrix&);

	//Destructor
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