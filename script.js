var i = 0;
var txt = 'p0mf';
var speed = 400;

window.onload = function typeWriter() {
  if (i < txt.length) {
    document.getElementById("demo").innerHTML += txt.charAt(i);
    i++;
    setTimeout(typeWriter, speed);
  }
}

let hasPlayed = false;
function handleFirstPlay(event) {
  if(hasPlayed === false) {
    hasPlayed = true;

    let vid = event.target;

    vid.onplay = null;

    // Start whatever you need to do after first playback has started
  }
}

function travel(){
    window.location.href = "main.html";
}

