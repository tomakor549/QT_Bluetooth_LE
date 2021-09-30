#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QBluetoothDeviceInfo>

class Device
{
public:
    Device() = default;
    Device(const QBluetoothDeviceInfo &d);
    QString getAddress() const;
    QString getName() const;
    QBluetoothDeviceInfo getDevice();
    void setDevice(const QBluetoothDeviceInfo &dev);


private:
    QBluetoothDeviceInfo device;

};

#endif // DEVICE_H
