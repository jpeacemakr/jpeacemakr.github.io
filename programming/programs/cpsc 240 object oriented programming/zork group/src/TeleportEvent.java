import java.util.Random;
import java.util.Hashtable;
import java.util.Iterator;
/**
  * TeleportEvent is triggered within ItemSpecificCommand, its purpose being
  * moving the current Player to a random Room in the dungeon.
  * @author JD
  */

class TeleportEvent extends Event {
	
	private String eventString;

	/**
	  * The constructor takes a String "Teleport currentPlayerName" where Teleport
	  * is an identifier in EventFactory, and currentPlayerName is used to save the
	  * Player object that needs to be teleported.
	  */
	TeleportEvent(String eventString){
		super(eventString);
		this.eventString = eventString;
	}
	
	/**
	  * This method randomly selects a Room within the current Dungeon's Hashtable
	  * of rooms and sets it as the current Player's current Room.
	  * @return a null String
	  */
	String execute(){
		Room destRoom = GameState.instance().getDungeon().getRandomRoom();
		GameState.instance().getCurrentPlayer().setCurrentRoom(destRoom);
		GameState.instance().getCurrentPlayer().setJustTeleported(true);
		return "\n\nTeleported!\n\n" + destRoom.describe();
	}

}
