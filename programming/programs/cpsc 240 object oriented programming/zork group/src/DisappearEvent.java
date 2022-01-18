/**
  * DisappearEvent is triggered within ItemSpecificCommand, and makes the Item
  * unobtainable to the player from anywhere within the dungeon.
  * @author JD
  */
class DisappearEvent extends Event {
	
	private String eventString;
	private Item disappearedItem;
	
	/**
	  * The constructor takes a String "Disappear itemName" with Disappear serving as an identifier
	  * in EventFactory, and it stores the item with the name itemName.
	  */
	DisappearEvent(String eventString){
		super(eventString);
		String[] split = eventString.split(" ");
		this.eventString = split[0];
		this.disappearedItem = GameState.instance().getDungeon().getItem(split[1]);
	}

	/**
	  * This method removes an item from the current room if it is there,
	  * and from the current player's inventory if it was not in the room,
	  * effectively making it disappear from the dungeon.
	  * @return an empty String to confrom to superclass Event structure.
	  */
	String execute(){
		Player currentPlayer = GameState.instance().getCurrentPlayer();
		Room currentRoom = currentPlayer.getCurrentRoom();
		if(currentPlayer.getInventory().contains(disappearedItem)){
			currentPlayer.getInventory().remove(disappearedItem);
		}
		if(currentRoom.getContents().contains(disappearedItem)){
			currentRoom.remove(disappearedItem);
		}
		if (GameState.instance().getCurrentPlayer().getWeapon()==disappearedItem){
			GameState.instance().getCurrentPlayer().setWeapon(null);	
		}
		if (GameState.instance().getCurrentPlayer().getArmor()==disappearedItem){
			GameState.instance().getCurrentPlayer().setArmor(null);	
		}
		if (GameState.instance().getCurrentPlayer().getShield()==disappearedItem){
			GameState.instance().getCurrentPlayer().setShield(null);	
		}
		return "";
	}

}
