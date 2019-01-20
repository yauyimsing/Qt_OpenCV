#include "opencvclass.h"
#include <iostream>
#include "opencvfunction.h"

using namespace std;

OpenCvClass::OpenCvClass()
{

}

bool OpenCvClass::checkImage()
{
    if(image.empty())
    {
        image = Mat(100, 100, CV_8UC3, Scalar(255, 0, 0));
        cout << "image empty" << endl;
    }
}

void OpenCvClass::createAlphaMat(Mat &mat)
{
    for(int i = 0; i < mat.rows; ++i)
    {
        for(int j = 0; j < mat.cols; ++j)
        {
            Vec4b &rgba = mat.at<Vec4b>(i, j);
            rgba[0] = UCHAR_MAX;
            rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) /
                                           ((float)mat.cols)*UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) /
                                           ((float)mat.rows)*UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(100);
        }
    }
}

void OpenCvClass::createAlphaMat()
{
    Mat mat(480, 640, CV_8UC4);
    createAlphaMat(mat);
    vector<int>compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    try
    {
        imwrite("alpha.png", mat, compression_params);
        result = mat;

    }
    catch(runtime_error &ex)
    {
        cout << ex.what() << endl;

    }
}

void OpenCvClass::addLogo()
{
    opencvfun::addLogo(image, result, "images\\logo.png");
}

void OpenCvClass::colorReduce(int div)
{
    result = image.clone();
    int method = 2;
    switch (method) {
    case 0:
    {
        int rowNumber = result.rows;
        int colNumber = result.cols * result.channels();
        for(int i = 0; i < rowNumber; i++)
        {
            uchar* data = result.ptr<uchar>(i);
            for(int j = 0; j < colNumber; j++)
            {
                data[j] = data[j] / div * div + div/2;
            }
        }
        break;
    }
    case 1:
    {
        Mat_<Vec3b>::iterator it = result.begin<Vec3b>();
        Mat_<Vec3b>::iterator itend = result.end<Vec3b>();
        for(; it != itend; ++it)
        {
            (*it)[0] = (*it)[0] / div * div + div / 2;
            (*it)[1] = (*it)[1] / div * div + div / 2;
            (*it)[2] = (*it)[2] / div * div + div / 2;
        }
        break;
    }
    case 2:
    {
        int rowNumber = result.rows;
        int colNumber = result.cols;
        for(int i = 0; i < rowNumber; i++)
        {
            for(int j = 0; j < colNumber; j++)
            {
                result.at<Vec3b>(i, j)[0]
                        = result.at<Vec3b>(i, j)[0] / div * div + div/2;
                result.at<Vec3b>(i, j)[1]
                        = result.at<Vec3b>(i, j)[2] / div * div + div/2;
                result.at<Vec3b>(i, j)[2]
                        = result.at<Vec3b>(i, j)[2] / div * div + div/2;
            }
        }
    }
    default:
        break;
    }
}

void OpenCvClass::splitChannels(int channel)
{
    vector<Mat> channels;
    split(image, channels);
    switch(channel)
    {
    case RED:
        channels.at(0) = Scalar(0);
        channels.at(1) = Scalar(0);
        merge(channels, result);
        //result = channels.at(2);
        break;
    case GREEN:
        channels.at(0) = Scalar(0);
        channels.at(2) = Scalar(0);
        merge(channels, result);
        //result = channels.at(1);
        break;
    case BLUE:
        channels.at(1) = Scalar(0);
        channels.at(2) = Scalar(0);
        merge(channels, result);
        //result = channels.at(0);
        break;
    default:
        break;
    }
}

void OpenCvClass::LoadPicture()
{
    image = cv::imread(imgPath);
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

Mat& OpenCvClass::getImage()
{
    checkImage();
    return image;
}

Mat& OpenCvClass::getResult()
{
    if(result.empty())
    {
        result = Mat(100, 100, CV_8UC3, Scalar(255, 0, 0));
        cout << "result empty" << endl;
    }
    return result;
}

void OpenCvClass::erodeImage()
{
    checkImage();
    Mat element = getStructuringElement(MORPH_RECT, Size(17, 17));
    erode(image, result, element);
}

void OpenCvClass::blurImage()
{
    checkImage();
    blur(image, result, Size(7, 7));
}

void OpenCvClass::cannyImage()
{
    result.create(image.size(), image.type());
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    Mat edge;
    blur(grayImage, edge, Size(3, 3));
    Canny(edge, result, 3, 9, 3);
}

void OpenCvClass::openCapture()
{
    capture = new VideoCapture(0);
}

void OpenCvClass::closeCapture()
{
    capture->release();
    delete capture;
}

Mat &OpenCvClass::getFrame()
{
    if(!capture->isOpened())
    {
        cout << "VideoCapture is not opened." << endl;
        return frame;
    }
    //frame = Mat(100, 100, CV_8UC3, Scalar(0, 0, 255));
    *capture >> frame;
    imshow("capture", frame);
    return frame;
}

void OpenCvClass::setImage(Mat &image)
{
    this->image = image;
}


