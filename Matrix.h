/*
==============================================================
 Filename    :  Matrix.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  none.
 Description :  The aim of this file is to create a Matrix class that has operator
				overrides such that it behaves like a matrix.
==============================================================
*/

#ifndef SRC_MATRIX_H
#pragma once
#define SRC_MATRIX_H

#include <iostream>
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
	// Constructors
	Matrix() = default;
	Matrix(unsigned rows, unsigned columns, double initialValue);
	Matrix(const Matrix&);

	// Destructor
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
	double& operator()(const unsigned&, const unsigned&); // Allows for MATLAB-like
	// indexing
	unsigned getRows() const;
	unsigned getColumns() const;
	std::vector<double> getVector() const;
	void print() const; // Displays Matrix
	void diag(int); // Initializes the diagonal of the Matrix
};

#endif /*SRC_MATRIX_H*/