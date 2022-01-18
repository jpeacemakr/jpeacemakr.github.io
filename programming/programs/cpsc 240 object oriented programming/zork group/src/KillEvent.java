/**
  * KillEvent represents the death of a NonPlayableCharacter, and it is
  * triggered in AttackCommand when the NPC's health is reduced to 0 or below.
  * @author JD
  */
class KillEvent extends Event {
	
	private String eventString;
	//private NonPlayableCharacter killedNPC;
	
	/**
	  * The constructor is passed a String "Kill NPCName" where Kill is an
	  * identifier for EventFactory and NPCName is used to store the
	  * NonPlayableCharacter object that has to die.
	  */
	KillEvent(String eventString){
		super(eventString);
		String[] split = eventString.split(" ");
		this.eventString = split[0];
		//getNPCNamed split[1] yaddah yaddah save for later
	}
	
	/**
	  * This method's purpose is to remove the NonPlayableCharacter from the
	  * current Room, and add the NonPlayableCharacter's inventory to the current
	  * room's contents.
	  * @return currentPlayerName killed NPCName.
	  */
	String execute(){
		return null;
	}

}
