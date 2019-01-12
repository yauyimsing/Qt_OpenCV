#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <opencv2/opencv.hpp>
using namespace cv;

class ColorDetector
{
private:
    int minDist;
    cv::Vec3b target;
    Mat converted;
    Mat result;
    int getDistance(const cv::Vec3b&) const;
public:
    ColorDetector();
    Mat process(const Mat&);
    void setColorDistanceThreshold(int);
    int getColorDistanceThreshold() const;
    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    void setTargetColor(Vec3b color);
    Vec3b getTargetColor() const;
};

#endif // COLORDETECTOR_H
