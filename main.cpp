/*
 * this program should be in the opencv 3.2.0 so that it can be run.
 * qiu - 20190105
 */
#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <librarystatic0.h>
#include "qtform.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int a = 4;
    int b = 1;
    int c = 11;
    LibraryStatic0 lib0;
    c = lib0.StaticAdd(a,b);
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
    cout << "QtForm start..." << endl;
    //return 0;
    QtForm form;
    cout << "QtForm end..." << endl;
    return app.exec();
 }

