/********************************************************************************
** Form generated from reading UI file 'singleimageform.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEIMAGEFORM_H
#define UI_SINGLEIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleImageForm
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayoutImage_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox_1;
    QComboBox *comboBox_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SingleImageForm)
    {
        if (SingleImageForm->objectName().isEmpty())
            SingleImageForm->setObjectName(QStringLiteral("SingleImageForm"));
        SingleImageForm->resize(621, 300);
        gridLayout_2 = new QGridLayout(SingleImageForm);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        gridLayoutImage_2 = new QGridLayout();
        gridLayoutImage_2->setObjectName(QStringLiteral("gridLayoutImage_2"));

        horizontalLayout_3->addLayout(gridLayoutImage_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        comboBox_1 = new QComboBox(SingleImageForm);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));

        verticalLayout_2->addWidget(comboBox_1);

        comboBox_2 = new QComboBox(SingleImageForm);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        verticalLayout_2->addWidget(comboBox_2);

        lineEdit_2 = new QLineEdit(SingleImageForm);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        verticalLayout_2->addWidget(lineEdit_2);

        pushButton_2 = new QPushButton(SingleImageForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalLayout_2->setStretch(0, 1);

        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3->setStretch(0, 7);
        horizontalLayout_3->setStretch(1, 1);

        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        retranslateUi(SingleImageForm);

        QMetaObject::connectSlotsByName(SingleImageForm);
    } // setupUi

    void retranslateUi(QWidget *SingleImageForm)
    {
        SingleImageForm->setWindowTitle(QApplication::translate("SingleImageForm", "Form", 0));
        comboBox_1->clear();
        comboBox_1->insertItems(0, QStringList()
         << QApplication::translate("SingleImageForm", "image", 0)
         << QApplication::translate("SingleImageForm", "erode", 0)
         << QApplication::translate("SingleImageForm", "blur", 0)
         << QApplication::translate("SingleImageForm", "canny", 0)
         << QApplication::translate("SingleImageForm", "capture", 0)
         << QApplication::translate("SingleImageForm", "create alpha mat", 0)
         << QApplication::translate("SingleImageForm", "add logo", 0)
         << QApplication::translate("SingleImageForm", "color reduce", 0)
         << QApplication::translate("SingleImageForm", "split channels", 0)
        );
        pushButton_2->setText(QApplication::translate("SingleImageForm", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class SingleImageForm: public Ui_SingleImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEIMAGEFORM_H
