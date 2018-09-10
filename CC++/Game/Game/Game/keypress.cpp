#include "keypress.h"

KeyPressReceiver::KeyPressReceiver()
{

}

KeyPressReceiver::~KeyPressReceiver()
{

}

bool KeyPressReceiver::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if((key->key() == Qt::Key_Up) || (key->key() == Qt::Key_Left) || (key->key() == Qt::Key_Right) || (key->key() == Qt::Key_Down))
        {
            emit getKey(key->key());
        }
        else
        {
            return QObject::eventFilter(obj,event);
        }
        return true;
    }
    else
    {
        event->ignore();
        return QObject::eventFilter(obj,event);
    }
    event->ignore();
    return false;
}
