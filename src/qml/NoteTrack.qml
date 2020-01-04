import QtQuick 2.12

import kompozitor 1.0

Rectangle {
    id: track
    property var notes : []

    color: "gray"

    Component.onCompleted: {

        var noteRange = 0
        var trackDuration = 0

        for (var i = 0; i < notes.length; i++) {
            var note = notes[i]

            if (note.pitch > noteRange) {
                noteRange = note.pitch
            }

            if (note.end > trackDuration) {
                trackDuration = note.end
            }
        }

        var pixelsPerSecond = track.width / trackDuration
        var noteHeight = track.height / noteRange

        var component = Qt.createComponent("TrackNote.qml")

        // Display all notes
        for (var i = 0; i < notes.length; i++) {
            var note = notes[i];
            var noteStartX = note.start * pixelsPerSecond
            var noteWidth = (note.end - note.start) * pixelsPerSecond
            var noteHeightOffset = (note.pitch - 1) * noteHeight
            component.createObject(track,
                {"x": noteStartX,
                 "y": noteHeightOffset,
                 "height": noteHeight,
                 "width": noteWidth})
        }
    }
}