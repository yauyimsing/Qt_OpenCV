#include "eventlineedit.h"
#include <QKeyEvent>
#include <QDebug>

EventLineEdit::EventLineEdit(QWidget *parent)
    : QLineEdit(parent)
{

}

void EventLineEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "EventLineEdit key down event";
    QLineEdit::keyPressEvent(event);
    event->ignore();

}

bool EventLineEdit::event(QEvent *event)
{
    //qDebug() << "event";
    if(event->type() == QEvent::KeyPress)
        qDebug() << "event->type() == QEvent::KeyPress";
    return QLineEdit::event(event);
}
