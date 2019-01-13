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
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewForm
{
public:
    QGridLayout *gridLayout;
    QLabel *textLabelImage;

    void setupUi(QWidget *ViewForm)
    {
        if (ViewForm->objectName().isEmpty())
            ViewForm->setObjectName(QStringLiteral("ViewForm"));
        ViewForm->resize(606, 486);
        gridLayout = new QGridLayout(ViewForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textLabelImage = new QLabel(ViewForm);
        textLabelImage->setObjectName(QStringLiteral("textLabelImage"));
        textLabelImage->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(textLabelImage, 0, 0, 1, 1);


        retranslateUi(ViewForm);

        QMetaObject::connectSlotsByName(ViewForm);
    } // setupUi

    void retranslateUi(QWidget *ViewForm)
    {
        ViewForm->setWindowTitle(QApplication::translate("ViewForm", "Form", 0));
        textLabelImage->setText(QApplication::translate("ViewForm", "TextLabelImage", 0));
    } // retranslateUi

};

namespace Ui {
    class ViewForm: public Ui_ViewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWFORM_H
