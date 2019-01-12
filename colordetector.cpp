#include "colordetector.h"
#include <iostream>
using namespace std;

ColorDetector::ColorDetector():minDist(100)
{
    target[0] = target[1] = target[2] = 128;
}
Mat ColorDetector::process(const Mat& image)
{
    result.create(image.rows, image.cols, CV_8U);
    converted.create(image.rows, image.cols, image.type());
    cvtColor(image, converted, CV_BGR2Lab);
    cv::Mat_<cv::Vec3b>::const_iterator it = converted.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itend = converted.end<cv::Vec3b>();
    cv::Mat_<uchar>::iterator itout = result.begin<uchar>();
    //int size = itend - it;
    cout << "end: " << itend.ptr << "size:" << itend - it << endl;
    for (; it != itend; it++, itout++)
    {
        //cout << "it: " << it.ptr << endl;
        //cout << "times: " << size - i++ << endl;
        if (getDistance(*it) < minDist)
        {
            *itout = 255;
        }
        else
        {
            *itout = 0;
        }
    }
    return result;
}

void ColorDetector::setColorDistanceThreshold(int distance)
{
    if(distance < 0)
        distance = 0;
    minDist = distance;
}

int ColorDetector::getColorDistanceThreshold() const
{
    return minDist;
}

void ColorDetector::setTargetColor(unsigned char red, unsigned char green, unsigned char blue)
{
    /*
    target[2] = red;
    target[1] = green;
    target[0] = blue;
    */
    Mat tmp(1, 1, CV_8UC3);
    tmp.at<Vec3b>(0, 0)[0] = blue;
    tmp.at<Vec3b>(0, 0)[1] = green;
    tmp.at<Vec3b>(0, 0)[2] = red;
    cvtColor(tmp, tmp, CV_BGR2Lab);
    target = tmp.at<Vec3b>(0, 0);
}

void ColorDetector::setTargetColor(Vec3b color)
{
    target = color;
}

Vec3b ColorDetector::getTargetColor() const
{
    return target;
}

int ColorDetector::getDistance(const cv::Vec3b & color) const
{
    int value = abs(color[0] - target[0])
        + abs(color[1] - target[1])
        + abs(color[2] - target[2]);
    //cout << "v: " << value << endl;
    return value;
}
