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

    imageLabel->imageRead("D:\\picture\\en.jpg");
    ui->gridLayoutImage->addWidget(imageLabel, 0, 0, 1, 1);
    imshow("origin", imageLabel->getImage());
}



void ViewForm::paintEvent(QPaintEvent *event)
{
}



