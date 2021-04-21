/*
==============================================================
 Filename    :  EntryMatrix.h
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.1
 License     :  none.
 Description :  This class works identically to Matrix.h, except it will always return
				a matrix when doing computations
==============================================================
*/
#ifndef SRC_ENTRYMATRIX_H
#define SRC_ENTRYMATRIX_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "Entry.h"
#include "Matrix.h"


/// <summary>
/// Matrix class that can take variables and constants. Defines matrix operations for use in integration and dynamics calculations.
/// </summary>
class EntryMatrix
{
private:
	unsigned rowSize;
	unsigned colSize;
	std::vector<std::vector<Entry>> matrix;

public:
	EntryMatrix() = default;

	/// <summary>
	/// Constructor for Entry matrix, needs number of rows and columns and the initialization values.
	/// </summary>
	/// <param name="rows">number of desired rows</param>
	/// <param name="columns">number of desired columns</param>
	/// <param name="initialValue">initial value for all values in matrix</param>
	EntryMatrix(unsigned int rows, unsigned int columns, double initialValue);


	EntryMatrix(const EntryMatrix&);
	~EntryMatrix();

	// Matrix operations
	Matrix operator+(EntryMatrix);	//addition
	Matrix operator+(Matrix);		//addition
	Matrix operator-(EntryMatrix);	//substraction
	Matrix operator-(Matrix);		//substraction
	Matrix operator*(EntryMatrix);	//multiplicaiton
	Matrix operator*(Matrix);		//multiplication
	//Matrix transpose(); // Not yet implemented

	//// Scalar Operations
	//Matrix operator+(double); // Not yet implemented
	//Matrix operator-(double); // Not yet implemented
	//Matrix operator*(double); // Not yet implemented
	//Matrix operator/(double); // Not yet implemented

	// Other member functions
	Entry& operator()(const unsigned&, const unsigned&);
	unsigned getRows() const;
	unsigned getColumns() const;
	void print();
	void diag(Entry);
};

#endif /*SRC_MATRIX_H*/