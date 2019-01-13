#include "viewform.h"
#include "ui_viewform.h"
#include "histogram1d.h"
#include "qtform.h"
#include "histogram1d.h"
#include "colorhistogram.h"

ViewForm::ViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewForm)
{
    initilize();
    ui->setupUi(this);
}

ViewForm::~ViewForm()
{
    delete ui;
}

void ViewForm::showEvent(QShowEvent * event)
{
    histogram();
    if(!result.empty())
    {
        displayMat(result);
    }
}

void ViewForm::displayMat(Mat& image)
{
    QImage result = QtForm::cvMat2QImage(image);
    result = result.scaled(ui->textLabelImage->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->textLabelImage->setPixmap(QPixmap::fromImage(result));
}

void ViewForm::histogram()
{
    if(!image.empty())
    {
        Histogram1D h;
        result = h.getHistogramImage(imageROI);
        //ColorHistogram ch;
        //result = ch.getHistogramImage(image);
        imshow("Histogram", image);
    }
}

void ViewForm::initilize()
{
    mouseDownPoint = QPoint(0, 0);
    mouseMovePoint = QPoint(0, 0);
    mouseUpPoint = QPoint(0, 0);
}

void ViewForm::imageRead(string filename)
{
    image = imread(filename, 0);
    int roiWidth, roiHeight;
    roiHeight = roiWidth = 100;
    imageROI = image(Rect(image.rows/2,
                          image.cols/2,
                          roiHeight,
                          roiWidth));
}

void ViewForm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::darkRed);
    painter.setPen(pen);
    painter.drawRect(QRect(mouseDownPoint, mouseUpPoint));
}

void ViewForm::mousePressEvent(QMouseEvent *event)
{
    mouseDownPoint = event->pos();
    mouseUpPoint = event->pos();
}

void ViewForm::mouseMoveEvent(QMouseEvent *event)
{
    mouseUpPoint = event->pos();
    draw();
    update();
}

void ViewForm::mouseReleaseEvent(QMouseEvent *event)
{

}

void ViewForm::draw()
{
}

