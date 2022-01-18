/**
 * The EventFactory class follows both the singleton and factory design patterns.
 * It instantiates all objects of type Event and Event's subclasses.
 * @author JD
 */

public class EventFactory {
	
	private static EventFactory theInstance;

	/**
	  * The purpose of the instance() method is to return an object of type EventFactory,
	  * so other methods can be called on it from a non-static context.
	  * @return the method instantiates a new object if one does not yet exist, otherwise, it returns
	  * the same object.
	  */
	public static synchronized EventFactory instance(){
		if(theInstance == null){
			theInstance = new EventFactory();
		}
		return theInstance;
	}

	private EventFactory(){

	}
	
	/**
	  * The purpose of the parse() method is to instantiate the appropriate subtype of Event.
	  * @param eventString is a String with the name of the event subtype (i.e. "Drop" or "Win") and
	  * other needed information, such as an item name or character name; with the two words separated
	  * by a space.
	  * @return the method returns an object of the appropriate subclass of Event.
	  */
	public Event parse(String eventString){
		if(eventString.startsWith("Drop")){
			return new DropEvent(eventString);
		} else if(eventString.startsWith("Die")){
			return new DieEvent(eventString);
		} else if(eventString.startsWith("Disappear")){
			return new DisappearEvent(eventString);
		} else if(eventString.startsWith("Score")){
			return new ScoreEvent(eventString);
		} else if(eventString.startsWith("Teleport")){
			return new TeleportEvent(eventString);
		} else if(eventString.startsWith("Transform")){
			return new TransformEvent(eventString);
		} else if(eventString.startsWith("Win")){
			return new WinEvent(eventString);
		} else if(eventString.startsWith("Wound")){
			return new WoundEvent(eventString);
		} else{
			return new DebugEvent(eventString);
		}
	}
}
