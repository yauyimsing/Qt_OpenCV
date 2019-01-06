#ifndef QTFORM_H
#define QTFORM_H

#include <QWidget>
#include <opencv2/opencv.hpp>
using namespace cv;

namespace Ui {
class QtForm;
}
class QtForm : public QWidget
{
    Q_OBJECT

public:
    explicit QtForm(QWidget *parent = 0);
    ~QtForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QtForm *ui;

private:
    void qtSetLayout();
    void showCapture();
    QImage toQimage(Mat, QSize);
};

#endif // QTFORM_H
