#include "histogram1d.h"
#include <iostream>
using namespace std;

Histogram1D::Histogram1D()
{
    histSize[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    channels[0] = 0;
    dim = 256;
    lut.create(1, dim, CV_8U);
    for(int i = 0; i < dim; i++)
    {
        lut.at<uchar>(i) = dim - i;
        //lut.at<uchar>(i) = 255.0*((i-0)/(255-0)+0.5);
    }
}

Mat Histogram1D::getHistogram(const Mat &image)
{
    MatND hist;
    calcHist(&image,
             1, // calculate histogram of single image
             channels, // channels
             Mat(), // not using picture as mask
             hist, // returned histogram
             1, // 1D histogram
             histSize, // number of xiang
             ranges // range of pixel
             );
    return hist;
}

Mat Histogram1D::getHistogramImage(const Mat &image)
{
    MatND hist = getHistogram(image);
    double maxVal = 0;
    double minVal = 0;
    minMaxLoc(hist, &minVal, &maxVal, 0, 0);
    Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));
    int hpt = static_cast<int>(0.9*histSize[0]);
    for(int h=0; h < histSize[0]; h++)
    {
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal*hpt/maxVal);
        line(histImg, Point(h, histSize[0]),
                Point(h, histSize[0] - intensity),
                Scalar::all(0));
    }
    cout << "h1" << endl;
    return histImg;
}

Mat Histogram1D::stretch(const Mat &image, int minValue)
{
    MatND hist = getHistogram(image);
    int imin = 0;
    for(; imin < histSize[0]; imin++)
    {
        //cout << imin << ":" << hist.at<float>(imin) << endl;
        if(hist.at<float>(imin)>minValue)
            break;
    }
    int imax = histSize[0] -1;
    for(;imax>=0;imax--)
    {
        if(hist.at<float>(imax)>minValue)
            break;
    }
    int dim(256);
    Mat lookup(1,
               &dim,
               CV_8U);
    for(int i=0;i<256;i++)
    {
        if(i<imin)
            lookup.at<uchar>(i) = 0;
        else if(i > imax)
            lookup.at<uchar>(i) = 255;
        else
            lookup.at<uchar>(i) = static_cast<uchar>(
                        255.0*(i-imin)/(imax-imin)+0.5);
    }
    Mat result;
    result = applyLookUp(image, lookup);
    return result;
}

Mat Histogram1D::applyLookUp(const Mat &image)
{
    Mat result;
    LUT(image, lut, result);
    return result;
}
Mat Histogram1D::applyLookUp(const Mat &image, const Mat &lookup)
{
    Mat result;
    LUT(image, lookup, result);
    return result;
}


