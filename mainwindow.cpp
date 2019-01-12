#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QMdiSubWindow>
#include "qtform.h"
#include "showdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setToolBar();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setToolBar()
{
    QToolButton* toolBtn = new QToolButton(this);
    toolBtn->setText("Color");
    QMenu* colorMenu = new QMenu(this);
    colorMenu->addAction("Red");
    colorMenu->addAction("Green");
    toolBtn->setMenu(colorMenu);
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolBar->addWidget(toolBtn);
    QSpinBox* spinBox = new QSpinBox(this);
    ui->toolBar->addWidget(spinBox);
}

void MainWindow::on_actionNew_N_triggered()
{
    QTextEdit* edit = new QTextEdit(this);
    QMdiSubWindow* child = ui->mdiArea->addSubWindow(edit);
    child->setWindowTitle("multi-document sub-window");
    child->show();
}

void MainWindow::on_actionShow_triggered()
{
    QtForm* qtForm = new QtForm(this);
    int height = qtForm->height();
    int width = qtForm->width();
    QMdiSubWindow* child = ui->mdiArea->addSubWindow(qtForm);
    child->setWindowTitle("picture sub-window");
    child->resize(width + 100, height + 100);
    child->show();
}

void MainWindow::on_actionDialog_triggered()
{
    ShowDialog* dialog = new ShowDialog(this);
    dialog->show();
}
