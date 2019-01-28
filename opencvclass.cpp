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

void OpenCvClass::minAreaRectImage()
{
    Mat image(600, 600, CV_8UC3);
    RNG& rng = theRNG();
    int count = rng.uniform(3, 103);
    vector<Point> points;
    for(int i = 0; i < count; i++)
    {
        Point point;
        point.x = rng.uniform(image.cols/4, image.cols*3/4);
        point.y = rng.uniform(image.rows/4, image.rows*3/4);
        points.push_back(point);
    }
    RotatedRect box = minAreaRect(points);
    Point2f vertex[4];
    box.points(vertex);
    image = Scalar::all(0);
    for(int i = 0; i < count; i++)
    {
        circle(image, points[i], 3, Scalar(rng.uniform(0, 255),
                                           rng.uniform(0, 255),
                                           rng.uniform(0, 255)),
               FILLED, LINE_AA);
    }
    for(int i = 0; i < 4; i++)
    {
        line(image, vertex[i], vertex[(i+1)%4], Scalar(100, 200, 211), 2, LINE_AA);
    }
    result = image;
}

void OpenCvClass::minEnclosingCircleImage()
{
    Mat image(600, 600, CV_8UC3);
    RNG& rng = theRNG();
    int count = rng.uniform(3, 103);
    vector<Point> points;
    for(int i = 0; i < count; i++)
    {
        Point point;
        point.x = rng.uniform(image.cols/4, image.cols*3/4);
        point.y = rng.uniform(image.rows/4, image.rows*3/4);
        points.push_back(point);
    }
    Point2f center;
    float radius = 0;
    minEnclosingCircle(Mat(points), center, radius);
    image = Scalar::all(0);
    for(int i = 0; i < count; i++)
    {
        circle(image, points[i], 3, Scalar(rng.uniform(0, 255),
                                           rng.uniform(0, 255),
                                           rng.uniform(0, 255)),
               FILLED, LINE_AA);
    }
    circle(image, center, cvRound(radius), Scalar(rng.uniform(0, 255),
                                                  rng.uniform(0, 255),
                                                  rng.uniform(0, 255)),
                      2, LINE_AA);
    result = image;
}

void OpenCvClass::momentImage()
{
    Mat grayImage;
    Mat cannyMat;
    int threshold = 100;
    RNG& rng = theRNG();
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat image = imread("images/half_circle.png");
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    blur(grayImage, grayImage, Size(3, 3));
    Canny(grayImage, cannyMat, threshold, threshold*2, 3);
    findContours(cannyMat, contours, hierarchy,
                 RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    vector<Moments> mu(contours.size());
    for(unsigned int i = 0; i < contours.size(); i++)
    {
        mu[i] = moments(contours[i], false);
    }
    vector<Point2f> mc(contours.size());
    for(unsigned int i = 0; i < contours.size(); i++)
    {
        mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00),
                        static_cast<float>(mu[i].m01 / mu[i].m00));
    }
    Mat drawing = Mat::zeros(cannyMat.size(), CV_8UC3);

    for(unsigned int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255));
        if(arcLength(contours[i], true) > 1)
        {
            drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
            circle(drawing, mc[i], 4, color, -1, 8, 0);
            cout << "area" << i << ": " << contourArea(contours[i]) << endl;
            cout << "length" << i << ": " << arcLength(contours[i], true) << endl;
        }
    }

    result = drawing;
}

void OpenCvClass::watershedImage()
{
    Mat srcImage, grayImage, maskImage;
    this->image.copyTo(srcImage);
    cvtColor(srcImage, maskImage, COLOR_BGR2GRAY);
    cvtColor(maskImage, grayImage, COLOR_GRAY2BGR);
    maskImage = Scalar::all(0);
    int i, j, compCount = 0;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //findContours(g);
}

void OpenCvClass::calcHS2DHistImage()
{
    Mat srcImage = this->image;
    Mat hsvImage;
    cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
    int hueBinNum = 30;
    int saturationBinNum = 32;
    int histSize[] = {hueBinNum, saturationBinNum};
    float hueRanges[] = {0, 180};
    float saturationRanges[] = {0, 256};
    const float* ranges[] = {hueRanges, saturationRanges};
    MatND dstHist;
    int channels[] = {0, 1};
    calcHist(&hsvImage,
             1,
             channels,
             Mat(),
             dstHist,
             2,
             histSize,
             ranges,
             true,
             false);
    double maxValue = 0;
    minMaxLoc(dstHist, 0, &maxValue, 0, 0);
    int scale = 10;
    Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum*scale, CV_8UC3);
    for(int hue = 0; hue < hueBinNum; hue++)
    {
        for(int saturation = 0; saturation < saturationBinNum; saturation++)
        {
            float binValue = dstHist.at<float>(hue, saturation);
            int intensity = cvRound(binValue*255/maxValue);
            rectangle(histImg, Point(hue*scale, saturation*scale),
                      Point((hue+1)*scale - 1, (saturation+1)*scale - 1),
                      Scalar::all(intensity), FILLED);
        }
    }
    result = histImg;
}

