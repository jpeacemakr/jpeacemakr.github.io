/**
  * ScoreEvent is triggered any time the player makes an accomplishment.
  * This is most prominently in ItemSpecificCommand, AttackCommand, and KillEvent.
  * @author JD
  */
class ScoreEvent extends Event {
	
	private String eventString;
	private int numPoints;

	/**
	  * The constructor takes a String "Score(n) currentPlayerName" where Score is
	  * an identifier for EventFactory, n is an integer value representing the number
	  * of points the Player just earned, and currentPlayerName is used to store the
	  * Player object whose turn it is.
	  */
	ScoreEvent(String eventString){
		super(eventString);
		String[] splitA = eventString.split(" ");
		this.eventString = splitA[0]; //Score(n)
		String[] splitB = splitA[0].split("\\("); 
		String pointString = splitB[1].substring(0, splitB[1].length() -1);
		this.numPoints = Integer.parseInt(pointString);
	}
	
	/**
	  * This method increments the current player's score by an amount specified in the
	  * constructor's parameters.
	  * @return a null String.
	  */
	String execute(){
		int oldScore = GameState.instance().getCurrentPlayer().getScore();
		int newScore = oldScore + numPoints;
		if(newScore>50){
			GameState.instance().getCurrentPlayer().setScore(50);
			return "";
		}
		GameState.instance().getCurrentPlayer().setScore(newScore);
		return "";
	}


}
