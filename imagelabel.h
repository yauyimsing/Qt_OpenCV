#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QObject>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = 0);
    ~ImageLabel();
    void imageRead(string filename);
    const Mat getImage();
    ImageLabel& operator<<(Mat& image);
    ImageLabel& operator<<(QString text);
    void showImage(Mat &image);
    void Delay_MSec(unsigned int msec);
private:
    Mat image;
    Mat result;
    Mat imageROI;
    QPoint mouseDownPoint, mouseUpPoint, mouseMovePoint;
    void showEvent(QShowEvent * event);
    void initilize();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void draw();
    void histogram();
    void displayMat(Mat &image);
    void getProbilityMat(const Mat &image, const Mat &imageROI,  Mat &result, int mode = 0);
    Mat getImageROI(Mat &image, QPoint start, QPoint end);
    int i;

};

#endif // IMAGELABEL_H
