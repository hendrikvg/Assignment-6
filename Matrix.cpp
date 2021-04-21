/*
==============================================================
 Filename    :  Matrix.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  6.1
 License     :  none.
 Description :  The aim of this file is to create a Matrix class that has operator
			   overrides such that it behaves like a matrix.
==============================================================
*/

#include "Matrix.h"

/// <summary>
/// Matrix constructor that initializes a Matrix with rows and colums and
/// an initial value for all entries.
/// </summary>
/// <param name="rows">The number of rows that the Matrix should have.</param>
/// <param name="columns">The number of columns the Matrix should have.</param>
/// <param name="initialValue">The value ever entry should have.</param>
Matrix::Matrix(unsigned rows, unsigned columns, double initialValue) : rowSize(rows), colSize(columns)
{
	matrix.resize(rowSize);
	for (unsigned row = 0; row < matrix.size(); row++)
	{
		matrix[row].resize(colSize, initialValue);
	}
}

/// <summary>
/// Copy constructor that initializes a Matrix with the properties of another Matrix.
/// </summary>
/// <param name="B">The other matrix that gets copied.</param>
Matrix::Matrix(const Matrix& B)
{
	this->colSize = B.getColumns();
	this->rowSize = B.getRows();
	this->matrix = B.matrix;
}

// Destructor
Matrix::~Matrix() {

}


// Matrix operations: 


/// <summary>
/// Matrix + operator override that enables adding up two Matrices.
/// </summary>
/// <param name="B">The other Matrix that gets added.</param>
/// <returns>The current Matrix object + B.</returns>
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
// Scalar Multiplication
Matrix Matrix::operator*(double B) {
	Matrix result(rowSize, colSize, 0.0);
	for (unsigned row = 0; row < rowSize; row++)
	{
		for (unsigned column = 0; column < colSize; column++)
		{
			result(row + 1, column + 1) = this->matrix[row][column] * B;
		}
	}
	return result;
}

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

/// <summary>
/// getVector() Returns the contents of the matrix as a vector.
/// </summary>
/// <returns>All contents of this Matrix object on one row.</returns>
std::vector<double> Matrix::getVector() const
{
	std::vector<double> vector;
	for (unsigned row = 0; row < rowSize; row++)
	{
		for (unsigned column = 0; column < colSize; column++)
		{
			vector.push_back(matrix[row][column]);
		}
	}
	return vector;
}

/// <summary>
/// Prints the Matrix.
/// </summary>
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


/// <summary>
/// Initializes the diagonal of a Matrix.
/// </summary>
/// <param name="input">Value to put on the diagonal.</param>
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