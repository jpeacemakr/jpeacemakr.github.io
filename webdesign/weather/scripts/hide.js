// hide header when page is scrolled down
function hideHeader() {
    

    if ((window.innerWidth >= 768 && window.pageYOffset >= 400) || ((window.innerWidth < 768 && window.pageYOffset >= 100) && (window.getComputedStyle(document.getElementById("weatheralertouter")).display === "none"))) {
      document.getElementById("hideheader").style.top = "-600px";
    } else {
      document.getElementById("hideheader").style.top = "0px";
    }
  }





  
// toggles the display of weatheralertsbody when used with onclick event
function toggleWeatherAlert() {
    let alertBody = document.getElementById("weatheralertbody");
    let alertHeader = document.getElementById("hideheader");

    
    if (alertBody.style.display === "block") {
        alertBody.style.display = "none";
        if (window.innerWidth >= 768) {
          alertHeader.style.position = "sticky";
        }
    } else {
        alertBody.style.display = "block";
        alertHeader.style.position = "static";
    }
}





  