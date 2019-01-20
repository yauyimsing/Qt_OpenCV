#include "imagelabel.h"
#include <iostream>
#include "qtform.h"
#include "histogram1d.h"
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include "contentfinder.h"
#include "colorhistogram.h"
#include "QApplication"
#include <QTime>

using namespace std;

ImageLabel::ImageLabel(QWidget* parent)
    : QLabel(parent)
{
    cout << "ImageLabel ImageLabel()" << endl;
    initilize();
}

ImageLabel::~ImageLabel()
{
    cout << "ImageLabel ~ImageLabel()" << endl;
}

void ImageLabel::showEvent(QShowEvent * event)
{
    displayMat(image);
}

void ImageLabel::displayMat(Mat& image)
{
    if(image.empty())
    {
        return;
    }
    cout << "ImageLabel displayMat" << endl;
    QImage result = QtForm::cvMat2QImage(image);
    result = result.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(QPixmap::fromImage(result));
}

void ImageLabel::histogram()
{
    cout << "ImageLabel histogram" << endl;
    if(!image.empty())
    {
        Histogram1D h;
        result = h.getHistogramImage(imageROI);
    }
    else
    {
        cout << "ImageLabel image empty" << endl;
    }
}

void ImageLabel::getProbilityMat(const Mat &image, const Mat &imageROI, Mat &result, int mode)
{
    if(mode == 0) // gray image
    {
        Histogram1D h;
        h.hCalcBackProject(image, imageROI, result);
    }
    else if(mode == 1) // color image
    {
        ColorHistogram hc;
        Mat convert;
        convert = hc.colorReduce(image, 32);
        Mat imgROI = getImageROI(convert, mouseDownPoint, mouseUpPoint);
        MatND hist = hc.getHistogram(imgROI);
        ContentFinder f;
        f.setHistogram(hist);
        f.setThreshold(0.0f);
        result = f.find(convert);
    }
}

void ImageLabel::initilize()
{
    this->setAlignment(Qt::AlignCenter);
    mouseDownPoint = QPoint(0, 0);
    mouseMovePoint = QPoint(0, 0);
    mouseUpPoint = QPoint(0, 0);
}

void ImageLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::darkRed);
    painter.setPen(pen);
    painter.drawRect(QRect(mouseDownPoint, mouseMovePoint));
}

void ImageLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouseDownPoint = event->pos();
        mouseMovePoint = event->pos();
        mouseUpPoint = event->pos();
    }
    else if(event->button() == Qt::RightButton)
    {
        return;
    }
}

void ImageLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        return;
    }
    else
    {
        mouseMovePoint = event->pos();
        update();
    }
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouseUpPoint = event->pos();
        draw();
    }
    else if(event->button() == Qt::RightButton)
    {
        displayMat(image);
    }
}

void ImageLabel::draw()
{
    imageROI = getImageROI(image, mouseDownPoint, mouseUpPoint);
    displayMat(imageROI);

    getProbilityMat(image, imageROI, this->result, 1);
    //threshold(result, result, 120, 255, THRESH_BINARY);
    imshow("result", result);
    cv::waitKey(1000);
}

Mat ImageLabel::getImageROI(Mat &image, QPoint start, QPoint end)
{
    int x, y, width, height;
    float tmpx, tmpy, tmpwidth, tmpheight;
    tmpx = (float)start.x() / this->width() * image.cols;
    tmpy = (float)start.y() / this->height() * image.rows;
    tmpwidth = (float)(end.x() - start.x()) / this->width() * image.cols;
    tmpheight = (float)(end.y() - start.y()) / this->height() * image.rows;
    x = tmpx;
    y = tmpy;
    width = tmpwidth;
    height = tmpheight;
    Mat imageroi = image(Rect(x, y, width, height));
    return imageroi;
}

void ImageLabel::imageRead(string filename)
{
    image = imread(filename, 1);
    if(image.empty())
    {
        cout << "image empty" << endl;
        return;
    }
    int roiWidth, roiHeight;
    roiHeight = roiWidth = 100;
    imageROI = image(Rect(image.rows/3,
                          image.cols/3,
                          roiHeight,
                          roiWidth));
}

const Mat ImageLabel::getImage()
{
    return image;
}

ImageLabel& ImageLabel::operator<<(Mat &image)
{
    displayMat(image);
    //Delay_MSec(2000);
    return *this;
}

void ImageLabel::showImage(Mat &image)
{
    displayMat(image);
}
void ImageLabel::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
