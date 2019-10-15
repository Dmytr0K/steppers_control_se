#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enginesLayout = new QGridLayout();
    switchesLayoyt = new QGridLayout();

    enginesWidget = new QWidget;
    switchesWidget = new QWidget;

    enginesWidget->setLayout(enginesLayout);
    switchesWidget->setLayout(switchesLayoyt);

    ui->scrollArea_engines->setWidget(enginesWidget);
    ui->scrollArea_engines->setWidgetResizable(true);
    ui->scrollArea_switches->setWidget(switchesWidget);
    ui->scrollArea_switches->setWidgetResizable(true);

    for (int i = 0; i < QUANTITY_ENGINES / COLUMNS_ENGINES; i++) {
        for (int j = 0; j < COLUMNS_ENGINES; j++) {
            if (COLUMNS_ENGINES * i + j < QUANTITY_ENGINES) {
                engineWidgets.append(new EngineWidget(COLUMNS_ENGINES * i + j + 1));
                if ((i % 2 && j % 2) || (!(i % 2) && !(j % 2))) {
                    engineWidgets[COLUMNS_ENGINES * i + j]->setAutoFillBackground(true);
                    QPalette pal = engineWidgets[COLUMNS_ENGINES * i + j]->palette();
                    pal.setColor(engineWidgets[COLUMNS_ENGINES * i + j]->backgroundRole(), QColor(204,204,204));
                    engineWidgets[COLUMNS_ENGINES * i + j]->setPalette(pal);
                }
                enginesLayout->addWidget(engineWidgets[COLUMNS_ENGINES * i + j], i, j);
            }
            else break;
        }
    }

    for (int i = 0; i < QUANTITY_SWITCHES / COLUMNS_SWITCHES; i++) {
        for (int j = 0; j < COLUMNS_SWITCHES; j++) {
            if (COLUMNS_SWITCHES * i + j < QUANTITY_SWITCHES) {
                switchesWidgets.append(new Switch(COLUMNS_SWITCHES * i + j + 1));
                if ((i % 2 && j % 2) || (!(i % 2) && !(j % 2))) {
                    switchesWidgets[COLUMNS_SWITCHES * i + j]->setAutoFillBackground(true);
                    QPalette pal = switchesWidgets[COLUMNS_SWITCHES * i + j]->palette();
                    pal.setColor(switchesWidgets[COLUMNS_SWITCHES * i + j]->backgroundRole(), QColor(204,204,204));
                    switchesWidgets[COLUMNS_SWITCHES * i + j]->setPalette(pal);
                }
                switchesLayoyt->addWidget(switchesWidgets[COLUMNS_SWITCHES * i + j], i, j);
            }
            else break;
        }
    }

    connect(ui->button_update, &QPushButton::clicked, this, &MainWindow::slot_update_serial);
    connect(ui->button_connect, &QPushButton::clicked, this, &MainWindow::slot_connect_serial);
    connect(ui->buttonApply, &QPushButton::clicked, [this] () -> void {
                int minAll = ui->spinMinAll->value();
                int maxAll = ui->spinMaxAll->value();
                for (int i = 0; i < engineWidgets.length(); i++) {
                    engineWidgets[i]->setMinSpeed(minAll);
                    engineWidgets[i]->setMaxSpeed(maxAll);
                }
            });
    Packet packet;
    qDebug() << packet.getPacket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_update_serial()
{
    ui->combo_ports->clear();
    list_serial.clear();
    avaliable_ports = QSerialPortInfo::availablePorts();
    for (auto ser : avaliable_ports) {
        list_serial.append(ser.portName());
    }
    ui->combo_ports->addItems(list_serial);
}

void MainWindow::slot_connect_serial()
{
    serial->setPort(avaliable_ports[ui->combo_ports->currentIndex()]);
    serial->open(QSerialPort::ReadOnly);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
}

