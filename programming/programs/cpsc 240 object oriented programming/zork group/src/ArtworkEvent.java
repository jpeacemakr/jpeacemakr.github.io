import java.io.File;
/**
  * The purpose of ArtworkEvent is to display ascii-style artwork from an exterior file
  * with a .art extension.
  * @author JD
  */

class ArtworkEvent extends Event {
	
	private String eventString;
	private File ascii;
	
	/**
	  * The contructor's purpose is to create a file object given the name in the eventString.
	  * @param eventString is a String containing "Artwork BLANK.art" where Artowrk is an
	  * identifier for EventFactory, and BLANK.art is the filename for the artwork being displayed.
	  */
	ArtworkEvent(String eventString){
		super(eventString);
	}
	/**
	  * The execute method retrieves the artwork from the .art file and returns
	  * it as a String.
	  */
	String execute(){
		return null;
	}
}
