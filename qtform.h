#ifndef QTFORM_H
#define QTFORM_H

#include <QWidget>

namespace Ui {
class QtForm;
}

class QtForm : public QWidget
{
    Q_OBJECT

public:
    explicit QtForm(QWidget *parent = 0);
    ~QtForm();

private:
    Ui::QtForm *ui;
};

#endif // QTFORM_H
