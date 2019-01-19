#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <opencv2/opencv.hpp>
using namespace cv;
namespace Ui {
class Form;
}
class TestForm : public QWidget
{
    Q_OBJECT
public:
    explicit TestForm(QWidget *parent = 0);
private:
    ~TestForm();
    Ui::Form *ui;
    void initilize();
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // TESTFORM_H
