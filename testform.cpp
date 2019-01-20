#include "testform.h"
#include "ui_testform.h"
#include <QKeyEvent>
#include <QWheelEvent>

TestForm::TestForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    initilize();
}

TestForm::~TestForm()
{
    delete ui;
}

void TestForm::initilize()
{
    ui->textEdit->installEventFilter(this);
    ui->spinBox->installEventFilter(this);
}

bool TestForm::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->textEdit)
    {
        if(event->type() == QEvent::Wheel)
        {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
            if(wheelEvent->delta() > 0)
                ui->textEdit->zoomIn();
            else
                ui->textEdit->zoomOut();
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(watched == ui->spinBox)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Space)
            {
                ui->spinBox->setValue(0);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
        return QWidget::eventFilter(watched, event);
}
