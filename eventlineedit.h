#ifndef EVENTLINEEDIT_H
#define EVENTLINEEDIT_H
#include <QLineEdit>

class EventLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit EventLineEdit(QWidget *prarent = 0);
protected:
    void keyPressEvent(QKeyEvent* event);
    bool event(QEvent *event);
};

#endif // EVENTLINEEDIT_H
