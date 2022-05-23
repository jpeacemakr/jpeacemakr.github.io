// if screen is big enough, swap expanded image (id expandedImg) with new image and use alt as caption (id imgtext), otherwise open in new window
function thumbnail(smallImage) {
    var w = Math.min(window.screen.availWidth, window.innerWidth);
    
    // Get the expanded image
    var expandImg = document.getElementById("expandedImg");

    if (w > 768) {
        // Get the image text
        var imgText = document.getElementById("imgtext");
        // Use the same src in the expanded image as the image being clicked on from the grid
        expandImg.src = smallImage.src.replace("_thumb", "");
        // Use the value of the alt attribute of the clickable image as text inside the expanded image
        imgText.innerHTML = smallImage.alt;
        // Show the container element (hidden with CSS)
        expandImg.parentElement.parentElement.style.display = "block";
    } else {
        window.location.href = smallImage.src; 
        expandImg.parentElement.parentElement.style.display = "none";
    }		
}