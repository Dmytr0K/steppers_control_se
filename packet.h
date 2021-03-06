#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <QByteArray>

#define FLAG 0xDD
#define ESC 0x7D

enum {OFF, ON};
enum {MOVE = 0x09, RUN = 0x10, STOP = 0x11, SWITCH = 0x12};

class Packet : public QObject
{
    Q_OBJECT
public:
    explicit Packet(QObject *parent = nullptr);

    void setCommand(const char &value);

    void setEngine_number(const char &value);

    void setEngine_speed(int value);

    void setSwitch_number(const char &value);

    void setSwitch_power(const char &value);

    void setEngine_steps(int value);

    QByteArray getPacket ();



private:
    static int id;

    int packet_id;
    char command = 0;
    char engine_number = 0;
    int engine_speed = 0;
    int engine_steps = 0;
    char switch_number = 0;
    char switch_power = 0;

    QByteArray intToBytes (int value);
    QByteArray byteStuffing (QByteArray bytes);
};

#endif // PACKET_H
