#include "dialfilter.h"

DialFilter::DialFilter(QObject *parent) : QObject(parent)
{

}

bool DialFilter::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            emit rightButtonClick();
            return  true;
        } else {
            return false;
        }
    }
    return  false;
}
