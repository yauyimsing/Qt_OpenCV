/********************************************************************************
** Form generated from reading UI file 'qtform.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTFORM_H
#define UI_QTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtForm
{
public:
    QLabel *label;

    void setupUi(QWidget *QtForm)
    {
        if (QtForm->objectName().isEmpty())
            QtForm->setObjectName(QStringLiteral("QtForm"));
        QtForm->resize(586, 416);
        label = new QLabel(QtForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 10, 521, 341));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(QtForm);

        QMetaObject::connectSlotsByName(QtForm);
    } // setupUi

    void retranslateUi(QWidget *QtForm)
    {
        QtForm->setWindowTitle(QApplication::translate("QtForm", "Form", 0));
        label->setText(QApplication::translate("QtForm", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class QtForm: public Ui_QtForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTFORM_H
