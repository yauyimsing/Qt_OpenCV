#include "qtform.h"
#include "ui_qtform.h"
#include <iostream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "opencvclass.h"
#include <opencv2/opencv.hpp>
#include "opencvfunction.h"

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
    showCapture();
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
    show();
    VideoCapture capture(0);
    cout << "while..." << endl;
    int i = 0;
    OpenCvClass opencv;
    while(true){
        opencv.tickStart();
        Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
        capture>>frame;  //读取当前帧
        imshow("video",frame);  //显示当前帧
        opencvfun::addLogo(frame, frame);
        QImage img = cvMat2QImage(frame);
        //设定图像大小自适应label窗口的大小
        img = img.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(img));

        opencv.tickEnd();
        cout << " time:" << opencv.getDuration() << "ms;"
             << endl;
        waitKey(30);  //延时30ms
        if(i++ > 100)
        {
            cv::imwrite("ee.jpg", frame);
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

QImage QtForm::cvMat2QImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
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
