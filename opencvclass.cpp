#include "opencvclass.h"
#include <iostream>
#include "opencvfunction.h"
#include <opencv2/highgui.hpp>
#include <opencv/cv.h>

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

void OpenCvClass::putText2Image(Mat &image, String text, int textRow)
{
    putText(result, text, Point(50, textRow), FONT_HERSHEY_SIMPLEX|FONT_ITALIC, 1, Scalar(255, 0, 0));
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
    opencvfun::addLogo(image, result, "images/logo.png");
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
void OpenCvClass::filter(int filter)
{
    switch (filter) {
    case BOX_FILTER:
        boxFilter(image, result, -1, Size(5, 5));
        break;
    case BLUR:
        blur(image, result, Size(7, 7));
        break;
    case GAUSSIAN_BLUR:
        GaussianBlur(image, result, Size(5, 5), 0, 0);
        break;
    case MEDIAN_BLUR:
        medianBlur(image, result, 7);
        break;
    case BILATERAL_FILTER:
        bilateralFilter(image, result, 25, 25*2, 25/2);
        break;
    default:
        break;
    }
}

Rect OpenCvClass::floodFillImage()
{
    Rect ccomp;
    result = image.clone();
    floodFill(result, Point(result.cols / 2, result.rows / 2), Scalar(0, 0, 0), &ccomp,
              Scalar(20, 20, 20), Scalar(20, 20, 20));
    return ccomp;
}

void OpenCvClass::resizeImage(int zoom)
{
    switch(zoom)
    {
    case ZOOM_IN:
        resize(image, result, Size(image.cols*2, image.rows*2), (0, 0), (0, 0), INTER_AREA);
        break;
    case ZOOM_OUT:
        resize(image, result, Size(), 0.5, 0.5);
        break;
    case PYR_UP:
        pyrUp(image, result, Size(image.cols * 2, image.rows*2));
        break;
    case PYR_DOWN:
        pyrDown(image, result, Size(image.cols/2, image.rows/2));
        break;
    default:
        break;
    }
}

void OpenCvClass::thresholdImage()
{
    Mat imageGray;
    cvtColor(image, imageGray, CV_BGR2GRAY);
    threshold(imageGray, result, 128, 255, THRESH_BINARY);
}

void OpenCvClass::getImageInfo()
{
    this->textRow = 50;
    result = image.clone();
    String s_text;
    s_text += "channels: ";
    s_text += to_string(result.channels());
    putText2Image(result, s_text, this->textRow);
    this->textRow += 50;
    s_text = "depth: ";
    s_text += to_string(result.depth());
    putText2Image(result, s_text, this->textRow);
    this->textRow += 50;
}

void OpenCvClass::houghLinesImage()
{
    Mat midImage, dstImage;
    grayImage = imread("images/line.png");
    Canny(grayImage, midImage, 50, 200, 3);
    cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

    vector<Vec2f> lines;
    HoughLines(midImage, lines, 1, CV_PI / 180, 70, 0, 0);
    for(size_t i = 0; i < lines.size(); i++)
    {
        cout << "time: " << i << endl;
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        int factor = 1000;
        pt1.x = cvRound(x0 + factor * (-b));
        pt1.y = cvRound(y0 + factor * (a));
        pt2.x = cvRound(x0 - factor * (-b));
        pt2.y = cvRound(y0 - factor * (a));
        line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
    }
    result = dstImage;
}

void OpenCvClass::HoughCirclesImage()
{
    Mat image, midImage, dstImage;
    image = imread("images/circle.png");
    result = image;
    cvtColor(image, midImage, COLOR_BGR2GRAY);
    GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);
    vector<Vec3f> circles;
    HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
    for(size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(result, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        circle(result, center, radius, Scalar(155, 50, 255), 3, 8, 0);
    }

}

void OpenCvClass::remapImage()
{
    Mat map_x, map_y;
    map_x.create(image.size(), CV_32FC1);
    map_y.create(image.size(), CV_32FC1);
    for(int j = 0; j < image.rows; j++)
    {
        for(int i = 0; i < image.cols; i++)
        {
            if(i > image.cols / 2)
                map_x.at<float>(j, i) = static_cast<float>(i);
            else
                map_x.at<float>(j, i) = static_cast<float>(image.cols - i);
            map_y.at<float>(j, i) = static_cast<float>(j);
        }
    }
    remap(image, result, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
}

void OpenCvClass::equalizeHistImage()
{
    equalizeHist(grayImage, result);
}

void OpenCvClass::affineTransformImage()
{
    Point2f srcTriangle[3];
    Point2f dstTriangle[3];
    Mat rotMat(2, 3, CV_32FC1);
    Mat warpMat(2, 3, CV_32FC1);
    Mat srcImage, dstImage_warp, dstImage_warp_rotate;
    srcImage = this->image;
    dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());
    srcTriangle[0] = Point2f(0, 0);
    srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
    srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));
    /*
    dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0),
                             static_cast<float>(srcImage.rows*0.33));
    dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65),
                             static_cast<float>(srcImage.rows*0.35));
    dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15),
                             static_cast<float>(srcImage.rows*0.6));
                             */
    dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.33),
                             static_cast<float>(srcImage.rows*0.33));
    dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.67),
                             static_cast<float>(srcImage.rows*0.33));
    dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.33),
                             static_cast<float>(srcImage.rows*0.67));
    warpMat = getAffineTransform(srcTriangle, dstTriangle);
    warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());

    Point center = Point(dstImage_warp.cols / 2, dstImage_warp.rows / 2);
    double angle = -30;
    double scale = 1.1;
    rotMat = getRotationMatrix2D(center, angle, scale);
    warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size());

    result = dstImage_warp_rotate;
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

