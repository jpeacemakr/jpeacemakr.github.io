/**
  * An Event's purpose is to change the state of the game without receiving explicit
  * user input; one event object represents one change being made. All Events are
  * instantiated within EventFactory.
  * @author JD
  */
abstract class Event {
	
	private String eventString; //contains both Drop, Transform(squishedCan), etc, AND original Item's name separated by a space
	
	/**
	  * The constructor for a generic Event simply saves the String it is passed.
	  * @param eventString is a String with the name of the event subtype (i.e. "Drop" or "Win") and
	  * other needed information, such as an item name or character name; with the two words separated
	  * by a space.
	  */
	Event(String eventString){
		this.eventString = eventString;
	}
	
	/**
	  * There is no generic case for execution, so Event's execute method is abstract.
	  * In general, the method will change the state of the game in some way and return a String. For many
	  * Event types, this will be null.
	  */
	abstract String execute();
}
