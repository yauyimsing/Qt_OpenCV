#include "qtform.h"
#include "ui_qtform.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace std;
using namespace cv;

QtForm::QtForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtForm)
{
    ui->setupUi(this);
    //qtSetLayout();
    VideoCapture capture(0);
    //【2】循环显示每一帧
    this->show();
    for(int i = 0; i < 100; i++){
        Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
        capture>>frame;  //读取当前帧
        imshow("video",frame);  //显示当前帧
        QImage img = QImage((const unsigned char*)(frame.data),
                                frame.cols, frame.rows, QImage::Format_RGB888);
        //设定图像大小自适应label窗口的大小
        img = img.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(img));

        waitKey(30);  //延时30ms
    }
    //capture.release();
}

QtForm::~QtForm()
{
    delete ui;
}

void QtForm::qtSetLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ui->label);
    layout->addWidget(ui->textEdit);
    layout->setSpacing(3);
    layout->setContentsMargins(5, 5, 5, 5);
    setLayout(layout);
}

void QtForm::on_pushButton_clicked()
{
    ui->textEdit->setVisible(!ui->textEdit->isVisible());
}
