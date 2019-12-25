import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: track
    property var samples : []

    color: "gray"

    Component.onCompleted: {

        // Test data, for now
        for (var i = 0; i < 441000; i++) {
            samples.push(Math.random() * 2 - 1)
        }

        var samplesPerPixel = samples.length / track.width

        var component = Qt.createComponent("TrackNote.qml")

        var maxHeight = track.height / 2

        for (var i = 0; i < track.width; i++) {

            var rectHeight = samples[i * samplesPerPixel] * maxHeight

            // Different positioning based on whether the sample has a positive or a negative value
            var y = rectHeight < 0 ? maxHeight : maxHeight - rectHeight
            rectHeight = Math.abs(rectHeight)

            component.createObject(track,
                            {"x": i,
                             "y": y,
                             "height": rectHeight,
                             "width": 1})
        }
    }
}