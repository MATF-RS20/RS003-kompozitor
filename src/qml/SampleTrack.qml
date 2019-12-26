import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Canvas {
    id: track
    property var samples : []

    antialiasing: false
    smooth: false
    renderStrategy: Canvas.Threaded

    onPaint: {

        var ctx = getContext("2d")

        ctx.fillStyle = Qt.rgba(0.5, 0.5, 1, 1);
        ctx.fillRect(0, 0, width, height);

        ctx.lineWidth = 1
        ctx.strokeStyle = "black"
        ctx.beginPath()
            ctx.moveTo(0, track.height / 2)
            for(var i = 0; i < samples.length; i++) {
                ctx.lineTo(i * track.width / samples.length, (samples[i] + 1) / 2 * track.height)
            }
        ctx.stroke()
    }
}