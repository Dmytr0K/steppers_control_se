#ifndef ENGINEWIDGET_H
#define ENGINEWIDGET_H

#include <QWidget>
#include <math.h>
#include "packet.h"
#include "dialfilter.h"


namespace Ui {
class EngineWidget;
}

class EngineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EngineWidget(int engine_num, QWidget *parent = nullptr);
    ~EngineWidget();

    void setMinSpeed(int value);
    void setMaxSpeed(int value);

private:
    int engineNumber;
    Ui::EngineWidget *ui;
    int minSpeed = 100;
    int maxSpeed = 2000;
    QString offStyle;
    QString onStyle;
    DialFilter *dialFilter;

signals:
    void readyToSendPacket(Packet &packet);
    void isMove(int num);
    void isStop(int num);
};

#endif // ENGINEWIDGET_H
