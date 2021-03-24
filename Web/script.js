var canvas = document.getElementById("mainCanvas");
var ctx = canvas.getContext("2d");
var SIZE = canvas.width = canvas.height = 2000;
var brushDown = false;
var brushColor = "blue";
var brushRadius = 10;
var BLANK_POS = [-1, -1];
var lastPos = BLANK_POS;
var mousePos = BLANK_POS;

var colorRect = [10, 10, 70, SIZE/5];
var rainbow = ctx.createLinearGradient(colorRect[0], colorRect[1], colorRect[0], colorRect[3]);
rainbow.addColorStop(0, "red");
rainbow.addColorStop(1/6, "orange");
rainbow.addColorStop(2/6, "yellow");
rainbow.addColorStop(3/6, "green");
rainbow.addColorStop(4/6, "blue");
rainbow.addColorStop(5/6, "indigo");
rainbow.addColorStop(1, "violet");

function reset() {
    brushDown = false;
    brushColor = "blue";
    brushRadius = 10;
    lastPos = [-1, -1];
    mousePos = [-1, -1];
    clear();
}

function storeMousePos(e) {
    var rect = canvas.getBoundingClientRect();
    var ox = (e.clientX - rect.left) / rect.width;
    var oy = (e.clientY - rect.top) / rect.height;
    var cx = ox * SIZE;
    var cy = oy * SIZE;
    if (brushDown && cx > colorRect[0] && cx < colorRect[2] && cy > colorRect[1] && cy < colorRect[3]) {
        new_color = ctx.getImageData(cx, cy, 1, 1).data;
        brushColor = `rgba(${new_color.join(",")})`;
    }
    mousePos = [ox, oy];
}
canvas.addEventListener("mousedown", (e) => {
    brushDown = true;
    storeMousePos(e);
});
canvas.addEventListener("mouseup", (e) => {
    brushDown = false;
    lastPos = BLANK_POS;
});
canvas.addEventListener("mousemove", (e) => {
    storeMousePos(e);
});

function clear() {
    ctx.fillStyle = "black";
    ctx.fillRect(0, 0, SIZE, SIZE);
    ctx.fillStyle = "white";
    ctx.beginPath();
    ctx.ellipse(SIZE/2, SIZE/2, SIZE/2, SIZE/2, 0, 0, 2 * Math.PI);
    ctx.fill();
}

function in_circle(x, y) {
    return Math.pow(x-0.5, 2) + Math.pow(y-0.5, 2) <= Math.pow(0.5, 2);
}

function draw() {
    if (brushDown) {
        ctx.strokeStyle = brushColor;
        ctx.lineWidth = brushRadius * 2;
        if (lastPos[0] != -1 && in_circle(...lastPos) && in_circle(...mousePos)) {
            ctx.beginPath();
            ctx.moveTo(lastPos[0] * SIZE, lastPos[1] * SIZE);
            ctx.lineTo(mousePos[0] * SIZE, mousePos[1] * SIZE, brushRadius, brushRadius, 0, 0, 2 * Math.PI);
            ctx.stroke();
        }
        lastPos = mousePos;
    }
    ctx.fillStyle = rainbow;
    ctx.fillRect(...colorRect);
}

reset();
(function loop() {
    draw();
    requestAnimationFrame(loop);
})();