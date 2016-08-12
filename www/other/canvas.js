var canvas = document.getElementById('myCanvas');
var context = canvas.getContext('2d');

canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

function putPoint(evt){
      //var message = "Mouse position: " + evt.clientX + "," + evt.clientY;
      //alert(message);
      context.beginPath();
      context.arc(evt.offsetX,evt.offsetY,10,0,2*3.14);
      context.fill();
}

canvas.addEventListener('mousedown',putPoint);
