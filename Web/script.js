var canvas = document.getElementById("mainCanvas");
var ctx = canvas.getContext("2d");
var SIZE = canvas.width = canvas.height = 2000;

function clear() {
    ctx.fillStyle = "black";
    ctx.fillRect(0, 0, SIZE, SIZE);
    ctx.fillStyle = "white";
    ctx.beginPath();
    ctx.ellipse(SIZE/2, SIZE/2, SIZE/2, SIZE/2, 0, 0, 2 * Math.PI);
    ctx.fill();
}

function draw() {
    clear();
}

(function loop() {
    draw();
    requestAnimationFrame(loop);
})();