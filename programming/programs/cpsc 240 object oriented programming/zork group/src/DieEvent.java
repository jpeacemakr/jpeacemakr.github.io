/**
  * DieEvent is triggered in ItemSpecificCommand and AttackCommand. It represents
  * the death of a Player.
  * @author JD
  */
class DieEvent extends Event {
	
	private String eventString;
	
	/**
	  * The constructer takes a String "Die currentPlayerName" where Die is an
	  * identifier for EventFactory and currentPlayerName is used to store the
	  * Player object that represents the Player whose turn it is.
	  */
	DieEvent(String eventString){
		super(eventString);
		this.eventString = eventString;
	}
	
	/**
	  * This method removes the current Player from GameState's turn order, and
	  * if the turn order is then empty, ends the game. If the turn order is not
	  * empty, the game continues for the player(s) remaining, and the newly dead
	  * player's inventory is added to the room.
	  * @return Leeroy Jenkins died. -OR- Leeroy Jenkins died. Game over!
	  */
	String execute(){
		GameState.instance().getCurrentPlayer().die();
		return "\n" +  GameState.instance().getCurrentPlayer().getName() + " died.";
	}

}
