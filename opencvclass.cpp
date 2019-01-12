#include "opencvclass.h"

OpenCvClass::OpenCvClass()
{

}

Mat OpenCvClass::LoadPicture()
{
    //IplImage* image = cvLoadImage(imgPath);
    //cv::Mat mat = cv::cvarrToMat(image);
    //cvReleaseImage(&image);
    Mat mat = cv::imread(imgPath);
    return mat;
}

void OpenCvClass::tickStart()
{
    this->startDuration = static_cast<double>(cv::getTickCount());
}

void OpenCvClass::tickEnd()
{
    this->endDuration = static_cast<double>(cv::getTickCount());
}

double OpenCvClass::getDuration()
{
    return (endDuration - startDuration) / cv::getTickFrequency() * 1000;
}


