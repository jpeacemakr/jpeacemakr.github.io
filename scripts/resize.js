//resizes the expanded image to fit the screen. used on page load and resize
function resizeExpandedImage() {
    if (((document.getElementById("expandedImg").naturalHeight*0.7) > document.getElementById("expandedImg").naturalWidth) || 
    (document.getElementById("expandedImg").naturalHeight == 0)) {
        console.log("it is vertical");
        console.log(document.getElementById("expandedImg").naturalHeight + " by " + document.getElementById("expandedImg").naturalWidth);
        document.getElementById("expandedImg").style.height = (Math.min (window.screen.availHeight, window.innerHeight) -120) + "px";
        document.getElementById("expandedImg").style.width = "";
    } else {
        console.log("it is horizontal");
        console.log(document.getElementById("expandedImg").naturalHeight + " by " + document.getElementById("expandedImg").naturalWidth);
        document.getElementById("expandedImg").style.width = "400px";
        document.getElementById("expandedImg").style.height = "";
    }
}
