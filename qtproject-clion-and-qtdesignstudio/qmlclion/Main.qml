import QtQuick
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        id: rectangle
        x: 131
        y: 154
        width: 470
        height: 200
        color: "#ffffff"

        Button {
            id: button
            x: 96
            y: 59
            width: 136
            height: 51
            text: qsTr("Button")
        }
    }
}
