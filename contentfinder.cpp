#include "contentfinder.h"

ContentFinder::ContentFinder()
    :threshold(-1.0f)
{
    ranges[0] = hranges;
    ranges[1] = hranges;
    ranges[2] = hranges;
}

void ContentFinder::setThreshold(float t)
{
    threshold = t;
}

float ContentFinder::getThreshold()
{
    return threshold;
}

void ContentFinder::setHistogram(const MatND &h)
{
    isSparse = false;
    histogram = h;
    normalize(histogram, histogram, 1.0);
}
void ContentFinder::setHistogram(const SparseMat &h)
{
    isSparse = true;
    shistogram = h;
    normalize(histogram, histogram, 1.0, NORM_L2);
}

Mat ContentFinder::find(const Mat &image, float minValue, float maxValue, int *channels, int dim)
{
    cv::Mat result;

    hranges[0]= minValue;
    hranges[1]= maxValue;

    for (int i=0; i<dim; i++)
        this->channels[i]= channels[i];

    if (isSparse) { // call the right function based on histogram type

       cv::calcBackProject(&image,
                  1,            // we only use one image at a time
                  channels,     // vector specifying what histogram dimensions belong to what image channels
                  shistogram,   // the histogram we are using
                  result,       // the resulting back projection image
                  ranges,       // the range of values, for each dimension
                  255.0         // the scaling factor is chosen such that a histogram value of 1 maps to 255
       );

    } else {

       cv::calcBackProject(&image,
                  1,            // we only use one image at a time
                  channels,     // vector specifying what histogram dimensions belong to what image channels
                  histogram,    // the histogram we are using
                  result,       // the resulting back projection image
                  ranges,       // the range of values, for each dimension
                  255.0         // the scaling factor is chosen such that a histogram value of 1 maps to 255
       );
    }

    // Threshold back projection to obtain a binary image
    if (threshold>0.0)
        cv::threshold(result, result, 255*threshold, 255, cv::THRESH_BINARY);

    return result;
}

Mat ContentFinder::find(const Mat& image)
{
    Mat result;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    channels[0] = 0;
    channels[1] = 1;
    channels[2] = 2;
    if(isSparse)
    {
        calcBackProject(&image,
                        1, channels,
                        shistogram,
                        result,
                        ranges,
                        255.0);

    }
    else
    {
        calcBackProject(&image,
                        1,
                        channels,
                        histogram,
                        result,
                        ranges,
                        255.0);
    }
    if(threshold > 0.0)
        cv::threshold(result, result, 255*threshold, 255, THRESH_BINARY);
    return result;
}

