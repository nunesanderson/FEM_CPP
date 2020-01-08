#include <iostream>
#include <string>
// using namespace std;

/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/

#ifndef _POST_PROCESSING_INCLUDED_
#define _POST_PROCESSING_INCLUDED_

class PostProcessing
{

private:
    Mesh meshData;
    Matrix<double> solution;
    string filePath;

public:
    PostProcessing(string filesPath, string meshFileName, Matrix<double> &solution);
    Matrix<double> getGradPoint(double x, double y);
    void getGradLine(double x_start, double x_end, double y_start, double y_end, int numberPoints);
    // ~PostProcessing();
};

#endif