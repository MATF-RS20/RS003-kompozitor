import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: "Kompozitor"

    Button {
        text: "Play"
        onClicked: mainModel.playSomething()
    }

    Button {
        x: 155
        y: 0
        text: "Record"
        onClicked: mainModel.recordSomething()
    }

    Frame {
        id: frame
        x: 136
        y: 182
        width: 362
        height: 110

        Button {
            id: button1
            x: -12
            y: -12
            width: 46
            height: 110
            text: qsTr("A")
            onClicked: mainModel.playNote(261.63)
        }

        Button {
            id: button2
            x: 40
            y: -12
            width: 46
            height: 110
            text: qsTr("S")
            onClicked: mainModel.playNote(293.66)
        }

        Button {
            id: button3
            x: 92
            y: -12
            width: 46
            height: 110
            text: qsTr("D")
            onClicked: mainModel.playNote(329.63)
        }

        Button {
            id: button4
            x: 26
            y: -12
            width: 45
            height: 45
            text: "W"
            background: Rectangle {
                color: "black"
            }
            contentItem: Text {
                font: button4.font
                color: button4.down ? "red" : "white"
                text: button4.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            onClicked: mainModel.playNote(277.18)
        }

        Button {
            id: button5
            x: 76
            y: -12
            width: 45
            height: 45
            text: "E"
            contentItem: Text {
                color: button5.down ? "red" : "white"
                text: button5.text
                font: button5.font
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: "#000000"
            }
            onClicked: mainModel.playNote(311.13)
        }
    }
}
