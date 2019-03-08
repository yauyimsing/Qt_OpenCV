#include "command.h"
#include "iostream"
#include <QApplication>
#include <QMouseEvent>
#include <QPoint>
#include <QtGlobal>
#include <QTime>
#include <QThread>

using namespace std;
Command::Command()
{

}

void Command::Task(QWidget* widget)
{
    int i = 0;
    while(true)
    {
        QWidget widget1;

        //cout << "hello kugou" << i << endl;
        i++;
        if(i>100)
        {
            break;
        }
        QThread::sleep(1);
    }
}

void Command::test0(QWidget *widget)
{
    QPoint pos;
    int x = qrand() % 800;
    int y = qrand() % 600;
    cout << "x:" << x << "  y:" << y << endl;
    pos.setX(x);
    pos.setY(y);
    QMouseEvent *mEvnPress;
    QMouseEvent *mEvnRelease;
    try
    {
        mEvnPress = new QMouseEvent(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(widget->focusWidget(),mEvnPress);
        mEvnRelease = new QMouseEvent(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(widget->focusWidget(),mEvnRelease);
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
}
