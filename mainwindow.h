#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QList>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include "enginewidget.h"
#include "switch.h"

#define QUANTITY_ENGINES 8
#define COLUMNS_ENGINES 4
#define QUANTITY_SWITCHES 12
#define COLUMNS_SWITCHES 6

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget *enginesWidget;
    QWidget *switchesWidget;

    QGridLayout *enginesLayout;
    QGridLayout *switchesLayoyt;

    QVector<EngineWidget*>engineWidgets;
    QVector<Switch*>switchesWidgets;

    QList <QSerialPortInfo> avaliable_ports;
    QStringList list_serial;
    QSerialPort *serial;

private slots:
    void slot_update_serial ();
    void slot_connect_serial ();
    void slot_send_packet(Packet &packet);
    void slot_read_serial();
};
#endif // MAINWINDOW_H
