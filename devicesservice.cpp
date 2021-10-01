#include "devicesservice.h"
#include <QMetaEnum>
#include <QDebug>

DevicesService::DevicesService(QObject *parent) : QObject(parent)
{
    qDebug()<<"DevicesService constructor start \n";
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &DevicesService::addDevice);
    connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &DevicesService::deviceScanError);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &DevicesService::deviceScanFinished);
    setUpdate("Search");
}

DevicesService::~DevicesService()
{
    qDebug()<<"DevicesService destructor start \n";
    delete discoveryAgent;
    discoveryAgent = nullptr;
}

void DevicesService::addDevice(const QBluetoothDeviceInfo& info)
{
    qDebug()<<"addDevice start \n";
    if (info.coreConfigurations()  & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
        setUpdate("Last device added: " + info.name());
}

void DevicesService::deviceScanFinished()
{
    qDebug()<<"deviceScanFinished start \n";
     const QList<QBluetoothDeviceInfo> foundDevices = discoveryAgent->discoveredDevices();
     for (const auto &nextDevice : foundDevices)
         if (nextDevice.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
             devices.append(new Device(nextDevice));

     emit devicesUpdated();
     m_deviceScanState = false;
     emit stateChanged();
     if (devices.isEmpty())
         setUpdate("No Low Energy devices found...");
     else
         setUpdate("Done! Scan Again!");
}

void DevicesService::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    qDebug()<<"deviceScanError start \n";
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        setUpdate("The Bluetooth adaptor is powered off, power it on before doing discovery.");
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        setUpdate("Writing or reading from the device resulted in an error.");
    else {
        static QMetaEnum qme = discoveryAgent->metaObject()->enumerator(
                    discoveryAgent->metaObject()->indexOfEnumerator("Error"));
        setUpdate("Error: " + QLatin1String(qme.valueToKey(error)));
    }

    m_deviceScanState = false;
    emit devicesUpdated();
    emit stateChanged();
}

void DevicesService::setUpdate(const QString &message)
{
    qDebug()<<"setUpdate start \n";
    //m_message = message;
    emit updateChanged(message + "\n");
}

void DevicesService::startDeviceDiscovery()
{
    qDebug()<<"startDeviceDiscovery start \n";
    qDeleteAll(devices);
    devices.clear();
    emit devicesUpdated();

    setUpdate("Scanning for devices ...");
    //! [les-devicediscovery-2]
    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    //! [les-devicediscovery-2]

    if (discoveryAgent->isActive()) {
        m_deviceScanState = true;
        emit stateChanged();
    }
}
