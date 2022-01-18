
/**
  * An object of LookCommand represents an instance when the user enters "look"
  * and its purpose is to return the current room's description.
  * @author JD
  */
class LookCommand extends Command {
	
	private String cmd;
	
	/**
	  * The constructor takes a String "look" where look solely serves as an identifier
	  * in CommandFactory and saves it similarly to superclass Command.
	  */
	LookCommand(String cmd){
		super(cmd);
		this.cmd = cmd;
	}
	
	/**
	  * The execute method recreates a player entering the room for the first time, that is,
	  * it temporarily resets the Room's beenHere boolean to false and describes the room.
	  * @return the current player's current room's full description.
	  */
	String execute(){
		Room currentRoom = GameState.instance().getCurrentPlayer().getCurrentRoom();
		currentRoom.resetBeenHere();
		return "\n" + currentRoom.describe();
	}

}
