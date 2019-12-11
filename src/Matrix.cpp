#include <iostream>
#include <stdexcept>
//using namespace std;
/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Matrix.h"
#include "../include/Messages.h"

template <class T>
T **Matrix<T>::Matrix_alloc(int n, int m)
{
	T **mat = new T *[n];
	if (n == 0 or m == 0)
		return mat;
	mat[0] = new T[n * m];

	for (int i = 1; i < n; i++)
		mat[i] = &mat[0][i * m];

	return mat;
}

template <class T>
Matrix<T>::Matrix(int n, int m)
{
	mat = Matrix_alloc(n, m);
	rows = n;
	cols = m;
	detVal = 0;
}

template <class T>
void Matrix<T>::Alloc(int n, int m)
{

	mat = Matrix_alloc(n, m);
	rows = n;
	cols = m;
	detVal = 0;
}

template <class T>
Matrix<T>::Matrix()
{
	mat = Matrix_alloc(0, 0);
	rows = 0;
	cols = 0;
	detVal = 0;
}

template <class T>
void Matrix<T>::print_matrix()
{

	for (int i = 0; i < rows; i += 1)
	{
		for (int j = 0; j < cols; j += 1)
		{
			std::cout << this->mat[i][j] << " ";
			if (j == cols - 1)
			{
				std::cout << std::endl;
			}
		}
	}
}

template <class T>
Matrix<T>::~Matrix()
{
	if (rows >= 1 and cols >= 1)
		delete[] mat[0];
	delete[] mat;
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &b)
{
	mat = Matrix_alloc(b.rows, b.cols);
	rows = b.rows;
	cols = b.cols;
	for (int K = 0; K < rows; ++K)
		for (int L = 0; L < cols; ++L)
			mat[K][L] = b.mat[K][L];
}

template <class T>
void Matrix<T>::calcDet()
{

	T ans;

	if (this->rows == this->cols)
	{
		switch (rows)
		{
		case 2:
			ans = this->mat[0][0] * this->mat[1][1] - this->mat[1][0] * this->mat[0][1];
			break;
		default:
			throw std::invalid_argument("Only for 2x2 matrices.");
			break;
		}
	}
	else
	{
		throw std::invalid_argument("The number of rows and cols should be the same.");
	}
	this->detVal = ans;
}

template <class T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> b)
{
	if (rows and cols)
		delete[] this->mat[0];
	delete[] this->mat;

	this->mat = b.mat;
	this->rows = b.rows;
	this->cols = b.cols;
	this->detVal = b.detVal;

	b.mat = NULL;
	b.rows = 0;
	b.cols = 0;
	b.detVal = 0;

	return *this;
}
