#ifndef COLORDETECTCONTROLLER_H
#define COLORDETECTCONTROLLER_H
#include "colordetector.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
class ColorDetectController
{
private:
    ColorDetector* cdetect;
    static ColorDetectController* singleton;
    Mat image;
    Mat result;
public:
    ColorDetectController();
    ~ColorDetectController();
    void setColorDistanceThreshold(int distance);
    int getColorDistanceThreshold() const;
    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    void getTargetColor(unsigned char& red, unsigned char& green, unsigned char& blue);
    bool setInputImage(std::string filename, int flags = IMREAD_COLOR);
    const Mat getInputImage() const;
    void process();
    const Mat getLastResult() const;
    static ColorDetectController* getInstance();
    static void destroy();
    static ColorDetectController *getSingleton();
    static void setSingleton(ColorDetectController *value);
};

#endif // COLORDETECTCONTROLLER_H
