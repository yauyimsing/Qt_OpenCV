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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtForm
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QTextEdit *textEdit;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;

    void setupUi(QWidget *QtForm)
    {
        if (QtForm->objectName().isEmpty())
            QtForm->setObjectName(QStringLiteral("QtForm"));
        QtForm->resize(747, 499);
        widget = new QWidget(QtForm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 22, 721, 461));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(500, 0));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(11111, 16777215));

        horizontalLayout->addWidget(label_2);

        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMaximumSize(QSize(11111, 50));

        horizontalLayout->addWidget(textEdit);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 6);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 8);
        verticalLayout->setStretch(1, 1);

        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(QtForm);

        QMetaObject::connectSlotsByName(QtForm);
    } // setupUi

    void retranslateUi(QWidget *QtForm)
    {
        QtForm->setWindowTitle(QApplication::translate("QtForm", "Form", 0));
        label->setText(QApplication::translate("QtForm", "TextLabel", 0));
        label_2->setText(QApplication::translate("QtForm", "TextLabel", 0));
        pushButton->setText(QApplication::translate("QtForm", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("QtForm", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class QtForm: public Ui_QtForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTFORM_H
