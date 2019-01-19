#ifndef QTFORM_H
#define QTFORM_H

#include <QWidget>
#include <opencv2/opencv.hpp>
using namespace cv;

class EventLineEdit;
namespace Ui {
class QtForm;
}
class QtForm : public QWidget
{
    Q_OBJECT

public:
    explicit QtForm(QWidget *parent = 0);
    ~QtForm();
    static QImage cvMat2QImage(const cv::Mat &mat);

private slots:
    void on_pushButton_clicked();

private:
    Ui::QtForm *ui;
    EventLineEdit *eventLineEdit;
    int timerId;
    bool captureState;

protected:
    void timerEvent(QTimerEvent *event);

private:
    void qtSetLayout();
    void showCapture();    
    void initilize();
protected:
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // QTFORM_H
