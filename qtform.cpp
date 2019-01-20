#include "qtform.h"
#include "ui_qtform.h"
#include <iostream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "opencvclass.h"
#include <opencv2/opencv.hpp>
#include "opencvfunction.h"
#include "colordetector.h"
#include "eventlineedit.h"
#include <QKeyEvent>
#include <QDebug>

using namespace std;

QtForm::QtForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtForm)
{
    ui->setupUi(this);
    initilize();
    //qtSetLayout();
    //【2】循环显示每一帧
    //this->show();
    //capture.release();
    OpenCvClass opencv;
    opencv.LoadPicture();
    Mat img = opencv.getImage();
    Mat result;
    ColorDetector detector;
    result = detector.process(img);
    QImage image = cvMat2QImage(result);
    image = image.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(image));
    showCapture();
}

QtForm::~QtForm()
{
    delete ui;
}

void QtForm::initilize()
{
    //qDebug() << "initilize";
    eventLineEdit = new EventLineEdit(this);
    ui->verticalLayout_right->addWidget(eventLineEdit);
    eventLineEdit->installEventFilter(this);

    timerId = startTimer(10000);
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

void QtForm::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerId)
    {
        captureState = false;
        qDebug() << "timer ends";
    }
}

void QtForm::showCapture()
{

    show();
    VideoCapture capture(0);
    captureState = true;
    cout << "while..." << endl;
    int i = 0;
    OpenCvClass opencv;
    Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
    Mat result;  //
    while(captureState){
        opencv.tickStart();
        capture>>frame;  //读取当前帧
        imshow("video",frame);  //显示当前帧
        opencvfun::ColorDetector(frame, result);
        //opencvfun::addLogo(result, result);
        QImage img = cvMat2QImage(result);
        //设定图像大小自适应label窗口的大小
        img = img.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(img));

        opencv.tickEnd();
        //cout << " time:" << opencv.getDuration() << "ms;" << endl;
        waitKey(5);  //延时30ms
        if(i++ > 100)
        {
            //cv::imwrite("ee.jpg", frame);
            //break;
        }
    }
    capture.release();
    cout << "while end..." << endl;
}

void QtForm::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "widget key down event";
}

bool QtForm::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->eventLineEdit)
    {
        if(event->type() == QEvent::KeyPress)
            qDebug() << "widget event filter";
    }
    return QWidget::eventFilter(watched, event);
}

QImage QtForm::cvMat2QImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        //cout << "cv_8uc1" << endl;
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        //qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        //qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

void QtForm::on_comboBox_currentIndexChanged(const QString &arg1)
{

}
