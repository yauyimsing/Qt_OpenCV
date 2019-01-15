#ifndef VIEWFORM_H
#define VIEWFORM_H

#include <QWidget>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QFont>
#include <QMouseEvent>
#include <QKeyEvent>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "imagelabel.h"
using namespace std;
using namespace cv;
namespace Ui {
class ViewForm;
}

class ViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit ViewForm(QWidget *parent = 0);
    ~ViewForm();

private:
    Mat image;
    Mat result;
    Mat imageROI;
    Ui::ViewForm *ui;
    ImageLabel* imageLabel;
    QPoint mouseDownPoint, mouseUpPoint, mouseMovePoint;
    void showEvent(QShowEvent * event);
    void initilize();
    void paintEvent(QPaintEvent *event);
public:
    void imageRead(string filename)
    {
        image = imread(filename, 0);
        int roiWidth, roiHeight;
        roiHeight = roiWidth = 100;
        imageROI = image(Rect(image.rows/2,
                              image.cols/2,
                              roiHeight,
                              roiWidth));
    }
};

#endif // VIEWFORM_H
