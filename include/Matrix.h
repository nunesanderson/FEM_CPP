#include <string>
#include <vector>
using namespace std;
using std::string;

#ifndef _MATRIX_INCLUDED_
#define _MATRIX_INCLUDED_

/**
 * Provides 2D array object
 * with contiguous memory allocation
 * ...
 * @param T: array type
 */
template <class T>
class Matrix
{

private:
    T **Matrix_alloc(int n, int m);

public:
    /**
 * Creates a 2D array with (0,0) rows and columns
 */
    Matrix();

    /**
 * Creates a 2D array with (rows,cols)
 * ...
 *  @param n: number of rows
 * @param m: number of cols
 */
    Matrix(int n, int m);
    Matrix(const Matrix &);

    ///Access to the array
    T **mat;

    ///Access the number of rows
    int rows;

    ///Access the number of cols
    int cols;

    ///Access the determinant
    T detVal;

    ///Allocate a Matrix
    void Alloc(int n, int m);

    /**
     * Solve a linear system
     * using the Lapack DGESV
     * ...
     * @param lhs: left hand side
     * @param rhd: right hand side
     * @return Return the result in the rhs
     */
    void SolveLinearSystem(Matrix &lhs, Matrix &rhs);

    ///Transpose the matrix
    Matrix Transpose();

    ///Inverse a matrix
    Matrix Inverse();

    /**
     * Set a value to a entire line of the matrix
     * ...
     * @param line: line to set
     * @param value: value to set the entire line
     */
    void SetLineValue(int line, T value);

    ///Set a value to the entire matrix
    void SetValue(T);

    ///Print the matrix
    void print_matrix();

    ///Calculates the determinant
    void calcDet();

    /**
     * Writes a matrix to a txt file
     * ...
     * @param path: directory
     * @param fileName: file name
     */
    void writeToFile(string path, string fileName);

    /**
     * Writes a vector<vector<int>> to a txt file
     * 
     * @param twoDArrayData: data to write
     * @param path: directory
     * @param fileName: file name
     */
    void write2DVectorToFile(vector<vector<int>> twoDArrayData, string path, string fileName);

    // operator overloading: =Matrix<T>
    Matrix &operator=(Matrix);

    // operator overloading: Matrix<T> *(matmult) Matrix<T>
    Matrix operator*(const Matrix &);

    // operator overloading: Matrix<T> + Matrix<T>
    Matrix operator+(const Matrix &);

    // operator overloading: Matrix<T> - Matrix<T>
    Matrix operator-(const Matrix &);

    // operator overloading: Matrix<T> * real
    Matrix operator*(T const &);

    ~Matrix();
};

#endif