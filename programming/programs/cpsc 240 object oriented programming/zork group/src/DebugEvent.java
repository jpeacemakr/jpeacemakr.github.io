/**
  * DebugEvent is triggered in EventFactory if no other known Event is instantiated.
  * @author JD
  */
class DebugEvent extends Event {
	
	private String eventString;
	
	/**
	  * The constructer takes a String and saves whatever gibberish it may contain.
	  */
	DebugEvent(String eventString){
		super(eventString);
		this.eventString = eventString;
	}
	
	/**
	  * This method changes nothing, and returns the problematic eventString for
	  * debeugging on the .zork file.
	  */
	String execute(){
		return "\n\n\"" + eventString + "\" is not a valid event, you doof.";
	}

}
