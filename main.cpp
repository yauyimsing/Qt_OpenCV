/*
 * this program should be in the opencv 3.2.0 so that it can be run.
 * qiu - 20190105
 */
#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "qtform.h"
#include "mainwindow.h"
#include "test.h"
#include "imagelabel.h"
#include "colorhistogram.h"
#include "contentfinder.h"

using namespace std;
using namespace cv;
void initilize();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    initilize();

    MainWindow w;
    w.show();
    for(int i = 0; i < 10; ++i)
    {
        cout << i << endl;
    }




    return app.exec();
 }

void initilize()
{    int a = 4;
     int b = 1;
     int c = 121;

     cout << "start..." << "c: " << c << endl;
 /*
         VideoCapture capture(0);
         //【2】循环显示每一帧
         for(int i = 0; i < 100; i++){
             Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
             capture>>frame;  //读取当前帧
             imshow("video",frame);  //显示当前帧
             waitKey(30);  //延时30ms
         }
 */
}

