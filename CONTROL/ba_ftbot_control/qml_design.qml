import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 400
    title: "Triangle Example"

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.fillStyle = "blue";

            // Define the points of the triangle
            var p1 = { x: canvas.width / 2, y: 10 };
            var p2 = { x: canvas.width - 10, y: canvas.height - 10 };
            var p3 = { x: 10, y: canvas.height - 10 };

            // Draw the triangle
            ctx.beginPath();
            ctx.moveTo(p1.x, p1.y);
            ctx.lineTo(p2.x, p2.y);
            ctx.lineTo(p3.x, p3.y);
            ctx.closePath();
            ctx.fill();
        }
    }
}
