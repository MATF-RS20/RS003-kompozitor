import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3

import kompozitor 1.0

ApplicationWindow {

    visible: true
    width: 1000
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
            text: mainModel.isRecordingMicrophone ? "Voice record stop" : "Voice record start"
            onClicked: {
                if(mainModel.isRecordingMicrophone){
                   mainModel.stopRecordingMicrophone();
                   frame.focus = "false";
                   dialogMicrophone.visible = "true";
                }
                else {
                  mainModel.startRecordingMicrophone();
                  frame.focus = "true";
                }
            }
        }
        
        Button {
            text: mainModel.isRecordingKeyboard ? "Keyboard record stop" : "Keyboard record start"
            onClicked: {
                if(mainModel.isRecordingKeyboard){
                    mainModel.stopRecordingKeyboard();
                    frame.focus = "false";
                    dialogKeyboard.visible = "true";
                }
                else {
                   mainModel.startRecordingKeyboard();
                   frame.focus = "true";
                }
            }
        }
    }

    Dialog {
        id: dialogKeyboard
        title: "Saving..."
        Label {
            text: "Do you want to save this recording?"
        }
        visible: false
        x: (parent.width - width) / 2
        y: (parent.height - height) / 3
        standardButtons: Dialog.Yes | Dialog.No

        onAccepted: {
            console.log("Yes clicked")
            mainModel.saveKeyboardComposition();
        }
        onRejected: {
            console.log("No clicked")
        }
    }

    Dialog {
            id: dialogMicrophone
            title: "Saving..."
            Label {
                text: "Do you want to save this recording?"
            }
            visible: false
            x: (parent.width - width) / 2
            y: (parent.height - height) / 3
            standardButtons: Dialog.Yes | Dialog.No

            onAccepted: {
                console.log("Yes clicked")
                mainModel.saveMicrophoneComposition();
            }
            onRejected: {
                console.log("No clicked")
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
        x: 600
        y: 520
        width: 70
        focus: false
        onAccepted: mainModel.octaveChanged(octaveNumber.getText(0,1))
        onEditingFinished: {
            frame.focus = "true";
        }
    }

    Button {
        id: playMelody1
        x: 700
        y: 0
        text: "Melody1"
        onPressed: mainModel.playMelody(0)
    }
    Button {
        id: playMelody2
        x: 810
        y: 0
        text: "Melody2"
        onPressed: mainModel.playMelody(1)
    }


    ListView {
        id: trackListView
        anchors.top: trackListControls.bottom
        anchors.left: parent.left
        width: 550
        height: 350
        clip: true
        model: TrackListModel { tracks: mainModel.tracks }
        Layout.fillWidth: true
        Layout.fillHeight: true
        ScrollBar.vertical: ScrollBar {}

        delegate: Column {
            Text {
                text: "Track " + dataTrackNumber
            }

            Row {
                spacing: 10.0
                Button {
                    text: "Start recording \n(WIP)"
                }

                // Load Track or SampleTrack based on the data
                Loader {
                    Component.onCompleted: {
                        if (dataTrackType == 1) {
                            setSource("NoteTrack.qml",
                                {
                                    width: 400,
                                    height: 100,
                                    notes: dataNotes,
                                    color: "green"
                                })
                        } else {
                            setSource("SampleTrack.qml",
                                {
                                    width: 400,
                                    height: 100,
                                    samples: dataSamples,
                                })
                        }

                    }
                }
            }

        }

        spacing: 10.0

    }

    Frame {
        id: frame
        anchors.top: octaveImage.bottom
        anchors.topMargin: 5
        anchors.left: parent.center
        anchors.rightMargin: 100
        x: 180

        width: 389
        height: 110
        focus: true
        Keys.onPressed: {
            if (event.isAutoRepeat) {
                return;
            }

            event.accepted=true;

            switch (event.key) {
                case Qt.Key_A: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(261.63, 1);
                    }
                    button1.down = "true";
                    mainModel.playNote(261.63);
                    break;
                }
                case Qt.Key_W: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(277.18, 2);
                    }
                    button4.down = "true";
                    mainModel.playNote(277.18);
                    break;
                }
                case Qt.Key_S: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(293.66, 3);
                    }
                    button2.down = "true";
                    mainModel.playNote(293.66);
                    break;
                }
                case Qt.Key_E: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(311.13, 4);
                    }
                    button5.down = "true";
                    mainModel.playNote(311.13);
                    break;
                }
                case Qt.Key_D: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(329.63, 5);
                    }
                    button3.down = "true";
                    mainModel.playNote(329.63);
                    break;
                }
                case Qt.Key_F: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(349.23, 6);
                    }
                    button6.down = "true";
                    mainModel.playNote(349.23);
                    break;
                }
                case Qt.Key_T: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(369.99, 7);
                    }
                    button11.down = "true";
                    mainModel.playNote(369.99);
                    break;
                }
                case Qt.Key_G: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(392.00, 8);
                    }
                    button7.down = "true";
                    mainModel.playNote(392.00);
                    break;
                }
                case Qt.Key_Y:
                case Qt.Key_Z: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(415.30, 9);
                    }
                    button12.down = "true";
                    mainModel.playNote(415.30);
                    break;
                }
                case Qt.Key_H: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(440.00, 10);
                    }
                    button8.down = "true";
                    mainModel.playNote(440.00);
                    break;
                }
                case Qt.Key_U: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(466.16, 11);
                    }
                    button13.down = "true";
                    mainModel.playNote(466.16);
                    break;
                }
                case Qt.Key_J: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(493.88, 12);
                    }
                    button9.down = "true";
                    mainModel.playNote(493.88);
                    break;
                }
                case Qt.Key_K: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.addRecordNote(523.25, 13);
                    }
                    button10.down = "true";
                    mainModel.playNote(523.25);
                    break;
                }
                default: event.accepted=false;
            }
        }
        Keys.onReleased: {
            if (event.isAutoRepeat) {
                return;
            }

            event.accepted=true;

            switch (event.key) {
                case Qt.Key_A: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(261.63, 1);
                    }
                    button1.down = !button1.down;
                    mainModel.stopNote(261.63);
                    break;
                }
                case Qt.Key_W: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(277.18, 2);
                    }
                    button4.down = !button4.down;
                    mainModel.stopNote(277.18);
                    break;
                }
                case Qt.Key_S: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(293.66, 3);
                    }
                    button2.down = !button2.down;
                    mainModel.stopNote(293.66);
                    break;
                }
                case Qt.Key_E: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(311.13, 4);
                    }
                    button5.down = !button5.down;
                    mainModel.stopNote(311.13);
                    break;
                }
                case Qt.Key_D: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(329.63, 5);
                    }
                    button3.down = !button3.down;
                    mainModel.stopNote(329.63);
                    break;
                }
                case Qt.Key_F: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(349.23, 6);
                    }
                    button6.down = !button6.down;
                    mainModel.stopNote(349.23);
                    break;
                }
                case Qt.Key_T: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(369.99, 7);
                    }
                    button11.down = !button11.down;
                    mainModel.stopNote(369.99);
                    break;
                }
                case Qt.Key_G: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(392.00, 8);
                    }
                    button7.down = !button7.down;
                    mainModel.stopNote(392.00);
                    break;
                }
                case Qt.Key_Y:
                case Qt.Key_Z: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(415.30, 9);
                    }
                    button12.down = !button12.down;
                    mainModel.stopNote(415.30);
                    break;
                }
                case Qt.Key_H: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(440.00, 10);
                    }
                    button8.down = !button8.down;
                    mainModel.stopNote(440.00);
                    break;
                }
                case Qt.Key_U: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(466.16, 11);
                    }
                    button13.down = !button13.down;
                    mainModel.stopNote(466.16);
                    break;
                }
                case Qt.Key_J: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(493.88, 12);
                    }
                    button9.down = !button9.down;
                    mainModel.stopNote(493.88);
                    break;
                }
                case Qt.Key_K: {
                    if(mainModel.isRecordingKeyboard){
                        mainModel.removeRecordNote(523.25, 13);
                    }
                    button10.down = !button10.down;
                    mainModel.stopNote(523.25);
                    break;
                }
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
            onPressed: {
                button1.down = "true";
                mainModel.playNote(261.63)
            }
            onReleased: {
                button1.down = !button1.down;
                mainModel.stopNote(261.63)
            }
        }

        Button {
            id: button2
            x: 37
            y: -12
            width: 46
            height: 110
            text: "S"
            onPressed: {
                button2.down = "true";
                mainModel.playNote(293.66)
            }
            onReleased: {
                button2.down = !button2.down;
                mainModel.stopNote(293.66)
            }

        }

        Button {
            id: button3
            x: 86
            y: -12
            width: 46
            height: 110
            text: "D"
            onPressed: {
                button3.down = "true";
                mainModel.playNote(329.63)
            }
            onReleased: {
                button3.down = !button3.down;
                mainModel.stopNote(329.63)
            }
        }

        Button {
            id: button4
            x: 14
            y: -12
            width: 45
            height: 45
            text: "W"
            background: Rectangle {
                color: button4.down ? "#404040" : "#0d0d0d";
                radius: 4;
            }
            contentItem: Text {
                font: button4.font
                color: "white"
                text: button4.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            onPressed: {
                button4.down = "true";
                mainModel.playNote(277.18);
            }
            onReleased: {
                button4.down = !button4.down;
                mainModel.stopNote(277.18)
            }
        }

        Button {
            id: button5
            x: 63
            y: -12
            width: 45
            height: 45
            text: "E"
            background: Rectangle {
                color: button5.down ? "#404040" : "#0d0d0d";
                radius: 4;
            }
            contentItem: Text {
                color: "white"
                text: button5.text
                font: button5.font
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            onPressed: {
                button5.down = "true";
                mainModel.playNote(311.13)
            }
            onReleased: {
                button5.down = !button5.down;
                mainModel.stopNote(311.13)
            }
        }

        Button {
            id: button6
            x: 135
            y: -12
            width: 46
            height: 110
            text: "F"
            onPressed: {
                button6.down = "true";
                mainModel.playNote(349.23)
            }
            onReleased: {
                button6.down = !button6.down;
                mainModel.stopNote(349.23)
            }
        }

        Button {
            id: button7
            x: 184
            y: -12
            width: 46
            height: 110
            text: "G"
            onPressed: {
                button7.down = "true";
                mainModel.playNote(392.00)
            }
            onReleased: {
                button7.down = !button7.down;
                mainModel.stopNote(392.00)
            }
        }

        Button {
            id: button8
            x: 233
            y: -12
            width: 46
            height: 110
            text: "H"
            onPressed: {
                button8.down = "true";
                mainModel.playNote(440.00)
            }
            onReleased: {
                button8.down = !button8.down;
                mainModel.stopNote(440.00)
            }
        }

        Button {
            id: button9
            x: 282
            y: -12
            width: 46
            height: 110
            text: "J"
            onPressed: {
                button9.down = "true";
                mainModel.playNote(493.88)
            }
            onReleased: {
                button9.down = !button9.down;
                mainModel.stopNote(493.88)
            }
        }

        Button {
            id: button10
            x: 331
            y: -12
            width: 46
            height: 110
            text: "K"
            onPressed: {
                button10.down = "true";
                mainModel.playNote(523.25)
            }
            onReleased: {
                button10.down = !button10.down;
                mainModel.stopNote(523.25)
            }
        }

        Button {
            id: button11
            x: 161
            y: -12
            width: 45
            height: 45
            text: "T"
            background: Rectangle {
                color: button11.down ? "#404040" : "#0d0d0d";
                radius: 4;
            }
            contentItem: Text {
                color: "white"
                text: button11.text
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font: button11.font
                elide: Text.ElideRight
            }
            onPressed: {
                button11.down = "true";
                mainModel.playNote(369.99)
            }
            onReleased: {
                button11.down = !button11.down;
                mainModel.stopNote(369.99)
            }
        }

        Button {
            id: button12
            x: 210
            y: -12
            width: 45
            height: 45
            text: "Y"
            background: Rectangle {
                color: button12.down ? "#404040" : "#0d0d0d";
                radius: 4;
            }
            contentItem: Text {
                color: "white"
                text: button12.text
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font: button12.font
                elide: Text.ElideRight
            }
            onPressed: {
                button12.down = "true";
                mainModel.playNote(415.30)
            }
            onReleased: {
                button12.down = !button12.down;
                mainModel.stopNote(415.30)
            }
        }

        Button {
            id: button13
            x: 259
            y: -12
            width: 45
            height: 45
            text: "U"
            background: Rectangle {
                color: button13.down ? "#404040" : "#0d0d0d";
                radius: 4;
            }
            contentItem: Text {
                color: "white"
                text: button13.text
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font: button13.font
                elide: Text.ElideRight
            }
            onPressed: {
                button13.down = "true";
                mainModel.playNote(466.16)
            }
            onReleased: {
                button13.down = !button13.down;
                mainModel.stopNote(466.16)
            }
        }
    }
}