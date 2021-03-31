#include <vector>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <string>
#include "Matrix.h"
#include "StateSpace.h"
#include "Simulator.h"
#include "Entry.h"
#include "EntryMatrix.h"
#include "ForwardEuler.h"
#include "Functions.h"
#include "Input.h"

#include "Test.h"

int main(int /*argc*/, char** /*argv*/) {
    std::cout << "HELLO WORLD\n";

    int nThreads = SDL_GetCPUCount();

    double t0 = 0;
    double dt = 0.01;
    double tEnd = 10;

    double C_dd = 0.1;
    //double C_dc = 1;
    double m_d = 3;
    //double m_c = 1;
    //double Fx = 1;
    //double Fy = 1;
    double const g = 9.81;

    Matrix x(5, 1, 0.0);
    Matrix u(2, 1, 0.0);
    u(1, 1) = 1;

    Input input(u);

    EntryMatrix A(5, 5, 0.0);
    A(1, 4) = 1.0;
    A(2, 5) = 1.0;
    A(4, 4) = Entry([&x, m_d, C_dd]() {return (1 / m_d) * (-C_dd * sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });
    A(5, 1) = Entry([&x, g]() {return (x(5, 1) == 0) ? -g : -g / x(5, 1); }); // bool ? this : that (conditional ternary operator)
    A(5, 5) = Entry([&x, m_d, C_dd]() {return (1 / m_d) * (-C_dd * sqrt(pow(x(4, 1), 2) + pow(x(5, 1), 2))); });
    ////A(6, 8) = 1;
    ////A(7, 9) = 1;
    ////A(8, 8) = (1 / m_c) * (-C_dc * sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2)));
    ////A(9, 9) = (1 / m_c) * (-C_dc * sqrt(pow(x(8, 1), 2) + pow(x(9, 1), 2)));

    EntryMatrix B(5, 2, 0.0);
    B(3, 2) = 1.0;
    B(4, 1) = Entry([&x, m_d]() {return (1 / m_d) * (-sin(x(3, 1))); });
    B(5, 1) = Entry([&x, m_d]() {return (1 / m_d) * (cos(x(3, 1))); });

    EntryMatrix C(5, 5, 0.0);
    C.diag(1);

    EntryMatrix D(5, 2, 0);

    StateSpace drone(A, B, C, D);

    x.print();
    ForwardEuler iets(&drone, t0, dt, tEnd);
    iets.integrate(x, u, x);
    x.print();


    //std::cout << nThreads;
 
    //SDL_Window* window = nullptr;
    //SDL_Renderer* renderer = nullptr;

    //SDL_Init(SDL_INIT_EVERYTHING);

    //// Create a Window in the middle of the screen
    //window = SDL_CreateWindow("Drone Simulation", SDL_WINDOWPOS_CENTERED,
    //    SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);

    //renderer = SDL_CreateRenderer(window, -1,
    //    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //system("pause");
    //SDL_Quit();
    return 0;
}



//#ifndef SRC_MATRIX_H
//#define SRC_MATRIX_H
//
//#include <vector>
//#include "Entry.h"
//
//template<typename T>
//class Matrix
//{
//private:
//	unsigned rowSize;
//	unsigned colSize;
//	std::vector<std::vector<T>> matrix;
//
//public:
//	Matrix(unsigned int rows = 1, unsigned int columns = 1, T initialValue = 0.0);
//	Matrix(const Matrix&);
//	~Matrix();
//
//	// Matrix operations
//	Matrix<T> operator+(Matrix<T>);
//	Matrix<T> operator-(Matrix<T>);
//	Matrix<T> operator*(Matrix<T>);
//	//Matrix transpose(); // Not yet implemented
//
//	//// Scalar Operations
//	//Matrix operator+(double); // Not yet implemented
//	//Matrix operator-(double); // Not yet implemented
//	//Matrix operator*(double); // Not yet implemented
//	//Matrix operator/(double); // Not yet implemented
//
//	// Other member functions
//	double& operator()(const unsigned&, const unsigned&);
//	unsigned getRows() const;
//	unsigned getColumns() const;
//	void print() const;
//	void diag(int);
//};
//
///// \file
///// Matrix.cpp
//
//#include "Matrix.h"
//#include <iostream>
//#include <algorithm>
//#include <vector>
//
//// Constructor
//template<typename T>
//Matrix<T>::Matrix(unsigned int rows, unsigned int columns, T initialValue)
//{
//	rowSize = rows;
//	colSize = columns;
//	matrix.resize(rowSize);
//	for (unsigned row = 0; row < matrix.size(); row++)
//	{
//		matrix[row].resize(colSize, initialValue);
//	}
//}
//
//// Copy Constructor
//template<typename T>
//Matrix<T>::Matrix(const Matrix& B)
//{
//	this->colSize = B.getColumns();
//	this->rowSize = B.getRows();
//	this->matrix = B.matrix;
//}
//
//// Destructor
//template<typename T>
//Matrix<T>::~Matrix() {
//
//}
//
//
//// Matrix operations
//// Addition of two matrices
//template<typename T>
//Matrix<T> Matrix<T>::operator+(Matrix B) {
//	Matrix sum(rowSize, colSize, 0.0);
//
//	for (unsigned row = 0; row < rowSize; row++)
//	{
//		for (unsigned column = 0; column < colSize; column++)
//		{
//			sum(row + 1, column + 1) = this->matrix[row][column] + B(row + 1, column + 1);
//		}
//	}
//	return sum;
//}
//
//// Subtraction of two matrices
//template<typename T>
//Matrix<T> Matrix<T>::operator-(Matrix B) {
//	Matrix difference(rowSize, colSize, 0.0);
//
//	for (unsigned row = 0; row < rowSize; row++)
//	{
//		for (unsigned column = 0; column < colSize; column++)
//		{
//			difference(row + 1, column + 1) = this->matrix[row][column] - B(row + 1, column + 1);
//		}
//	}
//	return difference;
//}
//
//// Multiplication of two matrices
//template<typename T>
//Matrix<T> Matrix<T>::operator*(Matrix B) {
//	Matrix product(rowSize, B.getColumns(), 0.0);
//	if (colSize == B.getRows())
//	{
//		for (unsigned rowA = 0; rowA < rowSize; rowA++)
//		{
//			for (unsigned colB = 0; colB < B.getColumns(); colB++)
//			{
//				for (unsigned colA = 0; colA < colSize; colA++)
//				{
//					product(rowA + 1, colB + 1) += matrix[rowA][colA] * B(colA + 1, colB + 1);
//				}
//			}
//		}
//		return product;
//	}
//	else
//	{
//		std::cerr << "Matrix dimensions do not agree for multiplication.";
//		return product;
//	}
//}
//
//// Scalar operations
//// Not implemented (yet)
//
//// Other member functions
//template<typename T>
//double& Matrix<T>::operator()(const unsigned& rowNr, const unsigned& colNr)
//{
//	return this->matrix[rowNr - 1][colNr - 1];
//}
//
//template<typename T>
//unsigned Matrix<T>::getRows() const
//{
//	return this->rowSize;
//}
//
//template<typename T>
//unsigned Matrix<T>::getColumns() const
//{
//	return this->colSize;
//}
//
//template<typename T>
//void Matrix<T>::print() const
//{
//	std::cout << "\n";
//	for (unsigned row = 0; row < rowSize; ++row)
//	{
//		for (unsigned column = 0; column < colSize; ++column)
//		{
//			if (column == colSize - 1)
//			{
//				std::cout << " " << matrix[row][column] << "\n";
//			}
//			else
//			{
//				std::cout << " " << matrix[row][column] << "\t";
//			}
//		}
//	}
//	std::cout << "\n";
//}
//
//template<typename T>
//void Matrix<T>::diag(int input)
//{
//	if (rowSize == colSize)
//	{
//		for (unsigned row = 0; row < rowSize; ++row)
//		{
//			matrix[row][row] = input;
//		}
//	}
//	else
//	{
//		std::cerr << "Cannot set diagonal of matrix as it is not square.";
//	}
//}
//
//
//#endif /*SRC_MATRIX_H*/