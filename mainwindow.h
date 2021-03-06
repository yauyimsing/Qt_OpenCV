#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow* ui;
    void setToolBar();
    void addStatusBar();
    void setAction();
signals:

public slots:
private slots:
    void on_actionNew_N_triggered();
    void on_actionShow_triggered();
    void on_actionDialog_triggered();
    void on_actionViewForm_triggered();
    void getCommand(const QString &string);
    void on_actionTestForm_triggered();
    void on_actionSingleImageForm_triggered();
};

#endif // MAINWINDOW_H
