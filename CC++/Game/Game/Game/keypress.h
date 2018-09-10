#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <QObject>
#include <QKeyEvent>

class KeyPressReceiver : public QObject
{

    Q_OBJECT

public:
    KeyPressReceiver();
    ~KeyPressReceiver();

signals:
    void getKey(int key);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // KEYPRESS_H
