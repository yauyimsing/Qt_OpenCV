#ifndef CMDACTION_H
#define CMDACTION_H
#include <QWidgetAction>

class QLineEdit;

class CmdAction : public QWidgetAction
{
    Q_OBJECT
public:
    explicit CmdAction(QObject* parent = 0);
protected:
    QWidget* createWidget(QWidget* parent);
signals:
    void getText(const QString& string);
private slots:
    void sendText();
private:
    QLineEdit* lineEdit;
};

#endif // CMDACTION_H
