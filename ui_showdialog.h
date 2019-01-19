/********************************************************************************
** Form generated from reading UI file 'showdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWDIALOG_H
#define UI_SHOWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLCDNumber *lcdNumber;
    QPushButton *pushButtonOpenImage;
    QPushButton *pushButtonSelectColor;
    QSlider *verticalSliderThreshold;
    QSpacerItem *verticalSpacer;
    QLabel *labelColor;
    QLabel *labelDistance;
    QLabel *labelThreshold;
    QPushButton *pushButtonProcess;
    QLabel *label;

    void setupUi(QDialog *ShowDialog)
    {
        if (ShowDialog->objectName().isEmpty())
            ShowDialog->setObjectName(QStringLiteral("ShowDialog"));
        ShowDialog->resize(678, 516);
        layoutWidget = new QWidget(ShowDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 50, 651, 451));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        lcdNumber = new QLCDNumber(layoutWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        QFont font;
        font.setFamily(QStringLiteral("SimSun"));
        font.setBold(true);
        font.setWeight(75);
        lcdNumber->setFont(font);
        lcdNumber->setDigitCount(8);

        verticalLayout->addWidget(lcdNumber);

        pushButtonOpenImage = new QPushButton(layoutWidget);
        pushButtonOpenImage->setObjectName(QStringLiteral("pushButtonOpenImage"));

        verticalLayout->addWidget(pushButtonOpenImage);

        pushButtonSelectColor = new QPushButton(layoutWidget);
        pushButtonSelectColor->setObjectName(QStringLiteral("pushButtonSelectColor"));

        verticalLayout->addWidget(pushButtonSelectColor);

        verticalSliderThreshold = new QSlider(layoutWidget);
        verticalSliderThreshold->setObjectName(QStringLiteral("verticalSliderThreshold"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(verticalSliderThreshold->sizePolicy().hasHeightForWidth());
        verticalSliderThreshold->setSizePolicy(sizePolicy);
        verticalSliderThreshold->setMaximumSize(QSize(155, 16777215));
        verticalSliderThreshold->setBaseSize(QSize(0, 0));
        verticalSliderThreshold->setLayoutDirection(Qt::LeftToRight);
        verticalSliderThreshold->setMaximum(255);
        verticalSliderThreshold->setValue(128);
        verticalSliderThreshold->setOrientation(Qt::Vertical);
        verticalSliderThreshold->setTickPosition(QSlider::TicksAbove);

        verticalLayout->addWidget(verticalSliderThreshold);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        labelColor = new QLabel(layoutWidget);
        labelColor->setObjectName(QStringLiteral("labelColor"));

        verticalLayout->addWidget(labelColor);

        labelDistance = new QLabel(layoutWidget);
        labelDistance->setObjectName(QStringLiteral("labelDistance"));

        verticalLayout->addWidget(labelDistance);

        labelThreshold = new QLabel(layoutWidget);
        labelThreshold->setObjectName(QStringLiteral("labelThreshold"));

        verticalLayout->addWidget(labelThreshold);

        pushButtonProcess = new QPushButton(layoutWidget);
        pushButtonProcess->setObjectName(QStringLiteral("pushButtonProcess"));

        verticalLayout->addWidget(pushButtonProcess);


        horizontalLayout->addLayout(verticalLayout);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 5);

        retranslateUi(ShowDialog);

        QMetaObject::connectSlotsByName(ShowDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowDialog)
    {
        ShowDialog->setWindowTitle(QApplication::translate("ShowDialog", "Dialog", 0));
        pushButtonOpenImage->setText(QApplication::translate("ShowDialog", "Open Image", 0));
        pushButtonSelectColor->setText(QApplication::translate("ShowDialog", "Select Color", 0));
        labelColor->setText(QApplication::translate("ShowDialog", "Color", 0));
        labelDistance->setText(QApplication::translate("ShowDialog", "Distance", 0));
        labelThreshold->setText(QApplication::translate("ShowDialog", "Threshold", 0));
        pushButtonProcess->setText(QApplication::translate("ShowDialog", "Process", 0));
        label->setText(QApplication::translate("ShowDialog", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class ShowDialog: public Ui_ShowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWDIALOG_H
