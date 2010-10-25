import Qt 4.7

Rectangle {
    id: window

    width: 360; height: 640
    color: "darkgreen"

    // a button to exit the app.
    Button {x: 165; y:10; width: 150; height: 55}

    // here are the cards

    Row {
        spacing: 30
        anchors.centerIn: parent
        Cards {
            yAxis: 1
            angle: 180
            image: "images/nicubunu_White_deck_Black_Joker.svg"
        }

        Cards {
            angle: 540
            xAxis: 1
            image: "images/nicubunu_White_deck_Queen_of_hearts.svg"
        }
    }
}
