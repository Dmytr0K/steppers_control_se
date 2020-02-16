#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QObject>

class PacketManager : public QObject
{
    Q_OBJECT
public:
    explicit PacketManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PACKETMANAGER_H
