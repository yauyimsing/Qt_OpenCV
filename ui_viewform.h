/********************************************************************************
** Form generated from reading UI file 'viewform.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWFORM_H
#define UI_VIEWFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewForm
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayoutImage;

    void setupUi(QWidget *ViewForm)
    {
        if (ViewForm->objectName().isEmpty())
            ViewForm->setObjectName(QStringLiteral("ViewForm"));
        ViewForm->resize(606, 486);
        gridLayout_2 = new QGridLayout(ViewForm);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayoutImage = new QGridLayout();
        gridLayoutImage->setObjectName(QStringLiteral("gridLayoutImage"));

        gridLayout_2->addLayout(gridLayoutImage, 0, 0, 1, 1);


        retranslateUi(ViewForm);

        QMetaObject::connectSlotsByName(ViewForm);
    } // setupUi

    void retranslateUi(QWidget *ViewForm)
    {
        ViewForm->setWindowTitle(QApplication::translate("ViewForm", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ViewForm: public Ui_ViewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWFORM_H
