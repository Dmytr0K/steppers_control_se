#include "enginewidget.h"
#include "ui_enginewidget.h"

EngineWidget::EngineWidget(int engine_num, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EngineWidget)
{
    ui->setupUi(this);
    ui->label_engine_number->setNum(engine_num);
    onStyle = "background-color: rgb(33, 255, 6);";
    offStyle = "background-color: rgb(252, 2, 128);";

    connect(ui->dial_speed, &QDial::valueChanged, [this](int value) -> void {
        ui->spinBox_speed->setValue(value);
        int offval = (abs(minSpeed) + abs(maxSpeed)) / OFFPER / 2;
        if (value > 0 - offval && value < 0 + offval) {
            //STOP
            ui->dial_speed->setStyleSheet(offStyle);
        } else {
            //RUN
            ui->dial_speed->setStyleSheet(onStyle);
        }
    });
    connect(ui->spinBox_speed, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) -> void {
        ui->dial_speed->setValue(value);
    });
    connect(ui->spinMin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) -> void {
        ui->dial_speed->setDisabled(true);
        ui->dial_speed->setMinimum(value);
        ui->spinBox_speed->setMinimum(value);
        ui->dial_speed->setValue(0);
        ui->dial_speed->setDisabled(false);
    });
    connect(ui->spinMax, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) -> void {
        ui->dial_speed->setDisabled(true);
        ui->dial_speed->setMaximum(value);
        ui->spinBox_speed->setMaximum(value);
        ui->dial_speed->setValue(0);
        ui->dial_speed->setDisabled(false);
    });


    setMinSpeed(minSpeed);
    setMaxSpeed(maxSpeed);
}

EngineWidget::~EngineWidget()
{
    delete ui;
}

void EngineWidget::setMinSpeed(int value)
{
    minSpeed = value;
    ui->spinMin->setValue(minSpeed);
}

void EngineWidget::setMaxSpeed(int value)
{
    maxSpeed = value;
    ui->spinMax->setValue(maxSpeed);
}
