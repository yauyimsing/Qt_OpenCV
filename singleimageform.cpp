#include "singleimageform.h"
#include "ui_singleimageform.h"
#include <QDebug>
#include "imagelabel.h"

SingleImageForm::SingleImageForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::SingleImageForm)
{
    qDebug() << "singleimagform";

    ui->setupUi(this);
    initilize();
}

SingleImageForm::~SingleImageForm()
{
    delete ui;
}

void SingleImageForm::initilize()
{
    cout << "ini" << endl;
    imageLabel = new ImageLabel(this);
    imageLabel->imageRead("images/en.jpg");
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
        opencv.getImageInfo();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "morphology")
    {
        ui->comboBox_2->addItem("dilate");
        ui->comboBox_2->addItem("erode");
        ui->comboBox_2->addItem("open");
        ui->comboBox_2->addItem("close");
        ui->comboBox_2->addItem("top hat");
        ui->comboBox_2->addItem("black hat");
    }
    else if(arg1 == "blur")
    {
        opencv.blurImage();
        //return;
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "gray")
    {
        opencv.getGrayImage();
        //return;
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "edge detection")
    {
        ui->comboBox_2->addItem("canny");
        ui->comboBox_2->addItem("sobel");
        ui->comboBox_2->addItem("laplacian");
        ui->comboBox_2->addItem("scharr");
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
    else if(arg1 == "contrast and bright")
    {
        opencv.contrastAndBright(1.5, -30);
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "filter")
    {
        ui->comboBox_2->addItem("box filter");
        ui->comboBox_2->addItem("blur");
        ui->comboBox_2->addItem("gaussian blur");
        ui->comboBox_2->addItem("median blur");
        ui->comboBox_2->addItem("bilateral filter");
    }
    else if(arg1 == "flood fill")
    {
        opencv.floodFillImage();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "resize")
    {
        ui->comboBox_2->addItem("zoom in");
        ui->comboBox_2->addItem("zoom out");
        ui->comboBox_2->addItem("pyr up");
        ui->comboBox_2->addItem("pyr down");
    }
    else if(arg1 == "threshold")
    {
        opencv.thresholdImage();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "translation")
    {
        ui->comboBox_2->addItem("hough lines");
        ui->comboBox_2->addItem("hough circles");
        ui->comboBox_2->addItem("channel blue");
    }
    else if(arg1 == "remap")
    {
        opencv.remapImage();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "affine transform")
    {
        opencv.affineTransformImage();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "equalize histogram")
    {
        opencv.equalizeHistImage();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "contours")
    {
        opencv.contoursImage();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "convex")
    {
        ui->comboBox_2->addItem("convex hull");
        ui->comboBox_2->addItem("min area rect");
        ui->comboBox_2->addItem("min enclosing circle");
        ui->comboBox_2->addItem("moments");
    }
    else if(arg1 == "watershed")
    {
        opencv.watershedImage();
        *imageLabel << opencv.getResult();
    }
    else if(arg1 == "histogram")
    {
        ui->comboBox_2->addItem("H-S 2D histogram");
        ui->comboBox_2->addItem("1D-single channels histogram");
        ui->comboBox_2->addItem("1D-3 channels histogram");
        ui->comboBox_2->addItem("histogram compare");
    }
    else if(arg1 == "calcBackProject")
    {
        ui->comboBox_2->addItem("calcBackProject");
        ui->comboBox_2->addItem("1D-single channels histogram");
        ui->comboBox_2->addItem("1D-3 channels histogram");
        ui->comboBox_2->addItem("histogram compare");
    }
    else if(arg1 == "match template")
    {
        ui->comboBox_2->addItem("match template");
        ui->comboBox_2->addItem("1D-single channels histogram");
        ui->comboBox_2->addItem("1D-3 channels histogram");
        ui->comboBox_2->addItem("histogram compare");
    }
}

