document.addEventListener('DOMContentLoaded', onLoad);

var boxesNames = ["box1", "box2", "box3", "box4", "box5"];
var boxes = new Array(5);
var _animationLength = 1000; // in ms
var _len;

function onLoad() {
  _len = boxesNames.length;
  for(var i = 0; i < _len; i++) {
    boxes[i] = document.getElementById(boxesNames[i]);
  }
  setTimeout(function(){ goDown(0,true); }, 1000);
}

function goDown(i,isDown) {
  if(i == _len) {
    isDown = !isDown;
    i = 0;
  }
  animate(boxes[i],(_animationLength/_len),isDown);
  setTimeout(function(){ goDown(i+1,isDown); }, _animationLength/_len);
}

function animate(object,time,isDown) {
  let start = Date.now();
  let timer = setInterval(function() {
  let timePassed = Date.now() - start;
  
  if (timePassed >= time) {
    clearInterval(timer); 
    return;
  }
  draw(timePassed,object,time,isDown);
  }, time/20);
}

function draw(timePassed,object,time,isDown) {
  if(isDown) {
    object.style.margin = `${Math.trunc(timePassed/time*100)}px 10px`;
  }
  else {
    object.style.margin = `${100 - Math.trunc(timePassed/time*100)}px 10px`;
  }
}