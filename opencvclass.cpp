#include "opencvclass.h"

OpenCvClass::OpenCvClass()
{

}

Mat OpenCvClass::LoadPicture()
{
    IplImage* image = cvLoadImage(imgPath);
    cv::Mat mat = cv::cvarrToMat(image);
    //cvReleaseImage(&image);
    //Mat mat2 = cv::imread(imgPath);
    return mat;
}
