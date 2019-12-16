#include <string>
#include <vector>
using namespace std;
using std::string;



#ifndef _MATRIX_INCLUDED_
#define _MATRIX_INCLUDED_

template <class T>
class Matrix
{

private:
    T **Matrix_alloc(int n, int m);

public:
    Matrix();
    Matrix(int n, int m);
    Matrix(const Matrix &);

    T **mat;
    int rows;
    int cols;
    T detVal;

    void Alloc(int n, int m);
    void SolveLinearSystem(Matrix &, Matrix &);
    Matrix Transpose();
    Matrix Inverse();
    void SetLineValue(int,T);
    void SetValue(T);
    void print_matrix();
    void calcDet();
    void writeToFile(string path, string fileName);
    void write2DVectorToFile(vector<vector<int>> twoDArrayData, string path, string fileName);

    



// operator overloads
    Matrix &operator=(Matrix);
    Matrix operator*(const Matrix &);
    Matrix operator+(const Matrix &);
    Matrix operator*(T const &);

    ~Matrix();
};

#endif