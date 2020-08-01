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
    ui->setupUi(this);
    imageLabel = new ImageLabel(this);
    initilize();

}

ViewForm::~ViewForm()
{
    delete ui;
}

void ViewForm::showEvent(QShowEvent * event)
{
    return;
}


void ViewForm::initilize()
{
    mouseDownPoint = QPoint(0, 0);
    mouseMovePoint = QPoint(0, 0);
    mouseUpPoint = QPoint(0, 0);

    imageLabel->imageRead("ee.jpg");
    ui->gridLayoutImage->addWidget(imageLabel, 0, 0, 1, 1);
    imshow("origin", imageLabel->getImage());
}



void ViewForm::paintEvent(QPaintEvent *event)
{
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

bool ViewForm::eventFilter(QObject *watched, QEvent *event)
{
    return true;
}



