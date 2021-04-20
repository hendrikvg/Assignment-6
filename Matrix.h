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

#include <iostream> // For std::cout
#include <vector> // To store the matrix
#include "EntryMatrix.h" // To enable operations on EntryMatrices

class EntryMatrix; // Forward declare EntryMatrix, necessary for compilation

/// <summary>
/// Allows creation of Matrices and defines matrix operations for linear 
/// algebra needed for statespace dynamics and control.
/// </summary>
class Matrix
{
private:
	unsigned int rowSize; // Storing rowsize and colsize prevents us from
	unsigned int colSize; // having to calculate the size again for every operation
	std::vector<std::vector<double>> matrix; // Stores the actual matrix values

public:
	// Constructors
	Matrix() = default; // For declaring Matrices
	Matrix(unsigned int rows, unsigned int columns, double initialValue); // Initiating Matrices
	Matrix(const Matrix&); // Copy constructor

	// Destructor
	~Matrix();

	// Matrix operations
	Matrix operator+(Matrix);
	Matrix operator+(EntryMatrix B); // Enables adding a normal and EntryMatrix
	// as if they were both normal matrices.
	Matrix operator-(Matrix);
	Matrix operator*(Matrix);
	//Matrix transpose(); // Not yet implemented

	//// Scalar Operations
	//Matrix operator+(double); // Not yet implemented
	//Matrix operator-(double); // Not yet implemented
	Matrix operator*(double);
	//Matrix operator/(double); // Not yet implemented

	// Other member functions
	double& operator()(const unsigned&, const unsigned&); // Allows for MATLAB-like
	// indexing
	unsigned getRows() const;
	unsigned getColumns() const;
	std::vector<double> getVector() const;
	void print() const; // Displays Matrix
	void diag(double); // Initializes the diagonal of the Matrix
};

#endif /*SRC_MATRIX_H*/