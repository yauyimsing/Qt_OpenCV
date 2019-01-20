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
    Mat image;
    Mat result;
    bool checkImage();
    VideoCapture* capture;
    Mat frame;
    void createAlphaMat(Mat &mat);
    enum Channels{RED = 0, GREEN = 1, BLUE = 2};
public:
    void LoadPicture();
    void tickStart();
    void tickEnd();
    double getDuration();
    Mat& getImage();
    Mat& getResult();
    void erodeImage();
    void blurImage();
    void cannyImage();
    void openCapture();
    void closeCapture();
    Mat & getFrame();
    void setImage(Mat& image);
    void createAlphaMat();
    void addLogo();
    void colorReduce(int div = 32);
    void splitChannels(int channel = RED);
};

#endif // OPENCVCLASS_H
