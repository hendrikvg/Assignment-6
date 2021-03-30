#ifndef SRC_ENTRYMATRIX_H
#define SRC_ENTRYMATRIX_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "Entry.h"
#include "Matrix.h"

class EntryMatrix
{
private:
	unsigned rowSize;
	unsigned colSize;
	std::vector<std::vector<Entry>> matrix;

public:
	EntryMatrix(unsigned int rows, unsigned int columns, Entry initialValue);
	EntryMatrix(const EntryMatrix&);
	~EntryMatrix();

	// Matrix operations
	Matrix operator+(EntryMatrix);
	Matrix operator+(Matrix);
	Matrix operator-(EntryMatrix);
	Matrix operator-(Matrix);
	Matrix operator*(EntryMatrix);
	Matrix operator*(Matrix);
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