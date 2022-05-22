// if screen is big enough, swap expanded image with new image, otherwise open in new window
function thumbnail(imgs) {
    var w = Math.min(window.screen.availWidth, window.innerWidth);
    
    // Get the expanded image
    var expandImg = document.getElementById("expandedImg");

    if (w > 600) {
        // Get the image text
        var imgText = document.getElementById("imgtext");
        // Use the same src in the expanded image as the image being clicked on from the grid
        expandImg.src = imgs.src.replace("_thumb", "");
        // Use the value of the alt attribute of the clickable image as text inside the expanded image
        imgText.innerHTML = imgs.alt;
        // Show the container element (hidden with CSS)
        expandImg.parentElement.parentElement.style.display = "block";
    } else {
        window.location.href = imgs.src; 
        expandImg.parentElement.parentElement.style.display = "none";
    }		
}