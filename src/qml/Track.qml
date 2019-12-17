import QtQuick 2.12

import kompozitor 1.0

Rectangle {
    property var noteRange: 1
    property var notes : []

    color: "gray"

    Component.onCompleted: {
        // Debug output for now
        console.log("Range of notes is: " + noteRange)
        console.log("Width is: " + width)
        console.log("Height is: " + height)
        for (var i = 0; i < notes.length; i++) {
            var note = notes[i]
            console.log("[" + note.pitch + ", " + note.start + ", " + note.end + "]")
        }

    }
}