void OpenCvClass::contrastAndBright(double contrast, int bright)
{
    result = image.clone();
    for(int y = 0; y < result.rows; y++)
    {
        for(int x = 0; x < result.cols; x++)
        {
            for(int c = 0; c < 3; c++)
            {
                result.at<Vec3b>(y, x)[c]
                        = saturate_cast<uchar>(contrast * result.at<Vec3b>(y, x)[c] + bright);
            }
        }
    }
}

void OpenCvClass::LoadPicture()
{
    image = cv::imread(imgPath);
    cvtColor(image, grayImage, COLOR_RGB2GRAY);
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

void OpenCvClass::morphology(int method)
{
    checkImage();
    Mat element;
    switch(method)
    {
    case DILATE_OPERATION:
        element = getStructuringElement(MORPH_RECT, Size(17, 17));
        dilate(image, result, element);
        break;
    case ERODE_OPERATION:
        element = getStructuringElement(MORPH_RECT, Size(17, 17));
        erode(image, result, element);
        break;
    case OPEN_OPERATION:
        element = getStructuringElement(MORPH_RECT, Size(17, 17));
        morphologyEx(image, result, MORPH_OPEN, element);
        break;
    case CLOSE_OPERATION:
        element = getStructuringElement(MORPH_RECT, Size(17, 17));
        morphologyEx(image, result, MORPH_CLOSE, element);
        break;
    case TOP_HAT_OPERATION:
        element = getStructuringElement(MORPH_RECT, Size(17, 17));
        morphologyEx(image, result, MORPH_TOPHAT, element);
        break;
    case BLACK_HAT_OPERATION:
        element = getStructuringElement(MORPH_RECT, Size(17, 17));
        morphologyEx(image, result, MORPH_BLACKHAT, element);
        break;
    default:
        break;
    }


}


void OpenCvClass::openImage()
{
    checkImage();
    Mat element = getStructuringElement(MORPH_RECT, Size(17, 17));

}

void OpenCvClass::blurImage()
{
    checkImage();
    blur(image, result, Size(7, 7));
}

void OpenCvClass::getGrayImage()
{
    checkImage();
    cvtColor(image, result, COLOR_RGB2GRAY);
}

void OpenCvClass::contoursImage()
{
    Mat srcImage;
    cvtColor(image, srcImage, COLOR_RGB2GRAY);
    Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
    srcImage = srcImage > 200;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    int index = 0;
    for(; index >= 0; index = hierarchy[index][0])
    {
        Scalar color(rand() % 255, rand() % 255, rand() % 255);
        drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
    }
    result = dstImage;
}

void OpenCvClass::convexHullImage()
{
    Mat image(600, 600, CV_8UC3);
    RNG& rng = theRNG();
    int count = (unsigned)rng%100 + 3;
    vector<Point> points;
    for(int i = 0; i < count; i++)
    {
        Point point;
        point.x = rng.uniform(image.cols/4, image.cols*3/4);
        point.y = rng.uniform(image.rows/4, image.rows*3/4);
        points.push_back(point);
    }
    vector<int> hull;
    convexHull(Mat(points), hull, true);
    image = Scalar::all(0);
    for(int i =0; i < count; i++)
    {
        circle(image, points[i], 3, Scalar(rng.uniform(0, 255),
                                           rng.uniform(0, 255),
                                           rng.uniform(0, 255)),
               FILLED, LINE_AA);
    }
    int hullcount = (int)hull.size();
    Point point0 = points[hull[hullcount-1]];
    for(int i =0; i < hullcount; i++)
    {
        Point point = points[hull[i]];
        line(image, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
        point0 = point;
    }
    result = image;
}
void OpenCvClass::cannyImage()
{
    result.create(image.size(), image.type());
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    Mat edge;
    blur(grayImage, edge, Size(3, 3));
    Canny(edge, edge, 3, 9, 3);
    result = Scalar::all(0);
    grayImage.copyTo(result, edge);
}

void OpenCvClass::sobelImage()
{
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Sobel(image, grad_x, image.depth(), 1, 0, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    Sobel(image, grad_y, image.depth(), 0, 1, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, result);
}

void OpenCvClass::laplacianImage()
{
    Mat filterImage, grayImage, dstImage;
    GaussianBlur(image, filterImage, Size(3, 3), 0, 0, BORDER_DEFAULT);
    cvtColor(filterImage, grayImage, COLOR_RGB2GRAY);
    Laplacian(grayImage, dstImage, image.depth(), 3, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(dstImage, result);
}

void OpenCvClass::scharr()
{
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Scharr(image, grad_x, image.depth(), 1, 0, 1, 0, BORDER_DEFAULT);
    Scharr(image, grad_y, image.depth(), 0, 1, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, result);
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


