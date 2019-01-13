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
    QPoint mouseDownPoint, mouseUpPoint, mouseMovePoint;
    void showEvent(QShowEvent * event);
    void displayMat(Mat& image);
    void histogram();
    void initilize();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void draw();
public:
    void imageRead(string filename);
};

#endif // VIEWFORM_H