void OpenCvClass::calc1DHistImage()
{
    Mat srcImage = this->image;
    srcImage = this->grayImage;
    MatND dstHist;
    int dims = 1;
    float hranges[] = {0, 255};
    const float* ranges[] = {hranges};
    int size = 256;
    int channels = 0;
    calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
    int scale = 1;
    Mat dstImage(size*scale, size, CV_8U, Scalar(0));
    double minValue = 0;
    double maxValue = 0;
    minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
    int hpt = saturate_cast<int>(0.9 * size);
    for(int i = 0; i < 256; i++)
    {
        float binValue = dstHist.at<float>(i);
        int realValue = saturate_cast<int>(binValue*hpt/maxValue);
        rectangle(dstImage, Point(i*scale, size-1), Point((i+1)*scale-1, size-realValue), Scalar(255));

    }
    result = dstImage;
}

void OpenCvClass::calc1D3CHistImage()
{
    Mat srcImage = this->image;
    int bins = 256;
    int hist_size[] = {bins};
    float range[] = {0, 256};
    const float* ranges[] = {range};
    MatND redHist, greenHist, blueHist;
    int channels_r[] = {0};
    int channels_g[] = {1};
    int channels_b[] = {2};
    calcHist(&srcImage, 1, channels_r, Mat(), redHist, 1, hist_size, ranges, true, false);
    calcHist(&srcImage, 1, channels_g, Mat(), greenHist, 1, hist_size, ranges, true, false);
    calcHist(&srcImage, 1, channels_b, Mat(), blueHist, 1, hist_size, ranges, true, false);
    double maxValue_red, maxValue_green, maxValue_blue;
    minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
    minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
    minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
    int scale = 1;
    int histHeight = 256;
    Mat histImage = Mat::zeros(histHeight, bins*3, CV_8UC3);
    for(int i = 0; i < bins; i++)
    {
        float binValue_red = redHist.at<float>(i);
        float binValue_green = greenHist.at<float>(i);
        float binValue_blue = blueHist.at<float>(i);
        int intensity_red = cvRound(binValue_red*histHeight/maxValue_red);
        int intensity_green = cvRound(binValue_green*histHeight/maxValue_green);
        int intensity_blue = cvRound(binValue_blue*histHeight/maxValue_blue);
        rectangle(histImage, Point(i*scale, histHeight-1),
                  Point((i+1)*scale-1, histHeight - intensity_red),
                  Scalar(255, 0, 0));
        rectangle(histImage, Point((i+bins)*scale, histHeight-1),
                  Point((i+bins+1)*scale-1, histHeight - intensity_green),
                  Scalar(0, 255, 0));
        rectangle(histImage, Point((i+bins*2)*scale, histHeight-1),
                  Point((i+bins*2+1)*scale-1, histHeight - intensity_blue),
                  Scalar(0, 0, 255));
    }
    result = histImage;
}

