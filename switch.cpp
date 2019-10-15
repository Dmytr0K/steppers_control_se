#include "switch.h"
#include "ui_switch.h"

Switch::Switch(int num, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Switch)
{
    ui->setupUi(this);

    ui->label_number->setNum(num);
    onStyle = ("QPushButton:!pressed"
                    "{"
                    "border-radius: 15px;"
                    "background-color: rgb(33, 255, 6);"
                    "border: 2px solid black;"
                    "}"
                    "QPushButton:pressed"
                    "{"
                    "border-radius: 15px;"
                    "background-color: rgb(33, 255, 6);"
                    "border: 2px solid gray;"
                    "}");

    offStyle = ("QPushButton:!pressed"
                     "{"
                     "border-radius: 15px;"
                     "background-color: rgb(252, 2, 128);"
                     "border: 2px solid black;"
                     "}"
                     "QPushButton:pressed"
                     "{"
                     "border-radius: 15px;"
                     "background-color: rgb(252, 2, 128);"
                     "border: 2px solid gray;"
                     "}");

    connect(ui->buttonChange, &QPushButton::clicked, [this]() -> void {
                if (activated) {
                    ui->buttonChange->setStyleSheet(offStyle);
                } else {
                    ui->buttonChange->setStyleSheet(onStyle);
                }
                activated = !activated;
            });
}

Switch::~Switch()
{
    delete ui;
}
