/*
==============================================================
 Filename    :  EntryMatrix.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.3
 License     :  none.
 Description :  This file handles the implementation of EntryMatrix.h
				This class works identically to Matrix.h, except it will always return
				a matrix when doing computations
==============================================================
*/
#include "EntryMatrix.h"

// Constructor
EntryMatrix::EntryMatrix(unsigned int rows, unsigned int columns, double initialValue) : rowSize(rows), colSize(columns)
{
	Entry initialEntryValue(initialValue);
	matrix.resize(rowSize);
	for (unsigned row = 0; row < matrix.size(); row++)
	{
		matrix[row].resize(colSize, initialEntryValue);
	}
}

// Copy Constructor
EntryMatrix::EntryMatrix(const EntryMatrix& B)
{
	this->colSize = B.getColumns();
	this->rowSize = B.getRows();
	this->matrix = B.matrix;
}

// Destructor
EntryMatrix::~EntryMatrix() {

}


// Matrix operations
// Addition of two matrices
Matrix EntryMatrix::operator+(EntryMatrix B) {
	Matrix sum(rowSize, colSize, 0.0);

	for (unsigned row = 0; row < rowSize; row++)
	{
		for (unsigned column = 0; column < colSize; column++)
		{
			sum(row + 1, column + 1) = this->matrix[row][column] + B(row + 1, column + 1).calculate();
		}
	}
	return sum;
}

// Addition of two matrices
Matrix EntryMatrix::operator+(Matrix B) {
	Matrix sum(rowSize, colSize, 0.0);

	for (unsigned row = 0; row < rowSize; row++)
	{
		for (unsigned column = 0; column < colSize; column++)
		{
			sum(row + 1, column + 1) = this->matrix[row][column] + B(row + 1, column + 1);
		}
	}
	return sum;
}

// Subtraction of two matrices
Matrix EntryMatrix::operator-(EntryMatrix B) {
	Matrix difference(rowSize, colSize, 0.0);

	for (unsigned row = 0; row < rowSize; row++)
	{
		for (unsigned column = 0; column < colSize; column++)
		{
			difference(row + 1, column + 1) = this->matrix[row][column] - B(row + 1, column + 1).calculate();
		}
	}
	return difference;
}

// Subtraction of two matrices
Matrix EntryMatrix::operator-(Matrix B) {
	Matrix difference(rowSize, colSize, 0.0);

	for (unsigned row = 0; row < rowSize; row++)
	{
		for (unsigned column = 0; column < colSize; column++)
		{
			difference(row + 1, column + 1) = this->matrix[row][column] - B(row + 1, column + 1);
		}
	}
	return difference;
}

// Multiplication of two matrices
Matrix EntryMatrix::operator*(EntryMatrix B) {
	Matrix product(B.getRows(), B.getColumns(), 0.0);
	if (colSize == B.getRows())
	{
		for (unsigned rowA = 0; rowA < rowSize; rowA++)
		{
			for (unsigned colB = 0; colB < B.getColumns(); colB++)
			{
				for (unsigned colA = 0; colA < colSize; colA++)
				{
					product(rowA + 1, colB + 1) += matrix[rowA][colA].calculate() * B(colA + 1, colB + 1).calculate();
				}
			}
		}
		return product;
	}
	else
	{
		std::cerr << "Matrix dimensions do not agree for multiplication.";
		return product;
	}
}

// Multiplication of two matrices
Matrix EntryMatrix::operator*(Matrix B) {
	Matrix product(rowSize, B.getColumns(), 0.0);
	if (colSize == B.getRows())
	{
		for (unsigned rowA = 0; rowA < rowSize; rowA++)
		{
			for (unsigned colB = 0; colB < B.getColumns(); colB++)
			{
				for (unsigned colA = 0; colA < colSize; colA++)
				{
					product(rowA + 1, colB + 1) += matrix[rowA][colA].calculate() * B(colA + 1, colB + 1);
				}
			}
		}
		return product;
	}
	else
	{
		std::cerr << "Matrix dimensions do not agree for multiplication.";
		return product;
	}
}

// Scalar operations
// Not implemented (yet)

// Other member functions
Entry& EntryMatrix::operator()(const unsigned& rowNr, const unsigned& colNr)
{
	return this->matrix[rowNr - 1][colNr - 1];
}

unsigned EntryMatrix::getRows() const
{
	return this->rowSize;
}

unsigned EntryMatrix::getColumns() const
{
	return this->colSize;
}

void EntryMatrix::print()
{
	std::cout << "\n";
	for (unsigned row = 0; row < rowSize; ++row)
	{
		for (unsigned column = 0; column < colSize; ++column)
		{
			if (column == colSize - 1)
			{
				std::cout << " " << matrix[row][column].calculate() << "\n";
			}
			else
			{
				std::cout << " " << matrix[row][column].calculate() << "\t";
			}
		}
	}
	std::cout << "\n";
}

void EntryMatrix::diag(Entry input)
{
	if (rowSize == colSize)
	{
		for (unsigned row = 0; row < rowSize; ++row)
		{
			matrix[row][row] = input;
		}
	}
	else
	{
		std::cerr << "Cannot set diagonal of matrix as it is not square.";
	}
}
