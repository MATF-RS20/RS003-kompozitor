import QtQuick 2.12
import QtQuick.Controls 2.12

import kompozitor 1.0

Button {
    property var freq: 0.0

    width: 45
    height: 45

    background: Rectangle {
        color: down ? "#404040" : "#0d0d0d";
        radius: 3;
    }
    contentItem: Text {
        font: parent.font
        color: "white"
        text: parent.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    onPressed: {
        down = "true";
        mainModel.playNote(freq);
    }
    onReleased: {
        down = undefined;
        mainModel.stopNote(freq)
    }
}