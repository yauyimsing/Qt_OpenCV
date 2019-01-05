/*
 * this program should be in the opencv 3.2.0 so that it can be run.
 * qiu - 20190105
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <librarystatic0.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    int a = 4;
    int b = 1;
    int c = 1;
    //Library0 lib;
    //c = lib.add(a, b);
    LibraryStatic0 lib0;
    c = lib0.StaticAdd(a,b);
    cout << "start..." << "c: " << c << endl;

    //cin >> c;
    //【1】从摄像头读入视频
        VideoCapture capture(0);
        //【2】循环显示每一帧
        for(int i = 0; i < 100; i++){
            Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
            capture>>frame;  //读取当前帧
            imshow("video",frame);  //显示当前帧
            waitKey(30);  //延时30ms

        }
        return 0;

/*
*/
    cout << "end..." << endl;
    return 0;
 }
