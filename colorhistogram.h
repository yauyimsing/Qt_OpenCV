#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include "opencv2/opencv.hpp"
#include "iostream"

using namespace std;
using namespace cv;

class ColorHistogram
{
private:
    int histSize[3];
    float hranges[2];
    const float* ranges[3];
    int channels[3];
    Mat stretch(const Mat &image, int minValue);
public:
    ColorHistogram();
    MatND getHistogram(const Mat& image);
    SparseMat getSparseHistogram(const Mat& image);
    Mat getHistogramImage(const Mat &image);
};

#endif // COLORHISTOGRAM_H
