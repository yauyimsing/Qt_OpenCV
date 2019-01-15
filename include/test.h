#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
namespace Ui {
class Test;
}

class QDESIGNER_WIDGET_EXPORT Test : public QWidget
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = 0);
    ~Test();

private:
    Ui::Test *ui;
};

#endif // TEST_H
