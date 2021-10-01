import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 440
    height: 680
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        anchors.fill: parent

        Text {
            id: text
            text: ""
            height: 200
            width: parent.width

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
        }

        Connections {
            target: deviceService
            function onUpdateChanged(value) {
                text.text += value;
            }
        }


        Button{
            id: button
            text: "click me"
            height: 50
            width: 100
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            onClicked: {
                deviceService.startDeviceDiscovery()
                if(deviceService.state){
                    text.text = "Searching...";
                }
            }
        }
    }


}
