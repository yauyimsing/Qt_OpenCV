#include "qtform.h"
#include "ui_qtform.h"
#include <iostream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "opencvclass.h"
#include <opencv2/opencv.hpp>

using namespace std;

QtForm::QtForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtForm)
{
    ui->setupUi(this);
    //qtSetLayout();
    //【2】循环显示每一帧
    //this->show();
    //capture.release();
    OpenCvClass opencv;
    Mat img = opencv.LoadPicture();
    QImage image = toQimage(img, ui->label->size());
    img.release();
    ui->label->setPixmap(QPixmap::fromImage(image));
    //showCapture();
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

void QtForm::showCapture()
{
    VideoCapture capture(0);
    cout << "while..." << endl;
    int i = 0;
    while(true){
        Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
        capture>>frame;  //读取当前帧
        imshow("video",frame);  //显示当前帧
        QImage img = QImage((const unsigned char*)(frame.data),
                                frame.cols, frame.rows, QImage::Format_RGB888);
        //设定图像大小自适应label窗口的大小
        img = img.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(img));

        waitKey(30);  //延时30ms
        if(i++ > 100)
        {
            break;
        }
    }
    cout << "while end..." << endl;
}

QImage QtForm::toQimage(Mat image, QSize size)
{
    QImage img = QImage((const unsigned char*)(image.data),
                            image.cols, image.rows, QImage::Format_RGB888);
    img = img.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    return img;
}


