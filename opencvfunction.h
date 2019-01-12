#ifndef OPENCVFUNCTION_H
#define OPENCVFUNCTION_H
#include <opencv2/opencv.hpp>
using namespace cv;

#define LOGOPATH "images\\logo.png"
namespace opencvfun
{
    void salt(Mat& image, int n = 1000);
    void colorReduce(const Mat image, Mat& resultImage, int div = 64);
    void getColorChannel(const Mat image, Mat& result, int channel = 0);
    void sharpen(const Mat& image, Mat& result);
    void sharpen2D(const Mat& image, Mat& result);
    void imageChangeAdd(const Mat& image, Mat& result, int channel = 0, int value = 0);
    void addLogo(const Mat& image, Mat& result, char* logo = LOGOPATH);
    void ColorDetector(Mat&, Mat&, Vec3b = Vec3b(128, 128, 128), int minDist = 100);
    int getDistance(const Vec3b&, const Vec3b&);
}

#endif // OPENCVFUNCTION_H
