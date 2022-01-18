/**
  * WoundEvent is triggered within ItemSpecificCommand and AttackCommand, its purpose being
  * reducing the health of a Character object.
  * @author JD
  */
class WoundEvent extends Event {
	
	private String eventString;
	private Character woundedCharacter; //for combat
	private int numHealthPoints;

	/**
	  * The constructor takes a String "Wound(n) characterName" where Wound is an identifier
	  * in EventFactory, n is an integer that represents how many health points to take away,
	  * and characterName is the name of the Character being wounded.
	  */
	WoundEvent(String eventString){
		super(eventString);
		String[] splitA = eventString.split(" ");
		this.eventString = splitA[0]; //Wound(n)
		String[] splitB = splitA[0].split("\\("); 
		String HPString = splitB[1].substring(0, splitB[1].length() -1);
		this.numHealthPoints = Integer.parseInt(HPString);
	}
	
	/**
	  * This method reduces the health of the correct Character by the correct amount.
	  * @return a null String to conform to superclass Event structure.
	  */
	String execute(){
		Player currentPlayer = GameState.instance().getCurrentPlayer();

		int oldHealth = currentPlayer.getHealth();
		int maxHealth = currentPlayer.getMaxHealth();
		int newHealth = oldHealth - numHealthPoints;
		
		currentPlayer.setHealth(newHealth);

		if(numHealthPoints > 0){ //damage
			if(newHealth <= 0){ //player died
			
				return EventFactory.instance().parse("Die " + currentPlayer.getName()).execute();
			}
			return "\n" + currentPlayer.getName() + " lost " + numHealthPoints + " health points.";

		}else if(numHealthPoints < 0){ //heal
			if(newHealth > maxHealth){
				currentPlayer.setHealth(maxHealth);
			}
			return "\n" + currentPlayer.getName() + " gained " + -numHealthPoints + " health points.";
		}
		return "";
	}

}
