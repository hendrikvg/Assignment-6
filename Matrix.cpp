/*
==============================================================
 Filename    :  Matrix.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
				Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  1.0
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
Matrix::Matrix(unsigned int rows, unsigned int columns, double initialValue) : rowSize(rows), colSize(columns)
{
	matrix.resize(rowSize); // Create required number of rows.
	for (unsigned row = 0; row < matrix.size(); row++) // For every row...
	{
		matrix[row].resize(colSize, initialValue); // Create required number of
		// columns with initial value.
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

/// <summary>
/// Destructor, destroys the Matrix object.
/// </summary>
Matrix::~Matrix() {

}


// Matrix operations

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

/// <summary>
/// Matrix + operator override that enables adding up a Matrix and an EntryMatrix.
/// </summary>
/// <param name="B">The EntryMatrix that gets added.</param>
/// <returns>The current Matrix object + B.</returns>
Matrix Matrix::operator+(EntryMatrix B)
{
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

/// <summary>
/// Matrix - operator override that enables subtracting two Matrices.
/// </summary>
/// <param name="B">The Matrix that gets subtracted.</param>
/// <returns>The current Matrix object - B.</returns>
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

/// <summary>
/// Matrix * operator override that enables doing Matrix multiplications.
/// </summary>
/// <param name="B">The other Matrix that gets multiplied with.</param>
/// <returns>The current Matrix object * B.</returns>
Matrix Matrix::operator*(Matrix B) {
	Matrix product(rowSize, B.getColumns(), 0.0);
	if (colSize == B.getRows()) // Check whether dimensions agree for multiplication
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

/// <summary>
/// Matrix * operator override that enables scalar multiplication.
/// </summary>
/// <param name="B">Scalar of type double.</param>
/// <returns>The current Matrix object * B.</returns>
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

/// <summary>
/// Matrix () operator override that enables Matrix indexing like in MATLAB.
/// </summary>
/// <param name="rowNr">Row you want to retrieve/manipulate (starts on 1).</param>
/// <param name="colNr">Column you want to retrieve/manipulate (starts on 1).</param>
/// <returns>Matrix(rowNumber, colNumber)</returns>
double& Matrix::operator()(const unsigned& rowNumber, const unsigned& colNumber)
{
	return this->matrix[rowNumber - 1][colNumber - 1];
}

/// <summary>
/// getRows() returns the number of rows of this Matrix object.
/// </summary>
/// <returns>Number of rows of this Matrix object.</returns>
unsigned Matrix::getRows() const
{
	return this->rowSize;
}

/// <summary>
/// getColumns() returns the number of columns of this Matrix object.
/// </summary>
/// <returns>Number of columns of this Matrix object.</returns>
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
void Matrix::diag(double input)
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