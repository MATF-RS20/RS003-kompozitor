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
        width: 389
        height: 110
        focus: true
        Keys.onPressed: {
            if (event.key === Qt.Key_A  && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(261.63)
            }
            else if (event.key === Qt.Key_S && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(293.66)
            }
            else if (event.key === Qt.Key_D && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(329.63)
            }
            else if (event.key === Qt.Key_W && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(277.18)
            }
            else if (event.key === Qt.Key_E && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(311.13)
            }
            else if (event.key === Qt.Key_F && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(349.23)
             }
            else if (event.key === Qt.Key_T && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(369.99)
            }
            else if (event.key === Qt.Key_G && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(392.00)
            }
            else if (event.key === Qt.Key_Y && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(415.30)
            }
            else if (event.key === Qt.Key_H && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(440.00)
            }
            else if (event.key === Qt.Key_U && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(466.16)
            }
            else if (event.key === Qt.Key_J && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(493.88)
            }
            else if (event.key === Qt.Key_K && !event.isAutoRepeat){
                event.accepted=true;
                mainModel.playNote(523.25)
            }
        }
        Keys.onReleased: {
            if (event.key === Qt.Key_A) {
                console.log("Key A is Up!")
            }
        }
        Button {
            id: button1
            x: -12
            y: -12
            width: 46
            height: 110
            text: "A"
            onClicked: mainModel.playNote(261.63)
        }

        Button {
            id: button2
            x: 37
            y: -12
            width: 46
            height: 110
            text: "S"
            onClicked: mainModel.playNote(293.66)
        }

        Button {
            id: button3
            x: 86
            y: -12
            width: 46
            height: 110
            text: "D"
            onClicked: mainModel.playNote(329.63)
        }

        Button {
            id: button4
            x: 14
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
            x: 63
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

        Button {
            id: button6
            x: 135
            y: -12
            width: 46
            height: 110
            text: "F"
            onClicked: mainModel.playNote(349.23)
        }

        Button {
            id: button7
            x: 184
            y: -12
            width: 46
            height: 110
            text: "G"
            onClicked: mainModel.playNote(392.00)
        }

        Button {
            id: button8
            x: 233
            y: -12
            width: 46
            height: 110
            text: "H"
            onClicked: mainModel.playNote(440.00)
        }

        Button {
            id: button9
            x: 282
            y: -12
            width: 46
            height: 110
            text: "J"
            onClicked: mainModel.playNote(493.88)
        }

        Button {
            id: button10
            x: 331
            y: -12
            width: 46
            height: 110
            text: "K"
            onClicked: mainModel.playNote(523.25)
        }

        Button {
            id: button11
            x: 161
            y: -12
            width: 45
            height: 45
            text: "T"
            contentItem: Text {
                color: button11.down ? "red" : "white"
                text: button11.text
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font: button11.font
                elide: Text.ElideRight
            }
            background: Rectangle {
                color: "#000000"
            }
            onClicked: mainModel.playNote(369.99)
        }

        Button {
            id: button12
            x: 210
            y: -12
            width: 45
            height: 45
            text: "Y"
            contentItem: Text {
                color: button12.down ? "red" : "white"
                text: button12.text
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font: button12.font
                elide: Text.ElideRight
            }
            background: Rectangle {
                color: "#000000"
            }
            onClicked: mainModel.playNote(415.30)
        }

        Button {
            id: button13
            x: 259
            y: -12
            width: 45
            height: 45
            text: "U"
            contentItem: Text {
                color: button13.down ? "red" : "white"
                text: button13.text
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font: button13.font
                elide: Text.ElideRight
            }
            background: Rectangle {
                color: "#000000"
            }
            onClicked: mainModel.playNote(466.16)
        }
    }
}
