/**
  * WinEvent will be triggered when a player satisfies requirements to
  * complete the game.
  * @author JD
  */
class WinEvent extends Event {

	private String eventString;
	
	/**
	  * The constructor is passed a String "Win currentPlayerName" and stores the
	  * corresponding Player object.
	  */
	WinEvent(String eventString){
		super(eventString);
		this.eventString = eventString;
	}
	
	/**
	  * The execute method's purpose is to end the game and display a message informing the player
	  * that victory was achieved.
	  */
	String execute(){
		GameState.instance().getCurrentPlayer().die();
		return "\n" + GameState.instance().getCurrentPlayer().getName() + " won!";
	}
}
