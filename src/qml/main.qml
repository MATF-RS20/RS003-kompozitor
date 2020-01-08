import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3

import kompozitor 1.0

ApplicationWindow {

    Material.theme: Material.Dark
    Material.accent: Material.Orange

    visible: true
    width: 1200
    height: 600
    title: "Kompozitor"

    Row {
        id: trackListControls
        spacing: 10

        Button {
            icon.source: "microphone.svg"
            text: "Add microphone track"
            onClicked: {
                mainModel.addMicrophoneTrack()
                item.focus = "true";
            }
        }

        Button {
            icon.source: "piano.svg"
            text: "Add keyboard track"
            onClicked: {
                mainModel.addKeyboardTrack()
                item.focus = "true";
            }
        }

        Button {
            text: "Rewind"
        }

        Button {
            icon.source: "play.svg"
        }

        Button {
            icon.source: "pause.svg"
        }

        Button {
            icon.source: "stop.svg"
        }

        Button {
            icon.source: "piano.svg"
            text: "Keyboard record start"
            onClicked: {
                if(mainModel.isRecordingKeyboard){
                    text = "Keyboard record start";
                    mainModel.stopRecordingKeyboard(-1);
                    item.focus = "true";
                    dialogKeyboard.visible = "true";
                }
                else {
                    text = "Keyboard record stop";
                    mainModel.startRecordingKeyboard();
                    item.focus = "true";
                }
            }
        }

        Button {
            text: "Melody1"
            onPressed: mainModel.playMelody(0)
        }

        Button {
            text: "Melody2"
            onPressed: mainModel.playMelody(1)
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
        width: 700
        height: 50
        anchors.bottom: item.top
        anchors.topMargin: 10
        anchors.bottomMargin: 15
    }

    Rectangle {
        id: octaveImage
        width: 108
        height: 50
        color: "#770000FF"
        border.color: "black"
        border.width: 1
        radius: 10
        anchors.bottom: item.top
        anchors.bottomMargin: 15
        x: 308
        MouseArea {
                anchors.fill: parent
                drag.target: parent;
                drag.axis: "XAxis"
                drag.minimumX: 0
                drag.maximumX: 591
                onReleased: mainModel.calculateOctave(octaveImage.x)
            }
    }

    ListView {
        id: trackListView
        anchors {
            top: trackListControls.bottom
            left: parent.left
            bottom: octaveImage.top
            right: parent.right
            topMargin: 10
            bottomMargin: 10
            leftMargin: 5
            rightMargin: 5
        }
        clip: true
        model: TrackListModel { tracks: mainModel.tracks }
        Layout.fillWidth: true
        Layout.fillHeight: true
        ScrollBar.vertical: ScrollBar {}

        delegate: Item {

            // Resize to children
            width: childrenRect.width
            height: childrenRect.height

            anchors {
                left: parent.left
                right: parent.right
            }

            Text {
                id: trackIdText
                text: "Track " + dataTrackNumber
            }

            Button {
                anchors {
                    top: trackIdText.bottom
                }
                id: startRecordingButton
                text: dataTrackType == 1 ?
                    (dataTrackIsRecording ? "Keyboard stop" : "Keyboard start")
                    : (dataTrackIsRecording ? "Voice stop" : "Voice start")
                icon.source: dataTrackType == 1 ?
                "piano.svg" : "microphone.svg"
                onClicked: {
                    if (dataTrackType == 1){
                        if(dataTrackIsRecording){
                           item.focus = "true";
                           mainModel.stopRecordingKeyboard(index);
//                           dialogKeyboard.visible = "true";
                        }
                        else {
                          item.focus = "true";
                          mainModel.startRecordingKeyboard(index);
                        }
                    }
                    else if (dataTrackType == 0){
                        if(mainModel.isRecordingMicrophone){
                           item.focus = "false";
                           mainModel.stopRecordingMicrophone(index);
//                           dialogMicrophone.visible = "true";
                        }
                        else {
                          item.focus = !item.focus;
                          mainModel.startRecordingMicrophone(index);
                        }
                    }
                }
            }

            Button {
                id: playButton
                anchors {
                    top: startRecordingButton.bottom
                    left: parent.left
                }
                //text: (dataTrackIsPlaying ? "Stop" : "Start")
                icon.source: dataTrackIsPlaying ? "stop.svg" : "play.svg"
                onClicked: {
                 if(dataTrackIsPlaying){
                      item.focus = "true";
                      mainModel.stopTrack(index);
                   }
                   else {
                     item.focus = "true";
                     mainModel.playTrack(index);
                   }
                }
            }

            Button {
                id: deleteButton
                anchors {
                    top: playButton.bottom
                    left: parent.left
                }
                //text: "Delete"
                icon.source: "delete.svg"
            }



            // Load Track or SampleTrack based on the data
            Loader {

                anchors {
                    left: startRecordingButton.right
                    right: parent.right
                    top: trackIdText.top
                    bottom: deleteButton.bottom
                }

                Component.onCompleted: {
                    if (dataTrackType == 1) {
                        setSource("NoteTrack.qml",
                            {
                                notes: dataNotes,
                            })
                    } else {
                        setSource("SampleTrack.qml",
                            {
                                samples: dataSamples,
                            })
                    }

                }
            }
        }

        spacing: 10.0

    }

    Item {
        id: item
        anchors.left: parent.left
        anchors.leftMargin: 130
        anchors.rightMargin: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

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
        WhitePianoButton {
            id: button1
            x: -12
            y: -12
            freq: 261.63
            text: "A"
        }

        WhitePianoButton {
            id: button2
            x: 37
            y: -12
            freq: 293.66
            text: "S"
        }

        WhitePianoButton {
            id: button3
            x: 86
            y: -12
            freq: 329.63
            text: "D"
        }

        BlackPianoButton {
            id: button4
            x: 14
            y: -12
            freq: 277.18
            text: "W"
        }

        BlackPianoButton {
            id: button5
            x: 63
            y: -12
            freq: 311.13
            text: "E"
        }

        WhitePianoButton {
            id: button6
            x: 135
            y: -12
            freq: 349.23
            text: "F"
        }

        WhitePianoButton {
            id: button7
            x: 184
            y: -12
            freq: 392.00
            text: "G"
        }

        WhitePianoButton {
            id: button8
            x: 233
            y: -12
            freq: 440.00
            text: "H"
        }

        WhitePianoButton {
            id: button9
            x: 282
            y: -12
            freq: 493.88
            text: "J"
        }

        WhitePianoButton {
            id: button10
            x: 331
            y: -12
            freq: 523.25
            text: "K"
        }

        BlackPianoButton {
            id: button11
            x: 161
            y: -12
            freq: 369.99
            text: "T"
        }

        BlackPianoButton {
            id: button12
            x: 210
            y: -12
            freq: 415.30
            text: "Y"
        }

        BlackPianoButton {
            id: button13
            x: 259
            y: -12
            freq: 466.16
            text: "U"
        }
    }
}