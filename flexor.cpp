#include "flexor.h"
#include "ui_flexor.h"

flexor::flexor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::flexor)
{
    ui->setupUi(this);
}

flexor::~flexor()
{
    delete ui;
}
