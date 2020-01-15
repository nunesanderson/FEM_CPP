#include <iostream>
#include <stdexcept>
#include <lapacke.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
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
		case 1:
			ans = this->mat[0][0];
			break;
		case 2:
			ans = this->mat[0][0] * this->mat[1][1] - this->mat[1][0] * this->mat[0][1];
			break;
		default:
			throw std::invalid_argument("Determinant: Dimensions not supported. Received " + to_string(this->rows) + " x " + to_string(this->cols));
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
Matrix<T> Matrix<T>::Transpose()
{

	Matrix<T> ans(this->cols, this->rows);

	for (size_t i = 0; i < ans.rows; i++)
	{
		for (size_t j = 0; j < ans.cols; j++)
		{
			ans.mat[i][j] = this->mat[j][i];
		}
	}
	return ans;
}

template <class T>
Matrix<T> Matrix<T>::Inverse()
{

	// TODO: Implement a general interface for LAPACK
	Matrix<double> ans(this->rows, this->cols);
	switch (this->rows)
	{
	case 1:
		ans.mat[0][0] = 1.0 / this->mat[0][0];
		break;

	case 2:
	{
		// Calculate the determinant of the matrix
		double det = this->mat[0][0] * this->mat[1][1] - this->mat[0][1] * this->mat[1][0];
		double detinv = 1 / det;

		//Calculate the inverse of the matrix
		ans.mat[0][0] = +detinv * this->mat[1][1];
		ans.mat[1][0] = -detinv * this->mat[1][0];
		ans.mat[0][1] = -detinv * this->mat[0][1];
		ans.mat[1][1] = +detinv * this->mat[0][0];
		for (size_t i = 0; i < ans.rows; i++)
		{
			for (size_t j = 0; j < ans.cols; j++)
			{
				this->mat[i][j] = ans.mat[i][j];
			}
		}
	}
	break;

	default:
		throw std::invalid_argument("Matrix inverse: Dimensions not supported. Received " + to_string(this->rows) + " x " + to_string(this->cols));
		break;
	}

	return ans;
}

template <class T>
void Matrix<T>::write2DVectorToFile(vector<vector<int>> twoDArrayData, string path, string fileName)
{

	Messages messages;
	messages.logMessage("Writing data file " + fileName);

	string filePath(path + "/" + fileName + ".txt");
	ofstream myfile;
	myfile.open(filePath);
	for (vector<int> &this_vector : twoDArrayData)
	{
		size_t counter = 0;
		for (int &this_value : this_vector)
		{
			myfile << this_value;
			if (counter < this_vector.size() - 1)
			{
				myfile << " ";
			}
			counter++;
		}
		myfile << "\n";
	}
	myfile.close();

	messages.logMessage("Writing data file " + fileName + ": Done");
}

template <class T>
void Matrix<T>::writeToFile(string path, string fileName)
{

	Messages messages;
	messages.logMessage("Writing data file " + fileName);

	string filePath(path + "/" + fileName + ".txt");

	ofstream myfile;
	myfile.open(filePath);

	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < this->cols; j++)
		{
			myfile << this->mat[i][j];
			if (j < this->cols - 1)
			{
				myfile << " ";
			}
		}
		myfile << "\n";
	}

	myfile.close();

	messages.logMessage("Writing data file " + fileName + ": Done");
}

template <class T>
void Matrix<T>::SolveLinearSystem(Matrix &lhs, Matrix &rhs)
{

	Messages msg;
	msg.logMessage("Solving linear system.");

	if ((lhs.rows == lhs.cols) && (lhs.cols == rhs.cols))
	{
	}

	else
	{
		throw std::invalid_argument("The dimensions of the system do not match: lhs.rows - lhs.cols - rhs.cols: " + to_string(lhs.rows) + "-" + to_string(lhs.cols) + "-" + to_string(rhs.cols));
	}

	// Ccnvertes the 2D array to 1D array
	double *lhs1D;
	lhs1D = new double[lhs.rows * lhs.cols];

	for (size_t i = 0; i < lhs.rows; i++)
	{
		for (size_t j = 0; j < lhs.cols; j++)
		{
			// cout<<i * lhs.cols + j<<endl;
			lhs1D[i * lhs.cols + j] = lhs.mat[i][j];
		}
	}

	double *rhs1D = rhs.mat[0];

	// Lapack
	int N = lhs.rows, NRHS = 1, LDA = N, LDB = NRHS;
	int ipiv[N], info;

	info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, N, NRHS, lhs1D, LDA, ipiv, rhs1D, LDB);

	*rhs.mat = rhs1D;
	msg.logMessage("Solving linear system: Done");
}

template <class T>
void Matrix<T>::SetLineValue(int line, T value)
{

	for (size_t k = 0; k < this->cols; k++)
		this->mat[line][k] = value;
}

template <class T>
void Matrix<T>::SetValue(T value)
{

	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t k = 0; k < this->cols; k++)
		{
			this->mat[i][k] = value;
		}
	}
}

// TODO: implement for 2*Matrix
template <class T>
Matrix<T> Matrix<T>::operator*(T const &b)
{

	Matrix<T> result(this->rows, this->cols);
	result.rows = this->rows;
	result.cols = this->cols;

	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
		{
			result.mat[i][j] = this->mat[i][j] * b;
		}

	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &b)
{

	int r1 = this->rows;
	int c1 = this->cols;
	int r2 = b.rows;
	int c2 = b.cols;

	Matrix<T> result(r1, c2);
	result.SetValue(0);

	for (int i = 0; i < r1; ++i)
		for (int j = 0; j < c2; ++j)
			for (int k = 0; k < c1; ++k)
			{
				result.mat[i][j] += this->mat[i][k] * b.mat[k][j];
			}

	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &b)
{
	if (this->rows == b.rows && this->cols == b.cols)
	{

		Matrix<T> result(this->rows, this->cols);

		for (int i = 0; i < this->rows; ++i)
			for (int j = 0; j < this->cols; ++j)
				result.mat[i][j] = this->mat[i][j] + b.mat[i][j];

		return result;
	}
	else
	{
		throw std::invalid_argument("The dimensions dont match.");
	}
}
template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &b)
{
	if (this->rows == b.rows && this->cols == b.cols)
	{

		Matrix<T> result(this->rows, this->cols);

		for (int i = 0; i < this->rows; ++i)
			for (int j = 0; j < this->cols; ++j)
				result.mat[i][j] = this->mat[i][j] - b.mat[i][j];

		return result;
	}
	else
	{
		throw std::invalid_argument("The dimensions dont match.");
	}
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