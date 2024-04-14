

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.5
import QtQuick.Controls 6.5
import BaFtbotDesign
import QtQuick.Layouts
import QtQuick.Shapes

Rectangle {
    id: rectangle
    width: 900
    height: 600
    color: "#1a1e25"

    Item {
        id: speed
        x: 391
        y: 111
        width: 118
        height: 135

        CustomLabel {
            id: speedNum
            y: 94
            width: 40
            height: 47
            color: "#6d6d6d"
            text: "m/s"
            wrapMode: Text.WordWrap
            anchors.horizontalCenterOffset: 0
            lineHeight: 0.8
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
            anchors.horizontalCenter: horizontalCenter
        }

        CustomLabel {
            id: speedLabel
            y: 0
            text: "-"
            anchors.horizontalCenter: horizontalCenter
            font.pixelSize: 82
            anchors.horizontalCenterOffset: 0
        }
    }

    Item {
        id: voltage
        x: 61
        y: 59
        width: 118
        height: 135

        CustomLabel {
            id: voltageNum
            y: 80
            width: 40
            height: 47
            color: "#6d6d6d"
            text: "V"
            wrapMode: Text.WordWrap
            anchors.horizontalCenterOffset: 39
            lineHeight: 0.8
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 15
            anchors.horizontalCenter: horizontalCenter
        }

        CustomLabel {
            id: voltageLabel
            y: 28
            text: "-.-"
            anchors.horizontalCenter: horizontalCenter
            font.pixelSize: 60
            anchors.horizontalCenterOffset: -18
        }
    }

    Image {
        x: 744
        y: 59
        width: 87
        height: 87
        anchors.horizontalCenter: arc.horizontalCenter
        source: "images/controller.png"
        anchors.horizontalCenterOffset: 337
    }

    Switch {
        id: switch1
        x: 750
        y: 158
        onCheckedChanged: (switchPosition = checked)
    }

    ArcItem {
        id: arc
        x: 270
        y: 411
        width: 360
        height: 360
        visible: trueaaaa
        rotation: 180
        fillColor: "#00ffffff"
        antialiasing: true
        begin: 98
        end: 262
        capStyle: 32
        strokeColor: "#6d6d6d"
        strokeWidth: 14
    }

    ArcRight {
        id: arcRight
        x: 295
        y: 393
        width: 315
        height: 350
        strokeWidth: 20
        antialiasing: true
    }

    ArcLeft {
        id: arcLeft
        x: 315
        y: 366
        width: 315
        height: 400
        strokeWidth: 20
        antialiasing: true
    }

    CustomLabel {
        id: leftLabel
        y: 514
        width: 53
        height: 70
        color: "#6d6d6d"
        text: "L"
        wrapMode: Text.WordWrap
        anchors.horizontalCenterOffset: -204
        lineHeight: 0.8
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 50
        anchors.horizontalCenter: horizontalCenter
    }

    CustomLabel {
        id: rightLabel
        y: 514
        width: 53
        height: 70
        color: "#6d6d6d"
        text: "R"
        wrapMode: Text.WordWrap
        anchors.horizontalCenterOffset: 205
        lineHeight: 0.8
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 50
        anchors.horizontalCenter: horizontalCenter
    }
}
