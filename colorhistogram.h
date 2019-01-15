#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

class ColorHistogram
{
private:
    int histSize[3];
    float hranges[2];
    const float* ranges[3];
    int channels[3];
public:
    ColorHistogram();
    Mat getHistogram(const Mat& image);
    cv::SparseMat getSparseHistogram(const cv::Mat &image);
    cv::MatND getabHistogram(const cv::Mat &image);
    cv::MatND getHueHistogram(const cv::Mat &image);
    cv::Mat colorReduce(const cv::Mat &image, int div = 64);
};

#endif // COLORHISTOGRAM_H
