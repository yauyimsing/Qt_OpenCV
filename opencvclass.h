#ifndef OPENCVCLASS_H
#define OPENCVCLASS_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

namespace OpenCV{
// filter method
#define BOX_FILTER 0
#define BLUR 1
#define GAUSSIAN_BLUR 2
#define MEDIAN_BLUR 3
#define BILATERAL_FILTER 4

// morthology method
#define DILATE_OPERATION 0
#define ERODE_OPERATION 1
#define OPEN_OPERATION 2
#define CLOSE_OPERATION 3
#define TOP_HAT_OPERATION 4
#define BLACK_HAT_OPERATION 5

// resize
#define ZOOM_IN 0
#define ZOOM_OUT 1
#define PYR_UP 2
#define PYR_DOWN 3
}

class OpenCvClass
{
public:
    OpenCvClass();
private:
    const char* imgPath = "images/en.jpg";
    double startDuration;
    double endDuration;
    Mat image;
    Mat grayImage;
    Mat result;
    bool checkImage();
    VideoCapture* capture;
    Mat frame;
    void createAlphaMat(Mat &mat);
    enum Channels{RED = 0, GREEN = 1, BLUE = 2};
    int textRow = 0;
private:
    void putText2Image(Mat &image, String text, int textRow);

public:
    void LoadPicture();
    void tickStart();
    void tickEnd();
    double getDuration();
    Mat& getImage();
    Mat& getResult();
    void morphology(int method = DILATE_OPERATION);
    void openImage();
    void blurImage();
    void cannyImage();
    void sobelImage();
    void laplacianImage();
    void scharr();
    void openCapture();
    void closeCapture();
    Mat & getFrame();
    void setImage(Mat& image);
    void createAlphaMat();
    void addLogo();
    void colorReduce(int div = 32);
    void splitChannels(int channel = RED);
    void contrastAndBright(double contrast = 1, int bright = 0);
    void filter(int filter = BOX_FILTER);
    Rect floodFillImage();
    void resizeImage(int zoom = ZOOM_IN);
    void thresholdImage();
    void getImageInfo();
    void houghLinesImage();
    void HoughCirclesImage();
    void remapImage();
    void equalizeHistImage();
    void affineTransformImage();
    void getGrayImage();
    void contoursImage();
    void convexHullImage();
    void minAreaRectImage();
    void minEnclosingCircleImage();
    void momentImage();
    void watershedImage();
    void calcHS2DHistImage();
    void calc1DHistImage();
    void calc1D3CHistImage();
    void histogramCompare();
    void calcBackProjectImage();
    void matchTemplateImage();
};

#endif // OPENCVCLASS_H
