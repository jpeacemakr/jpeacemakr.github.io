// hide header when page is scrolled down
function hideHeader() {
    if ((window.innerWidth >= 768 && window.pageYOffset >= 400) ||(window.innerWidth < 768 && window.pageYOffset >= 100) ) {
      document.getElementById("header").style.top = "-600px";
    } else {
      document.getElementById("header").style.top = "0px";
    }
  }





  
// toggles the display of weatheralertsbody when used with onclick event
function toggleWeatherAlert() {
    let alertBody = document.getElementById("weatheralertbody");
    
    if (alertBody.style.display === "block") {
        alertBody.style.display = "none";
    } else {
        alertBody.style.display = "block";
    }
}





  