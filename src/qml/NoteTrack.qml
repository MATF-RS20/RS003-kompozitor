import QtQuick 2.12

import kompozitor 1.0

Canvas {
    id: track
    property var notes : []

    antialiasing: false
    smooth: false
    renderStrategy: Canvas.Threaded

    onPaint: {
        var rangeMin = 1000
        var rangeMax = 0
        var trackDuration = 0

        for (var i = 0; i < notes.length; i++) {
            var note = notes[i]

            if (note.pitch < rangeMin) {
                rangeMin = note.pitch
            }

            if (note.pitch > rangeMax) {
                rangeMax = note.pitch
            }

            if (note.end > trackDuration) {
                trackDuration = note.end
            }
        }

        var pixelsPerSecond = track.width / trackDuration
        var noteHeight = track.height / (rangeMax - rangeMin + 1)

        var ctx = getContext("2d")

        // Color the background
        ctx.fillStyle = Qt.rgba(0, 1, 0, 0.5);
        ctx.fillRect(0, 0, width, height);

        // Display all notes
        ctx.fillStyle = "black"
        for (var i = 0; i < notes.length; i++) {
            var note = notes[i];
            var noteStartX = note.start * pixelsPerSecond
            var noteWidth = (note.end - note.start) * pixelsPerSecond
            var noteHeightOffset = (rangeMax - note.pitch) * noteHeight

            ctx.fillRect(noteStartX, noteHeightOffset, noteWidth, noteHeight);
        }
    }
}