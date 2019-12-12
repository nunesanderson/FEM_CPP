#include <iostream>
#include <string>
#include <time.h>
#include <vector>
/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Messages.h"
#include "../include/Matrix.h"
#include "Matrix.cpp"
#include "../include/ShapeFunctions.h"
#include "../include/PerformanceTestes.h"

using namespace std;

void PerformanceTestes::VectorMatrixMult()
{

    int n = 2 * 1000;
    time_t start, end;
    Messages msg;

    Matrix<double> matMatrix1(n, n);
    Matrix<double> matMatrix2(n, n);
    Matrix<double> ansMatrix(n, n);
    vector<vector<double>> matVector1;
    vector<vector<double>> matVector2;
    vector<vector<double>> ansVector;

    // Populate the arrays
    for (size_t i = 0; i < n; i++)
    {
        vector<double> vectorLine1;
        vector<double> vectorLine2;
        vector<double> vectorLineAns;
        for (size_t j = 0; j < n; j++)
        {
            matMatrix1.mat[i][j] = 1;
            matMatrix2.mat[i][j] = 1;
            vectorLine1.push_back(1);
            vectorLine2.push_back(1);
            vectorLineAns.push_back(0);
        }
        matVector1.push_back(vectorLine1);
        matVector2.push_back(vectorLine2);
        ansVector.push_back(vectorLineAns);
    }

    // Matrix class multiplication
    time(&start);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
            {
                ansMatrix.mat[i][j] += matMatrix1.mat[i][k] * matMatrix2.mat[k][j];
            }

    time(&end);
    double dif = difftime(end, start);
    msg.logMessage("Matrix -- Time:" + to_string(dif) + "s");

    // Vector class multiplication
    time(&start);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
            {
                ansVector[i][j] += matVector1[i][k] * matVector2[k][j];
            }

    time(&end);
    dif = difftime(end, start);
    msg.logMessage("Vector -- Time:" + to_string(dif) + "s");
    /*
========================================
Data:
int n = 5 * 1000 * 1000 * 100;
Intel® Core™ i5-7300U CPU @ 2.60GHz

Results:
[10:09:47] Vector -- Time:27.000000s
[10:10:00] Matrix -- Time:13.000000s
*/
}

void PerformanceTestes::vector_matrix()

{
    int n = 5 * 1000 * 1000 * 100;

    Messages msg;

    time_t start, end;
    time(&start);

    for (int i = 0; i < n; i++)
    {
        vector<double> test_vector;
        test_vector.push_back(1.0);
        test_vector.push_back(1.0);
        test_vector.push_back(1.0);
    }

    time(&end);
    double dif = difftime(end, start);
    msg.logMessage("Vector -- Time:" + to_string(dif) + "s");

    time(&start);
    for (int i = 0; i < n; i++)
    {
        Matrix<double> test_matrix(1, 3);
        test_matrix.mat[0][0] = 1.0;
        test_matrix.mat[0][1] = 1.0;
        test_matrix.mat[0][2] = 1.0;
    }

    time(&end);
    dif = difftime(end, start);
    msg.logMessage("Matrix -- Time:" + to_string(dif) + "s");

    /*
========================================
Data:
int n = 5 * 1000 * 1000 * 100;
Intel® Core™ i5-7300U CPU @ 2.60GHz

Results:
[10:04:56] Vector -- Time:28.000000s
[10:05:09] Matrix -- Time:13.000000s 
*/
}