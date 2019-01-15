#include "cmdaction.h"
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>

CmdAction::CmdAction(QObject *parent)
    :QWidgetAction(parent)
{
    lineEdit = new QLineEdit;
    connect(lineEdit, &QLineEdit::returnPressed, this, &CmdAction::sendText);
}

QWidget *CmdAction::createWidget(QWidget *parent)
{
    if(parent->inherits("QMenu") || parent->inherits("QToolBar"))
    {
        QSplitter* splitter = new QSplitter(parent);
        QLabel *label = new QLabel;
        label->setText("Insert Text");
        splitter->addWidget(label);
        splitter->addWidget(lineEdit);
        return splitter;
    }
    return 0;
}

void CmdAction::sendText()
{
    emit getText(lineEdit->text());
    lineEdit->clear();
}
