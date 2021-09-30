#include "device.h"
#include <QString>
#include <QBluetoothAddress>

Device::Device(const QBluetoothDeviceInfo &d){
    device = d;
}

QString Device::getAddress() const{
#ifdef Q_OS_DARWIN
    return device.deviceUuid().toString();
#else
    return device.address().toString();
#endif
}

QString Device::getName() const{
    return device.name();
}

QBluetoothDeviceInfo Device::getDevice(){
    return device;
}

void Device::setDevice(const QBluetoothDeviceInfo &dev){
    device = QBluetoothDeviceInfo(dev);
}
