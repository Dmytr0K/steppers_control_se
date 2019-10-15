#ifndef SWITCH_H
#define SWITCH_H

#include <QWidget>
#include "packet.h"

namespace Ui {
class Switch;
}

class Switch : public QWidget
{
    Q_OBJECT

public:
    explicit Switch(int num, QWidget *parent = nullptr);
    ~Switch();

private:
    Ui::Switch *ui;
    int switchNumber;
    bool activated = false;
    QString onStyle;
    QString offStyle;

signals:
    void readyToSendPacket(Packet &packet);
};

#endif // SWITCH_H
