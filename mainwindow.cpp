#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QSpinBox>
#include <QLabel>
#include <QTextEdit>
#include <QMdiSubWindow>
#include "qtform.h"
#include "showdialog.h"
#include "viewform.h"
#include "cmdaction.h"
#include <QDebug>
#include "testform.h"
#include "singleimageform.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setToolBar();
    setAction();
    addStatusBar();
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


void MainWindow::addStatusBar()
{
    ui->statusbar->showMessage("welcome to use mainwindow", 2000);
    QLabel* permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permanent->setText("yauyimsing");
    ui->statusbar->addPermanentWidget(permanent);
}

void MainWindow::setAction()
{
    CmdAction *action = new CmdAction;
    QMenu *editMenu = ui->menubar->addMenu("Command");
    editMenu->addAction(action);
    connect(action, SIGNAL(getText(const QString&)), this, SLOT(getCommand(const QString&)));
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

void MainWindow::on_actionViewForm_triggered()
{
    ViewForm* viewForm = new ViewForm(this);
    viewForm->imageRead("D:\\picture\\en.jpg");
    int height = viewForm->height();
    int width = viewForm->width();
    QMdiSubWindow* child = ui->mdiArea->addSubWindow(viewForm);
    child->setWindowTitle("picture sub-window");
    child->resize(width + 100, height + 100);
    child->show();
}

void MainWindow::getCommand(const QString &string)
{
    char*  ch;
    QByteArray ba = string.toLatin1(); // must
    ch=ba.data();
    cout << ch << endl;
}

void MainWindow::on_actionTestForm_triggered()
{
    TestForm *form = new TestForm(this);
    QSize size = form->size();
    QMdiSubWindow* child = ui->mdiArea->addSubWindow(form);
    child->setWindowTitle("picture sub-window");

    child->resize(size.width() + 100, size.height() + 100);
    child->show();
}

void MainWindow::on_actionSingleImageForm_triggered()
{
    SingleImageForm *form = new SingleImageForm(this);
    QSize size = form->size();
    QMdiSubWindow* child = ui->mdiArea->addSubWindow(form);
    child->setWindowTitle("picture sub-window");

    child->resize(size.width() + 100, size.height() + 100);
    child->show();
}
