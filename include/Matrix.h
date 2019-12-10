
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
    T **mat;
    int rows;
    int cols;

    void print_matrix();
	Matrix(const Matrix&);
	Matrix& operator=(Matrix);
    ~Matrix();
};

#endif