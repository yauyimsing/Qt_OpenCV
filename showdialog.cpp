#include "showdialog.h"
#include "ui_showdialog.h"
#include "qtform.h"
#include <iostream>
#include "histogram1d.h"
#include <Qtime>

using namespace std;

ShowDialog::ShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowDialog)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &timerUpdate);
    timer->start(1000);
    initLayout();
}

ShowDialog::~ShowDialog()
{
    delete ui;
}

void ShowDialog::showEvent(QShowEvent *)
{
    ColorDetectController::getInstance()
            ->setInputImage("D:\\picture\\en.jpg", IMREAD_GRAYSCALE);
    Mat image = ColorDetectController::getInstance()
            ->getInputImage();
    if(!image.empty())
    {
        displayMat(image);
        Histogram1D h;
        MatND histo = h.getHistogram(image);
        for(int i = 0; i < 256; i++)
        {
            cout << "value" << i << "=" << histo.at<float>(i) << endl;
        }
    }
}

void ShowDialog::initLayout()
{
    layout = new QVBoxLayout(this);
    menuBar = new QMenuBar(this);
    menuBar->setGeometry(QRect(0, 0, 400, 24));
    QMenu* menu = menuBar->addMenu("File");
    actionNew = menu->addAction("New");
    actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));;
    layout->setMenuBar(menuBar);
    setLayout(layout);
}

void ShowDialog::displayMat(Mat& image)
{
    QImage result = QtForm::cvMat2QImage(image);
    result = result.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(result));
}

void ShowDialog::timerUpdate()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    if((time.second() % 2) == 0)
    {
        text[5] = ' ';
    }
    ui->lcdNumber->display(text);
}

void ShowDialog::on_pushButtonSelectColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::green, this);
    if(color.isValid())
    {
        ColorDetectController::getInstance()->setTargetColor(
                    color.red(), color.green(), color.blue());
    }
}

void ShowDialog::on_pushButtonProcess_clicked()
{
    ColorDetectController::getInstance()
            ->setColorDistanceThreshold(
                ui->verticalSliderThreshold->value());
    ColorDetectController::getInstance()
            ->process();
    Mat result = ColorDetectController::getInstance()
            ->getLastResult();
    if(!result.empty())
    {
        displayMat(result);
    }
}
