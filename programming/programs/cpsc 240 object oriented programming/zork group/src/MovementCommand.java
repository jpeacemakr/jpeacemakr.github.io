/**
  * An object of MovementCommand represents an instance when the user enters an abbreviated
  * direction (n,s,e,w,u,d) into the command prompt. Its purpose is to change the current
  * player's current room.
  * @author JD
  */

class MovementCommand extends Command {

	private String dir; 
	
	/**
	  * The constructor takes a String. The String should only be either "n", "s", "e", "w",
	  * "u" or "d". The constructor saves this as the direction the user wants to leave.
	  */
	MovementCommand(String cmd){
		super(cmd);
		this.dir = cmd;
	}
	
	/**
	  * This method, using leaveBy()::Room, sets the current player's current room to a new room
	  * connected to the old room by an exit with a matching direction.
	  * @return if the room changes, the return is the new room's description. If it does not, then 
	  * the return is a statement saying that there is no valid exit in that direction.
	  */
	String execute(){ //yanked from old Command::execute()
		Room currentRoom = GameState.instance().getCurrentPlayer().getCurrentRoom();
		Room nextRoom = currentRoom.leaveBy(dir);
		if (nextRoom != null) {
			GameState.instance().getCurrentPlayer().setCurrentRoom(nextRoom);
			return "\n" + GameState.instance().nextPlayer() + GameState.instance().getCurrentPlayer().getCurrentRoom().describe(); 
		} else {
			return "\nSorry, you can't go " + dir + " from " + currentRoom.getTitle() + ".\n";
		}
	}
}
