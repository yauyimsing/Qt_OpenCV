#include "colorhistogram.h"

MatND ColorHistogram::getHistogram(const Mat &image)
{
    MatND hist;
    cv::calcHist(&image,
                 1,
                 channels,
                 Mat(),
                 hist,
                 3,
                 histSize,
                 ranges);
    return hist;
}

SparseMat ColorHistogram::getSparseHistogram(const Mat &image)
{
    SparseMat hist(3, histSize, CV_32F);
    calcHist(&image,
             1,
             channels,
             Mat(),
             hist,
             3,
             histSize,
             ranges);
    return hist;
}

Mat ColorHistogram::stretch(const Mat &image, int minValue)
{
    MatND hist = getHistogram(image);
    int imin = 0;
    for(; imin < histSize[0]; imin++)
    {
        cout << hist.at<float>(imin) << endl;
    }
}
Mat ColorHistogram::getHistogramImage(const Mat &image)
{
    return image;
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
    return histImg;
}
ColorHistogram::ColorHistogram()
{
    histSize[0] = histSize[1] = histSize[2] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    ranges[1] = hranges;
    ranges[2] = hranges;
    channels[0] = 0;
    channels[1] = 1;
    channels[2] = 2;
}
