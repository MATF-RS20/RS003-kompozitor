import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import kompozitor 1.0

ApplicationWindow {

    visible: true
    width: 900
    height: 600
    title: "Kompozitor"

    Row {
        id: trackListControls
        spacing: 10

        Button {
            text: "Add microphone track"
            onClicked: {
                mainModel.addMicrophoneTrack()
            }
        }

        Button {
            text: "Add keyboard track"
            onClicked: {
                mainModel.addKeyboardTrack()
            }
        }

        Button {
            text: "Record"
            onClicked: mainModel.recordSomething()
        }
        Button {
            text: mainModel.isRecording ? "Stop recording" : "Start recording"
            onClicked: mainModel.isRecording ? mainModel.stopRecording() : mainModel.startRecording()
        }
    }
    Image {
        source: "piano-keyboard.png"
        x: 0
        y: 400
        width: 700
        height: 120
    }

    Rectangle {
        id: octaveImage
        width: 108
        height: 50
        color: "#770000FF"
        border.color: "black"
        border.width: 1
        radius: 10
        x: 309
        y: 430
        MouseArea {
                anchors.fill: parent
                drag.target: parent;
                drag.axis: "XAxis"
                drag.minimumX: 5
                drag.maximumX: 589
                onReleased: mainModel.calculateOctave(octaveImage.x)
                //console.log(octaveImage.x)
            }
    }

    TextField {
        id: octaveNumber
        placeholderText: qsTr("Octave")
        x: 400
        y: 520
        width: 70
        focus: false
        onAccepted: mainModel.octaveChanged(octaveNumber.getText(0,1))
    }

    Button {
        id: playMelody1
        x: 600
        y: 0
        text: "Melody1"
        onPressed: mainModel.playMelody1()
    }


    ListView {
        id: trackListView
        anchors.top: trackListControls.bottom
        anchors.left: parent.left
        width: 300
        height: 400

        model: TrackListModel { tracks: mainModel.tracks }

        delegate: Column {
            Text {
                text: "Track " + dataTrackNumber
            }

            Row {
                spacing: 10.0
                Button {
                    text: "Start recording \n(WIP)"
                }

                Track {
                    width: 400
                    height: 100
                    notes: dataNotes
                    // temporary implementation of dataTrackType, for testing purposes
                    color: dataTrackType == 1 ? "green" : "blue"
                }
            }

        }

        spacing: 10.0

    }

    Frame {
        id: frame
        anchors.top: trackListView.bottom
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.rightMargin: 50

        width: 389
        height: 110
        focus: true
        Keys.onPressed: {
            if (event.isAutoRepeat) {
                return;
            }

            event.accepted=true;

            switch (event.key) {
                case Qt.Key_A: mainModel.playNote(261.63); break;
                case Qt.Key_W: mainModel.playNote(277.18); break;
                case Qt.Key_S: mainModel.playNote(293.66); break;
                case Qt.Key_E: mainModel.playNote(311.13); break;
                case Qt.Key_D: mainModel.playNote(329.63); break;
                case Qt.Key_F: mainModel.playNote(349.23); break;
                case Qt.Key_T: mainModel.playNote(369.99); break;
                case Qt.Key_G: mainModel.playNote(392.00); break;
                case Qt.Key_Y:
                case Qt.Key_Z: mainModel.playNote(415.30); break;
                case Qt.Key_H: mainModel.playNote(440.00); break;
                case Qt.Key_U: mainModel.playNote(466.16); break;
                case Qt.Key_J: mainModel.playNote(493.88); break;
                case Qt.Key_K: mainModel.playNote(523.25); break;
                default: event.accepted=false;
            }
        }
        Keys.onReleased: {
            if (event.isAutoRepeat) {
                return;
            }

            event.accepted=true;

            switch (event.key) {
                case Qt.Key_A: mainModel.stopNote(261.63); break;
                case Qt.Key_W: mainModel.stopNote(277.18); break;
                case Qt.Key_S: mainModel.stopNote(293.66); break;
                case Qt.Key_E: mainModel.stopNote(311.13); break;
                case Qt.Key_D: mainModel.stopNote(329.63); break;
                case Qt.Key_F: mainModel.stopNote(349.23); break;
                case Qt.Key_T: mainModel.stopNote(369.99); break;
                case Qt.Key_G: mainModel.stopNote(392.00); break;
                case Qt.Key_Y:
                case Qt.Key_Z: mainModel.stopNote(415.30); break;
                case Qt.Key_H: mainModel.stopNote(440.00); break;
                case Qt.Key_U: mainModel.stopNote(466.16); break;
                case Qt.Key_J: mainModel.stopNote(493.88); break;
                case Qt.Key_K: mainModel.stopNote(523.25); break;
                default: event.accepted=false;
            }
        }
        Button {
            id: button1
            x: -12
            y: -12
            width: 46
            height: 110
            text: "A"
            onPressed: mainModel.playNote(261.63)
            onReleased: mainModel.stopNote(261.63)
        }

        Button {
            id: button2
            x: 37
            y: -12
            width: 46
            height: 110
            text: "S"
            onPressed: mainModel.playNote(293.66)
            onReleased: mainModel.stopNote(293.66)

        }

        Button {
            id: button3
            x: 86
            y: -12
            width: 46
            height: 110
            text: "D"
            onPressed: mainModel.playNote(329.63)
            onReleased: mainModel.stopNote(329.63)
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
            onPressed: mainModel.playNote(277.18)
            onReleased: mainModel.stopNote(277.18)
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
            onPressed: mainModel.playNote(311.13)
            onReleased: mainModel.stopNote(311.13)
        }

        Button {
            id: button6
            x: 135
            y: -12
            width: 46
            height: 110
            text: "F"
            onPressed: mainModel.playNote(349.23)
            onReleased: mainModel.stopNote(349.23)
        }

        Button {
            id: button7
            x: 184
            y: -12
            width: 46
            height: 110
            text: "G"
            onPressed: mainModel.playNote(392.00)
            onReleased: mainModel.stopNote(392.00)
        }

        Button {
            id: button8
            x: 233
            y: -12
            width: 46
            height: 110
            text: "H"
            onPressed: mainModel.playNote(440.00)
            onReleased: mainModel.stopNote(440.00)
        }

        Button {
            id: button9
            x: 282
            y: -12
            width: 46
            height: 110
            text: "J"
            onPressed: mainModel.playNote(493.88)
            onReleased: mainModel.stopNote(493.88)
        }

        Button {
            id: button10
            x: 331
            y: -12
            width: 46
            height: 110
            text: "K"
            onPressed: mainModel.playNote(523.25)
            onReleased: mainModel.stopNote(523.25)
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
            onPressed: mainModel.playNote(369.99)
            onReleased: mainModel.stopNote(369.99)
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
            onPressed: mainModel.playNote(415.30)
            onReleased: mainModel.stopNote(415.30)
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
            onPressed: mainModel.playNote(466.16)
            onReleased: mainModel.stopNote(466.16)
        }
    }
}
