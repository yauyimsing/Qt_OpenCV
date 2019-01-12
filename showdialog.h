#ifndef SHOWDIALOG_H
#define SHOWDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QColorDialog>
#include <QColor>
#include "colordetectcontroller.h"

namespace Ui {
class ShowDialog;
}

class ShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowDialog(QWidget *parent = 0);
    ~ShowDialog();
    void showEvent(QShowEvent *);

private slots:
    void on_pushButtonSelectColor_clicked();

    void on_pushButtonProcess_clicked();

private:
    Ui::ShowDialog *ui;
    QVBoxLayout* layout;
    QMenuBar* menuBar;
    QAction* actionNew;
    void initLayout();
    void displayMat(Mat& image);

};

#endif // SHOWDIALOG_H
