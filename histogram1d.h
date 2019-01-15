#ifndef HISTOGRAM1D_H
#define HISTOGRAM1D_H

#include "opencv2/opencv.hpp"

using namespace cv;

class Histogram1D
{
private:
    int histSize[1];
    float hranges[2];
    const float* ranges[1];
    int channels[1];
    int dim;
    Mat lut;
public:
    Histogram1D();
    Mat getHistogram(const Mat& image);
    Mat getHistogramImage(const Mat& image);
    Mat stretch(const Mat& image, int minValue = 0);
    Mat applyLookUp(const Mat& image);
    Mat applyLookUp(const Mat& image, const Mat& lookup);
    void hCalcBackProject(const Mat& image, const Mat &imageROI, Mat &result);

};

#endif // HISTOGRAM1D_H
