#ifndef CONTENTFINDER_H
#define CONTENTFINDER_H
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class ContentFinder
{
private:
    float hranges[2];
    const float* ranges[3];
    int channels[3];
    float threshold;
    MatND histogram;
    SparseMat shistogram;
    bool isSparse;
public:
    ContentFinder();
    void setThreshold(float t);
    float getThreshold();
    void setHistogram(const MatND &h);
    Mat find(const Mat &image, float minValue, float maxValue, int *channels, int dim);
    Mat find(const Mat &image);
    void setHistogram(const SparseMat &h);
};

#endif // CONTENTFINDER_H
