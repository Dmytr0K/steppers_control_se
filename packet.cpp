#include "packet.h"

int Packet::id = 0;


Packet::Packet(QObject *parent) : QObject(parent)
{
    packet_id = id++;
}

void Packet::setCommand(const char &value)
{
    command = value;
}

void Packet::setEngine_number(const char &value)
{
    engine_number = value;
}

void Packet::setEngine_speed(int value)
{
    engine_speed = value;
}

void Packet::setSwitch_number(const char &value)
{
    switch_number = value;
}

void Packet::setSwitch_power(const char &value)
{
    switch_power = value;
}

QByteArray Packet::getPacket()
{
    QByteArray beforeBS;
    beforeBS.append(intToBytes(packet_id));
    beforeBS.append(command);
    if (command == MOVE)
    {
        beforeBS.append(engine_number);
        beforeBS.append(intToBytes(engine_speed));
    }
    if (command == SWITCH)
    {
        beforeBS.append(switch_number);
        beforeBS.append(switch_power);
    }

    QByteArray afterBS;
    afterBS.append(static_cast<char>(FLAG));
    afterBS.append(byteStuffing(beforeBS));
    afterBS.append(static_cast<char>(FLAG));
    return afterBS;
}

QByteArray Packet::intToBytes(int value)
{
    QByteArray res;
    res.append(static_cast<char>(value & 0xFF));
    res.append(static_cast<char>((value >> 8) & 0xFF));
    res.append(static_cast<char>((value >> 16) & 0xFF));
    res.append(static_cast<char>((value >> 24) & 0xFF));

    return res;
}

QByteArray Packet::byteStuffing(QByteArray bytes)
{
    QByteArray res;
    for (auto i : bytes)
    {
        if (static_cast<unsigned char>(i) == FLAG || static_cast<unsigned char>(i) == ESC)
        {
            res.append(ESC);
        }
        res.append(i);
    }

    return res;
}
