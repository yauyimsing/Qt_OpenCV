#ifndef OPENCVCLASS_H
#define OPENCVCLASS_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

class OpenCvClass
{
public:
    OpenCvClass();
private:
    const char* imgPath = "D:\\picture\\en.jpg";
    double startDuration;
    double endDuration;
public:
    Mat LoadPicture();
    void tickStart();
    void tickEnd();
    double getDuration();
};

#endif // OPENCVCLASS_H
