
//update switch element
function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?switch=1", true); }
  else { xhr.open("GET", "/update?switch=0", true); }
  xhr.send();
}

//update slider element on html page
function updateSliderPWM(element) {
  var sliderValue = document.getElementById("pwmSlider").value;
   //sliderValue = map(sliverValue, 0, 1023, 0, 100)
  document.getElementById("textSliderValue").innerHTML = sliderValue;
  console.log(sliderValue);
  
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/update?slider="+sliderValue, true);
  xhr.send();
}

  //update sliderelement on html page
  function updateSliderPWM27(element) {
  var sliderValue = document.getElementById("pwmSlider27").value;
  document.getElementById("textSliderValue27").innerHTML = sliderValue;
  console.log(sliderValue);
  
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/update?slider27="+sliderValue, true);
  xhr.send();
}

  //update slider for GPIO 13 element on html page
  function updateSliderPWM13(element) {
  var sliderValue = document.getElementById("pwmSlider13").value;
  document.getElementById("textSliderValue13").innerHTML = sliderValue;
  console.log(sliderValue);
  
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/update?slider13="+sliderValue, true);
  xhr.send();
}