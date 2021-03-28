/// \file
/// Matrix.cpp

#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include <vector>

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

void Matrix::showMatrix()
{
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
				std::cout << " " << matrix[row][column] << " ";
			}
		}
	}
	std::cout << "\n";
}

double& Matrix::operator()(const unsigned& rowNr, const unsigned& colNr)
{
	return this->matrix[rowNr][colNr];
}

unsigned Matrix::getRows() const
{
	return this->rowSize;
}

unsigned Matrix::getColumns() const
{
	return this->colSize;
}

// Addition of two matrices
Matrix Matrix::operator+(Matrix& B) {
	Matrix sum(colSize, rowSize);
	
	for (unsigned row = 0; row < rowSize; row++)
	{
		for (unsigned column = 0; column < colSize; column++)
		{
			sum(row, column) = this->matrix[row][column] + B(row, column);
		}
	}
	return sum;
}

// Subtraction of two matrices
Matrix Matrix::operator-(Matrix& B) {
	Matrix difference(colSize, rowSize);

	for (unsigned row = 0; row < rowSize; row++)
	{
		for (unsigned column = 0; column < colSize; column++)
		{
			difference(row, column) = this->matrix[row][column] - B(row, column);
		}
	}
	return difference;
}

// Multiplication of two matrices
Matrix Matrix::operator*(Matrix& B) {
	Matrix product(rowSize, B.getColumns(), 0.0);
	if (colSize == B.getRows())
	{
		for (unsigned rowA = 0; rowA < rowSize; rowA++)
		{
			for (unsigned columnB = 0; columnB < B.getColumns(); columnB++)
			{
				for (unsigned columnA = 0; columnA < colSize; columnA++)
				{
					double temporaryValue = matrix[rowA][columnA] * B(columnA,columnB)
				}
			}
		}
	} 
	else
	{
		std::cerr << "Matrix dimensions do not agree for multiplication.";
		return product;
	}
}