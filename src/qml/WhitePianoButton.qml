import QtQuick 2.12
import QtQuick.Controls 2.12

import kompozitor 1.0

Button {
    property double freq: 0.0

    width: 46
    height: 110

    background: Rectangle {
        color: down ? "#dddddd" : "#ffffff";
        radius: 3;
    }
    contentItem: Text {
        font: parent.font
        color: "black"
        text: parent.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    onPressed: {
        down = "true";
        mainModel.playNote(freq)
    }
    onReleased: {
        down = undefined;
        mainModel.stopNote(freq)
    }
}