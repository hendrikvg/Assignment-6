/// \file
/// Matrix.cpp

#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include <vector>

// Constructor

Matrix::Matrix(unsigned rows, unsigned columns, double initialValue)
{
	rowSize = rows;
	colSize = columns;
	matrix.resize(rowSize);
	for (unsigned row = 0; row < matrix.size(); row++)
		{
			matrix[row].resize(colSize, initialValue);
		}
}

// Copy Constructor
Matrix::Matrix(const Matrix& B)
{
	this->colSize = B.getColumns();
	this->rowSize = B.getRows();
	this->matrix = B.matrix;
}

// Destructor
Matrix::~Matrix() {

}


// Matrix operations
// Addition of two matrices
Matrix Matrix::operator+(Matrix B) {
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
Matrix Matrix::operator-(Matrix B) {
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
Matrix Matrix::operator*(Matrix B) {
	Matrix product(rowSize, B.getColumns(), 0.0);
	if (colSize == B.getRows())
	{
		for (unsigned rowA = 0; rowA < rowSize; rowA++)
		{
			for (unsigned colB = 0; colB < B.getColumns(); colB++)
			{
				for (unsigned colA = 0; colA < colSize; colA++)
				{
					product(rowA + 1, colB + 1) += matrix[rowA][colA] * B(colA + 1, colB + 1);
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
double& Matrix::operator()(const unsigned& rowNr, const unsigned& colNr)
{
	return this->matrix[rowNr - 1][colNr - 1];
}

unsigned Matrix::getRows() const
{
	return this->rowSize;
}

unsigned Matrix::getColumns() const
{
	return this->colSize;
}

void Matrix::print() const
{
	std::cout << "\n";
	for (unsigned row = 0; row < rowSize; ++row)
	{
		for (unsigned column = 0; column < colSize; ++column)
		{
			if (column == colSize - 1)
			{
				std::cout << " " << matrix[row][column] << "\n";
			}
			else
			{
				std::cout << " " << matrix[row][column] << "\t";
			}
		}
	}
	std::cout << "\n";
}

void Matrix::diag(int input)
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
