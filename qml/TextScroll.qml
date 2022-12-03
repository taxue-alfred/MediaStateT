//代码来源：https://cloud.tencent.com/developer/article/1463467

import QtQuick

Item {
    id: root
    property string text: "text"
    property int fontPixelSize: 20
    property string color: "black"

    width: sourceText.width
    height: sourceText.height
    clip: true

    PathView {
        id: pathView
        visible: sourceText.width > root.width
        width: textLoader.width*2; height: textLoader.height
        model: 2
        delegate: textComponent

        path: Path {
            startX: 0; startY: pathView.height/2
            PathLine { x: pathView.width; y: pathView.height/2 }
        }

        NumberAnimation on x {
            id: animation
            loops: Animation.Infinite
            from: 0
            to: -textLoader.width
            duration: 5000
        }
    }

    Text {
        id: sourceText
        visible: width <= root.width
        text: root.text
        font.pixelSize: root.fontPixelSize
        color: root.color
    }

    Loader {
        id: textLoader
        visible: false
        sourceComponent: textComponent
    }

    Component {
        id: textComponent
        Text {
            text: root.text + "   "
            font.pixelSize: root.fontPixelSize
            color: root.color
        }
    }

    /* Shielding sliding events. */
    MouseArea { anchors.fill: parent }
}