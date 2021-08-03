#include <pgmspace.h>

/*
The tiny Javascript/canvas based color picker is based on the clever work of the folks
at Sparkbox. https://seesparkbox.com/foundry/how_i_built_a_canvas_color_picker
*/

char main_js[] PROGMEM = R"=====(

var activeButton = null;
var colorCanvas = null;

window.addEventListener('DOMContentLoaded', (event) => {
  // init the canvas color picker
  

  // get list of modes from ESP
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
   if (xhttp.readyState == 4 && xhttp.status == 200) {
     document.getElementById('modes').innerHTML = xhttp.responseText;
     modes = document.querySelectorAll('ul#modes li a');
     modes.forEach(initMode);
   }
  };
  xhttp.open('GET', 'modes', true);
  xhttp.send();
});

function initMode(mode, index) {
  mode.addEventListener('click', (event) => onMode(event, index));
}

function onColor(event, color) {
  event.preventDefault();
  var match = color.match(/rgb\(([0-9]*),([0-9]*),([0-9]*)\)/);
  if(match) {
    var colorValue = Number(match[1]) * 65536 + Number(match[2]) * 256 + Number(match[3]);
    //console.log('onColor:' + match[1] + "," + match[2] + "," + match[3] + "," + colorValue);
    submitVal('c', colorValue);
  }
}

function onMode(event, mode) {
  event.preventDefault();
  if(activeButton) activeButton.classList.remove('active')
  activeButton = event.target;
  activeButton.classList.add('active');
  submitVal('m', mode);
}

function onBrightness(event, dir) {
  event.preventDefault();
  submitVal('b', dir);
}

function onSpeed(event, dir) {
  event.preventDefault();
  submitVal('s', dir);
}

function onAuto(event, dir) {
  event.preventDefault();
  submitVal('a', dir);
}

function submitVal(name, val) {
  var xhttp = new XMLHttpRequest();
  xhttp.open('GET', 'set?' + name + '=' + val, true);
  xhttp.send();
}
)=====";