void SingleImageForm::on_comboBox_1_currentTextChanged(const QString &arg1)
{

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
    else if(ui->comboBox_1->currentText() == "filter")
    {
        if(arg1 == "box filter")
        {
            opencv.filter(BOX_FILTER);
        }
        else if(arg1 == "blur")
        {
            opencv.filter(BLUR);
        }
        else if(arg1 == "gaussian blur")
        {
            opencv.filter(GAUSSIAN_BLUR);
        }
        else if(arg1 == "median blur")
        {
            opencv.filter(MEDIAN_BLUR);
        }
        else if(arg1 == "bilateral filter")
        {
            opencv.filter(BILATERAL_FILTER);
        }
        *imageLabel << opencv.getResult();
    }
    else if(ui->comboBox_1->currentText() == "morphology")
    {
        if(arg1 == "dilate")
        {
            opencv.morphology(DILATE_OPERATION);
        }
        else if(arg1 == "erode")
        {
            opencv.morphology(ERODE_OPERATION);
        }
        else if(arg1 == "open")
        {
            opencv.morphology(OPEN_OPERATION);
        }
        else if(arg1 == "close")
        {
            opencv.morphology(CLOSE_OPERATION);
        }
        else if(arg1 == "top hat")
        {
            opencv.morphology(TOP_HAT_OPERATION);
        }
        else if(arg1 == "black hat")
        {
            opencv.morphology(BLACK_HAT_OPERATION);
        }
        *imageLabel << opencv.getResult();
    }
    else if(ui->comboBox_1->currentText() == "resize")
    {
        if(arg1 == "zoom in")
        {
            opencv.resizeImage(ZOOM_IN);
        }
        else if(arg1 == "zoom out")
        {
            opencv.resizeImage(ZOOM_OUT);
        }
        else if(arg1 == "pyr up")
        {
            opencv.resizeImage(PYR_UP);
        }
        else if(arg1 == "pyr down")
        {
            opencv.resizeImage(PYR_DOWN);
        }
        *imageLabel << opencv.getResult();
    }
    else if(ui->comboBox_1->currentText() == "edge detection")
    {
        if(arg1 == "canny")
        {
            opencv.cannyImage();
        }
        else if(arg1 == "sobel")
        {
            opencv.sobelImage();
        }
        else if(arg1 == "laplacian")
        {
            opencv.laplacianImage();
        }
        else if(arg1 == "scharr")
        {
            opencv.scharr();
        }
        *imageLabel << opencv.getResult();
    }
    else if(ui->comboBox_1->currentText() == "translation")
    {
        if(arg1 == "hough lines")
        {
            opencv.houghLinesImage();
        }
        else if(arg1 == "hough circles")
        {
            opencv.HoughCirclesImage();
        }
        else if(arg1 == "laplacian")
        {
            opencv.laplacianImage();
        }
        else if(arg1 == "scharr")
        {
            opencv.scharr();
        }
        *imageLabel << opencv.getResult();
    }
    else if(ui->comboBox_1->currentText() == "convex")
    {
        if(arg1 == "convex hull")
        {
            opencv.convexHullImage();
            *imageLabel << opencv.getResult();
        }
        else if(arg1 == "min area rect")
        {
            opencv.minAreaRectImage();
        }
        else if(arg1 == "min enclosing circle")
        {
            opencv.minEnclosingCircleImage();
        }
        else if(arg1 == "moments")
        {
            opencv.momentImage();
        }
        *imageLabel << opencv.getResult();
    }
    else if(ui->comboBox_1->currentText() == "histogram")
    {
        if(arg1 == "H-S 2D histogram")
        {
            opencv.calcHS2DHistImage();
            *imageLabel << opencv.getResult();
        }
        else if(arg1 == "1D-single channels histogram")
        {
            opencv.calc1DHistImage();
        }
        else if(arg1 == "1D-3 channels histogram")
        {
            opencv.calc1D3CHistImage();
        }
        else if(arg1 == "histogram compare")
        {
            opencv.histogramCompare();
        }
        *imageLabel << opencv.getResult();
    }
    else if(ui->comboBox_1->currentText() == "calcBackProject")
    {
        if(arg1 == "calcBackProject")
        {
            opencv.calcBackProjectImage();
            *imageLabel << opencv.getResult();
        }
        else if(arg1 == "1D-single channels histogram")
        {
            opencv.calc1DHistImage();
        }
        *imageLabel << opencv.getResult();
    }
    else if(ui->comboBox_1->currentText() == "match template")
    {
        if(arg1 == "match template")
        {
            opencv.matchTemplateImage();
            *imageLabel << opencv.getResult();
        }
        *imageLabel << opencv.getResult();
    }
}
