#ifndef DEVICESSERVICE_H
#define DEVICESSERVICE_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QString>
#include "device.h"

class DevicesService : public QObject
{
    Q_OBJECT
public:
    explicit DevicesService(QObject *parent = nullptr);
    ~DevicesService();
    bool state(){return m_deviceScanState;}

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QString m_message;
    bool m_deviceScanState;
    QList<Device *> devices;

    void setUpdate(const QString &message);

public slots:
    void startDeviceDiscovery();

private slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void deviceScanFinished();
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error);

signals:
    void updateChanged(QString value);
    void devicesUpdated();
    void stateChanged();

};

#endif // DEVICESSERVICE_H
