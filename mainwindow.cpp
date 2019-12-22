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
    flexorParentWidget = new QWidget;
    flexorWidget = new Flexor(flexorParentWidget);

    enginesWidget->setLayout(enginesLayout);
    switchesWidget->setLayout(switchesLayoyt);

    ui->scrollArea_engines->setWidget(enginesWidget);
    ui->scrollArea_engines->setWidgetResizable(true);
    ui->scrollArea_switches->setWidget(switchesWidget);
    ui->scrollArea_switches->setWidgetResizable(true);
    ui->tabWidget->addTab(flexorParentWidget, "Bending machine");

    serial = new QSerialPort(this);
    disconnectStyle = "QPushButton:!pressed"
                      "{"
                      "background-color: rgb(255,164,166);"
                      "border-radius: 5px;"
                      "font: 12pt \"Arial\";"
                      "}"

                      "QPushButton:pressed"
                      "{"
                      "background-color: rgb(255,164,166);"
                      "border-radius: 5px;"
                      "font: 11pt \"Arial\";"
                      "}";
    connectStyle = "QPushButton:!pressed"
                   "{"
                   "background-color: rgb(85,255,127);"
                   "border-radius: 5px;"
                   "font: 12pt \"Arial\";"
                   "}"

                   "QPushButton:pressed"
                   "{"
                   "background-color: rgb(85,255,127);"
                   "border-radius: 5px;"
                   "font: 11pt \"Arial\";"
                   "}";

    for (int i = 0; i < QUANTITY_ENGINES / COLUMNS_ENGINES; i++)
    {
        for (int j = 0; j < COLUMNS_ENGINES; j++)
        {
            if (COLUMNS_ENGINES * i + j < QUANTITY_ENGINES)
            {
                engineWidgets.append(new EngineWidget(COLUMNS_ENGINES * i + j + 1));
                if ((i % 2 && j % 2) || (!(i % 2) && !(j % 2)))
                {
                    engineWidgets[COLUMNS_ENGINES * i + j]->setAutoFillBackground(true);
                    QPalette pal = engineWidgets[COLUMNS_ENGINES * i + j]->palette();
                    pal.setColor(engineWidgets[COLUMNS_ENGINES * i + j]->backgroundRole(), QColor(230,230,230));
                    engineWidgets[COLUMNS_ENGINES * i + j]->setPalette(pal);
                }
                enginesLayout->addWidget(engineWidgets[COLUMNS_ENGINES * i + j], i, j);
            }
            else break;
        }
    }

    for (int i = 0; i < QUANTITY_SWITCHES / COLUMNS_SWITCHES; i++)
    {
        for (int j = 0; j < COLUMNS_SWITCHES; j++)
        {
            if (COLUMNS_SWITCHES * i + j < QUANTITY_SWITCHES)
            {
                switchesWidgets.append(new Switch(COLUMNS_SWITCHES * i + j + 1));
                if ((i % 2 && j % 2) || (!(i % 2) && !(j % 2)))
                {
                    switchesWidgets[COLUMNS_SWITCHES * i + j]->setAutoFillBackground(true);
                    QPalette pal = switchesWidgets[COLUMNS_SWITCHES * i + j]->palette();
                    pal.setColor(switchesWidgets[COLUMNS_SWITCHES * i + j]->backgroundRole(), QColor(230,230,230));
                    switchesWidgets[COLUMNS_SWITCHES * i + j]->setPalette(pal);
                }
                switchesLayoyt->addWidget(switchesWidgets[COLUMNS_SWITCHES * i + j], i, j);
            }
            else break;
        }
    }

    connect(ui->button_update, &QPushButton::clicked, this, &MainWindow::slot_update_serial);
    connect(ui->button_connect, &QPushButton::clicked, this, &MainWindow::slot_connect_serial);
    connect(ui->buttonApply, &QPushButton::clicked, [this] () ->
            void {
                int minAll = ui->spinMinAll->value();
                int maxAll = ui->spinMaxAll->value();
                for (int i = 0; i < engineWidgets.length(); i++)
                {
                    engineWidgets[i]->setMinSpeed(minAll);
                    engineWidgets[i]->setMaxSpeed(maxAll);
                }
            });
    connect(flexorWidget, &Flexor::readyToSendPacket, this, &MainWindow::slot_send_packet);
    for (auto eng : engineWidgets)
    {
        connect(eng, &EngineWidget::readyToSendPacket, this, &MainWindow::slot_send_packet);
        connect(eng, &EngineWidget::isMove, [this] (int num) ->
                void {
            if (num >= 2 && num <= 4)
            {
                engineWidgets[num + 3]->setEnabled(false);
            }
            if (num >= 5 && num <= 7)
            {
                engineWidgets[num - 3]->setEnabled(false);
            }
        });
        connect(eng, &EngineWidget::isStop, [this] (int num) -> void {
            if (num >= 2 && num <= 4)
            {
                engineWidgets[num + 3]->setEnabled(true);
            }
            if (num >= 5 && num <= 7)
            {
                engineWidgets[num - 3]->setEnabled(true);
            }
        });
    }
    for (auto sw : switchesWidgets)
    {
        connect(sw, &Switch::readyToSendPacket, this, &MainWindow::slot_send_packet);
    }

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::slot_read_serial);
    connect(this, &MainWindow::new_packet, this, &MainWindow::slot_packet_handler);
    slot_update_serial();
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
    for (auto ser : avaliable_ports)
    {
        list_serial.append(ser.portName());
    }
    ui->combo_ports->addItems(list_serial);
}

void MainWindow::slot_connect_serial()
{
    if (!serial->isOpen())
    {
        serial->setPort(avaliable_ports[ui->combo_ports->currentIndex()]);
        serial->open(QSerialPort::ReadWrite);
        serial->setBaudRate(QSerialPort::Baud115200);
        serial->setDataBits(QSerialPort::Data8);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        if (serial->isOpen())
        {
            ui->button_connect->setText("Disconnect");
            ui->button_connect->setStyleSheet(disconnectStyle);
        }
    }
    else if (serial->isOpen())
    {
        serial->close();
        if (!serial->isOpen())
        {
            ui->button_connect->setText("Connect");
            ui->button_connect->setStyleSheet(connectStyle);
        }
    }
}

void MainWindow::slot_send_packet(Packet &packet)
{
    QByteArray bytes = packet.getPacket();
    serial->write(bytes);
    qDebug() << endl << bytes;
}

void MainWindow::slot_read_serial()
{
    static bool packet_reception = false;
    static bool is_last_esc = false;
    char temp_buffer;
    while (serial->bytesAvailable()) {
        serial->read(&temp_buffer, 1);
        if (!is_last_esc && static_cast<uint8_t>(temp_buffer) == FLAG) {
            if (!packet_reception) {
                packet_reception = true;
                recievedPacket.clear();
            } else {
                packet_reception = false;
                emit new_packet(recievedPacket);
            }
        } else {
            if (!is_last_esc && static_cast<uint8_t>(temp_buffer) == ESC) {
                is_last_esc = true;
            } else {
                recievedPacket.append(temp_buffer);
                if (is_last_esc) {
                    is_last_esc = false;
                }
            }
        }
    }
}

void MainWindow::slot_packet_handler(QByteArray packet)
{
    qDebug() << packet;
}
