import Qt 4.7

// This is a Qt Quick component. The name of the component is defined by the
// name of the file (ie Cards).

// Here we have taken some SVG file from Open Clipart(http://www.openclipart.org/people/nicubunu) to
// demonstrate how to use the QML Flipable element. Think of two images. One a playing card. The
// other is simply a pattern representing back of a playing card. When the user taps on the
// Flipable element, it rotates and displays the other side of the card.

// The key point here is the transition from one state to another. We have to faces to the
// card: front and back.

Flipable {
    id: container

    property alias image: frontImage.source
    property bool flipped: true
    property int xAxis: 0
    property int yAxis: 0
    property int angle: 0

    width: front.width; height: front.height

    // callee will define the front image
    front: Image { id: frontImage; smooth: true }
    back: Image { source: "images/nicubunu_Card_backs_suits_red.svg"; smooth: true }

    state: "back"

    MouseArea { anchors.fill: parent; onClicked: container.flipped = !container.flipped }

    transform: Rotation {
        id: rotation; origin.x: container.width / 2; origin.y: container.height / 2
        axis.x: container.xAxis; axis.y: container.yAxis; axis.z: 0
    }

    states: State {
        name: "back"; when: container.flipped
        PropertyChanges { target: rotation; angle: container.angle }
    }

    transitions: Transition {
        ParallelAnimation {
            NumberAnimation { target: rotation; properties: "angle"; duration: 600 }
            SequentialAnimation {
                NumberAnimation { target: container; property: "scale"; to: 0.75; duration: 300 }
                NumberAnimation { target: container; property: "scale"; to: 1.0; duration: 300 }
            }
        }
    }
}