void OpenCvClass::histogramCompare()
{
    string path = "images/book_resource_opencv3_programming_enter/";
    string path_base = path + "chapter9_compare_base.jpg";
    string path_compare0 = path + "chapter9_compare_compare0.jpg";
    string path_compare1 = path + "chapter9_compare_compare1.jpg";
    Mat srcImage_base, hsvImage_base;
    Mat srcImage_compare0, hsvImage_compare0;
    Mat srcImage_compare1, hsvImage_compare1;
    Mat hsvImage_halfDown;
    srcImage_base = imread(path_base);
    srcImage_compare0 = imread(path_compare0);
    srcImage_compare1 = imread(path_compare1);
    imshow("base", srcImage_base);
    imshow("compare0", srcImage_compare0);
    imshow("compare1", srcImage_compare1);
    cvtColor(srcImage_base, hsvImage_base, COLOR_BGR2HSV);
    cvtColor(srcImage_compare0, hsvImage_compare0, COLOR_BGR2HSV);
    cvtColor(srcImage_compare1, hsvImage_compare1, COLOR_BGR2HSV);
    hsvImage_halfDown = hsvImage_base(Range(hsvImage_base.rows/2, hsvImage_base.rows-1),
                                      Range(0, hsvImage_base.cols - 1));
    int h_bins = 50; int s_bins = 60;
    int histSize[] = {h_bins, s_bins};
    float h_ranges[] = {0, 256};
    float s_ranges[] = {0, 180};
    const float* ranges[] = {h_ranges, s_ranges};
    int channels[] = {0, 1};
    MatND baseHist;
    MatND halfDownHist;
    MatND compare0Hist;
    MatND compare1Hist;
    calcHist(&hsvImage_base, 1, channels, Mat(),
             baseHist, 2, histSize, ranges, true, false);
    calcHist(&hsvImage_halfDown, 1, channels, Mat(),
             halfDownHist, 2, histSize, ranges, true, false);
    calcHist(&hsvImage_compare0, 1, channels, Mat(),
             compare0Hist, 2, histSize, ranges, true, false);
    calcHist(&hsvImage_compare1, 1, channels, Mat(),
             compare1Hist, 2, histSize, ranges, true, false);
    normalize(baseHist, baseHist, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(halfDownHist, halfDownHist, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(compare0Hist, compare0Hist, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(compare1Hist, compare1Hist, 0, 1, NORM_MINMAX, -1, Mat());
    for(int i = 0; i < 4; i++)
    {
        int compare_method = i;
        double base_base = compareHist(baseHist, baseHist, compare_method);
        double base_half = compareHist(baseHist, halfDownHist, compare_method);
        double base_compare0 = compareHist(baseHist, compare0Hist, compare_method);
        double base_compare1 = compareHist(baseHist, compare1Hist, compare_method);
        cout << i << "base-base: " << base_base << endl;
        cout << i << "base-half: " << base_half << endl;
        cout << i << "base-compare0: " << base_compare0 << endl;
        cout << i << "base-compare1: " << base_compare1 << endl;
    }
    waitKey(1000);
    destroyWindow("base");
    destroyWindow("compare0");
    destroyWindow("compare1");
}

void OpenCvClass::calcBackProjectImage()
{
    string path = "images/book_resource_opencv3_programming_enter/";
    string path_image = path + "chapter9_calcBackProject_hand.jpg";
    Mat srcImage = imread(path_image, 1);
    Mat hsvImage, hueImage;
    int bins = 30;
    cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
    cout << "type:" << hsvImage.type() << "depth:" << hsvImage.depth() << endl;
    cout << "CV_8U: " << CV_8U << endl;
    hueImage.create(hsvImage.size(), CV_8UC1);
    cout << "type:" << hueImage.type() << "depth:" << hueImage.depth() << endl;
    int ch[] = {0, 0};
    mixChannels(&hsvImage, 1, &hueImage, 1, ch, 1);
    MatND hist;
    int histSize = MAX(bins, 2);
    float hue_range[] = {0, 180};
    const float* ranges = {hue_range};
    calcHist(&hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
    MatND backproj;
    calcBackProject(&hueImage, 1, 0, hist, backproj, &ranges, 1, true);
    imshow("hueImage", hueImage);

    // show the histogram image
    int w = 400; int h = 400;
    int bin_w = cvRound((double)w / histSize);
    Mat histImg = Mat::zeros(h, w, CV_8UC3);
    for(int i = 0; i < bins; i++)
    {
        rectangle(histImg, Point(i*bin_w, h),
                  Point((i+1)*bin_w, h-cvRound(hist.at<float>(i)*h/255.0)),
                  Scalar(100, 123, 255), -1);
    }
    imshow("histogram", histImg);

    result = backproj;
}

void OpenCvClass::matchTemplateImage()
{
    string path = "images/book_resource_opencv3_programming_enter/";
    string path_image = path + "chapter9_matchTemplate_image.jpg";
    string path_templ = path + "chapter9_matchTemplate_templ.jpg";
    Mat image = imread(path_image);
    Mat templ = imread(path_templ);
    Mat resultImage;
    int resultImage_cols = image.cols - templ.cols + 1;
    int resultImage_rows = image.rows - templ.rows + 1;
    resultImage.create(resultImage_cols, resultImage_rows, CV_32FC1);
    int method = TM_SQDIFF;
    matchTemplate(image, templ, resultImage, method);
    Mat normalizeImage;
    normalize(resultImage, normalizeImage, 0, 1, NORM_MINMAX, -1, Mat());
    double minValue, maxValue;
    Point minLocation, maxLocation, matchLocation;
    minMaxLoc(normalizeImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());
    if(method == TM_SQDIFF || method == TM_SQDIFF_NORMED)
    {
        matchLocation = minLocation;
    }
    else
    {
        matchLocation = maxLocation;
    }
    rectangle(image, matchLocation, Point(matchLocation.x + templ.cols,
                                         matchLocation.y + templ.rows),
              Scalar(0, 0, 255), 2, 8, 0);
    rectangle(normalizeImage, matchLocation, Point(matchLocation.x + templ.cols,
                                         matchLocation.y + templ.rows),
              Scalar(0, 0, 255), 2, 8, 0);

    imshow("rsult", resultImage);
    imshow("nor", normalizeImage);
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


