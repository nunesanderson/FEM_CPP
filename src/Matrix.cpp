#include <iostream>
using namespace std;

/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Matrix.h"
#include "../include/Messages.h"

template <class T>
T **Matrix<T>::Matrix_alloc(int n, int m)
{
	T **mat = new T *[n];
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
}

template <class T>
Matrix<T>::Matrix()
{
	mat = Matrix_alloc(0, 0);
	rows = 0;
	cols = 0;
}

template <class T>
void Matrix<T>::print_matrix()
{

	for (int i = 0; i < rows; i += 1)
	{
		for (int j = 0; j < cols; j += 1)
		{
			std::cout << mat[i][j] << " ";
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
	if (rows > 1)
	{
		delete[] mat[0];
		delete[] mat;
	}
	else
	{
		delete[] mat[0];
	}
}