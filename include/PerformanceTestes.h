#ifndef _PERFORMANCE_TESTS_INCLUDED_
#define _PERFORMANCE_TESTS_INCLUDED_

class PerformanceTestes
{

public:
    ///Performance test of allocanting a high number of small vector<double> and Matrix<double>
    void vector_matrix();

    //Performance test of a matrix multiplication. Maxtrix vs std::vector
    void VectorMatrixMult();
};

#endif