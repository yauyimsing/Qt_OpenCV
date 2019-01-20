#ifndef SINGLEIMAGEFORM_H
#define SINGLEIMAGEFORM_H
#include <QWidget>
#include <opencv2/opencv.hpp>
#include "opencvclass.h"

using namespace cv;

namespace Ui{
class SingleImageForm;
}
class ImageLabel;

class SingleImageForm : public QWidget
{
    Q_OBJECT
public:
    explicit SingleImageForm(QWidget *parent = 0);
    ~SingleImageForm();
private slots:
    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_1_currentIndexChanged(const QString &arg1);

private:
    enum Mode{ImageMode = 0, FrameMode = 1};
    ImageLabel *imageLabel;
    OpenCvClass opencv;
    Ui::SingleImageForm *ui;
    void initilize();
    Mat image;
    Mat result;
    bool displayMode; // 0: image, 1: frame
};

#endif // SINGLEIMAGEFORM_H
