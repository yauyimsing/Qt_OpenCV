#include "singleimageform.h"
#include "ui_singleimageform.h"
#include <QDebug>
#include "imagelabel.h"

SingleImageForm::SingleImageForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::SingleImageForm)
{
    ui->setupUi(this);
    qDebug() << "singleimagform";
    initilize();
}

SingleImageForm::~SingleImageForm()
{
    delete ui;
}

void SingleImageForm::initilize()
{
    imageLabel = new ImageLabel(this);
    imageLabel->imageRead("D:\\picture\\en.jpg");
    //ui->formLayoutImage->addWidget(imageLabel);
    ui->gridLayoutImage_2->addWidget(imageLabel, 0, 0, 1, 1);
    opencv.LoadPicture();
    displayMode = ImageMode;
}

void SingleImageForm::on_comboBox_1_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    if(arg1 == "image")
    {
        displayMode = ImageMode;
        opencv.LoadPicture();
        *imageLabel << opencv.getImage();
    }
    else if(arg1 == "erode")
    {
        opencv.erodeImage();
        //return;
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "blur")
    {
        opencv.blurImage();
        //return;
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "canny")
    {
        opencv.cannyImage();
        //return;
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "capture")
    {
        displayMode = FrameMode;
        opencv.openCapture();
        for(int i = 0; i < 100; i++)
        {
            Mat image = opencv.getFrame();
            *imageLabel << image;
            waitKey(30);
        }
        opencv.closeCapture();
    }
    else if(arg1 == "create alpha mat")
    {
        opencv.createAlphaMat();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "add logo")
    {
        opencv.addLogo();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "color reduce")
    {
        opencv.colorReduce();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "split channels")
    {
        ui->comboBox_2->addItem("channel red");
        ui->comboBox_2->addItem("channel green");
        ui->comboBox_2->addItem("channel blue");
    }
    cout << "combo finish" << endl;
}


void SingleImageForm::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if(ui->comboBox_1->currentText() == "split channels")
    {
        if(arg1 == "channel red")
        {
            opencv.splitChannels(0);
        }
        else if(arg1 == "channel green")
        {
            opencv.splitChannels(1);
        }
        else if(arg1 == "channel blue")
        {
            opencv.splitChannels(2);
        }
        *imageLabel << opencv.getResult();
    }
}
