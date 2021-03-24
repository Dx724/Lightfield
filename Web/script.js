var canvas = document.getElementById("mainCanvas");
var ctx = canvas.getContext("2d");
var SIZE = canvas.width = canvas.height = 2000;
var brushDown = false;
var brushColor = "blue";
var brushRadius = 10;
var BLANK_POS = [-1, -1];
var lastPos = BLANK_POS;
var mousePos = BLANK_POS;


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
}

reset();
(function loop() {
    draw();
    requestAnimationFrame(loop);
})();