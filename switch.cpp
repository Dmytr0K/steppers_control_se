#include "switch.h"
#include "ui_switch.h"

Switch::Switch(int num, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Switch)
{
    ui->setupUi(this);
    switchNumber = num - 1;
    ui->buttonChange->setText(QString::number(num));
    onStyle = ("QPushButton:!pressed"
                    "{"
                    "border-radius: 15px;"
                    "background-color: rgb(33, 255, 6);"
                    "border: 2px solid black;"
                    "color:black;"
                    "font-weight: 600;"
                    "font-size: 10pt;"
                    "}"
                    "QPushButton:pressed"
                    "{"
                    "border-radius: 15px;"
                    "background-color: rgb(33, 255, 6);"
                    "border: 2px solid gray;"
                    "color:black;"
                    "font-weight: 600;"
                    "font-size: 8pt;"
                    "}");

    offStyle = ("QPushButton:!pressed"
                     "{"
                     "border-radius: 15px;"
                     "background-color: rgb(252, 2, 128);"
                     "border: 2px solid black;"
                     "color:white;"
                     "font-weight: 600;"
                     "font-size: 10pt;"
                     "}"
                     "QPushButton:pressed"
                     "{"
                     "border-radius: 15px;"
                     "background-color: rgb(252, 2, 128);"
                     "border: 2px solid gray;"
                     "color:white;"
                     "font-weight: 600;"
                     "font-size: 8pt;"
                     "}");

    connect(ui->buttonChange, &QPushButton::clicked, [this]() -> void {
                Packet *packet = new Packet;
                packet->setCommand(SWITCH);
                packet->setSwitch_number(static_cast<char>(switchNumber));
                if (activated) {
                    //OFF
                    packet->setSwitch_power(OFF);
                    ui->buttonChange->setStyleSheet(offStyle);
                } else {
                    //ON
                    packet->setSwitch_power(ON);
                    ui->buttonChange->setStyleSheet(onStyle);
                }
                emit readyToSendPacket(*packet);
                activated = !activated;
            });
}

Switch::~Switch()
{
    delete ui;
}
