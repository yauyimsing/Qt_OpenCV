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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QTextEdit *textEdit;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_right;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;

    void setupUi(QWidget *QtForm)
    {
        if (QtForm->objectName().isEmpty())
            QtForm->setObjectName(QStringLiteral("QtForm"));
        QtForm->resize(768, 540);
        gridLayout = new QGridLayout(QtForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(QtForm);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(500, 430));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(QtForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(11111, 16777215));

        horizontalLayout->addWidget(label_2);

        textEdit = new QTextEdit(QtForm);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMaximumSize(QSize(11111, 50));

        horizontalLayout->addWidget(textEdit);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 6);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 8);
        verticalLayout->setStretch(1, 1);

        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        verticalLayout_right = new QVBoxLayout();
        verticalLayout_right->setObjectName(QStringLiteral("verticalLayout_right"));
        comboBox = new QComboBox(QtForm);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout_right->addWidget(comboBox);

        pushButton = new QPushButton(QtForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_right->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_right->addItem(verticalSpacer);

        lineEdit = new QLineEdit(QtForm);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_right->addWidget(lineEdit);

        pushButton_2 = new QPushButton(QtForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_right->addWidget(pushButton_2);


        gridLayout_2->addLayout(verticalLayout_right, 0, 2, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(QtForm);

        QMetaObject::connectSlotsByName(QtForm);
    } // setupUi

    void retranslateUi(QWidget *QtForm)
    {
        QtForm->setWindowTitle(QApplication::translate("QtForm", "Form", 0));
        label->setText(QApplication::translate("QtForm", "TextLabel", 0));
        label_2->setText(QApplication::translate("QtForm", "Info(&I)", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("QtForm", "image", 0)
         << QApplication::translate("QtForm", "erade", 0)
        );
        pushButton->setText(QApplication::translate("QtForm", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("QtForm", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class QtForm: public Ui_QtForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTFORM_H
