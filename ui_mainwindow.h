/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_N;
    QAction *actionOpen_O;
    QAction *actionShow;
    QAction *actionDialog;
    QAction *actionViewForm;
    QAction *actionTestForm;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menuFile_F;
    QMenu *menuEdit_E;
    QMenu *menuStart_S;
    QMenu *menuForm;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 721);
        actionNew_N = new QAction(MainWindow);
        actionNew_N->setObjectName(QStringLiteral("actionNew_N"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture/images/png/face.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_N->setIcon(icon);
        actionOpen_O = new QAction(MainWindow);
        actionOpen_O->setObjectName(QStringLiteral("actionOpen_O"));
        actionShow = new QAction(MainWindow);
        actionShow->setObjectName(QStringLiteral("actionShow"));
        actionDialog = new QAction(MainWindow);
        actionDialog->setObjectName(QStringLiteral("actionDialog"));
        actionViewForm = new QAction(MainWindow);
        actionViewForm->setObjectName(QStringLiteral("actionViewForm"));
        actionTestForm = new QAction(MainWindow);
        actionTestForm->setObjectName(QStringLiteral("actionTestForm"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 29));
        menuFile_F = new QMenu(menubar);
        menuFile_F->setObjectName(QStringLiteral("menuFile_F"));
        menuEdit_E = new QMenu(menubar);
        menuEdit_E->setObjectName(QStringLiteral("menuEdit_E"));
        menuStart_S = new QMenu(menubar);
        menuStart_S->setObjectName(QStringLiteral("menuStart_S"));
        menuForm = new QMenu(menubar);
        menuForm->setObjectName(QStringLiteral("menuForm"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile_F->menuAction());
        menubar->addAction(menuEdit_E->menuAction());
        menubar->addAction(menuStart_S->menuAction());
        menubar->addAction(menuForm->menuAction());
        menuFile_F->addAction(actionNew_N);
        menuFile_F->addAction(actionOpen_O);
        menuStart_S->addAction(actionShow);
        menuStart_S->addAction(actionDialog);
        menuForm->addAction(actionViewForm);
        menuForm->addAction(actionTestForm);
        toolBar->addAction(actionOpen_O);
        toolBar->addAction(actionShow);
        toolBar->addAction(actionDialog);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew_N->setText(QApplication::translate("MainWindow", "New(&N)", 0));
#ifndef QT_NO_TOOLTIP
        actionNew_N->setToolTip(QApplication::translate("MainWindow", "New File", 0));
#endif // QT_NO_TOOLTIP
        actionOpen_O->setText(QApplication::translate("MainWindow", "Open(O)", 0));
        actionShow->setText(QApplication::translate("MainWindow", "Show", 0));
        actionDialog->setText(QApplication::translate("MainWindow", "Dialog", 0));
        actionViewForm->setText(QApplication::translate("MainWindow", "ViewForm", 0));
        actionTestForm->setText(QApplication::translate("MainWindow", "TestForm", 0));
        menuFile_F->setTitle(QApplication::translate("MainWindow", "File(&F)", 0));
        menuEdit_E->setTitle(QApplication::translate("MainWindow", "Edit(&E)", 0));
        menuStart_S->setTitle(QApplication::translate("MainWindow", "Option", 0));
        menuForm->setTitle(QApplication::translate("MainWindow", "Form", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
