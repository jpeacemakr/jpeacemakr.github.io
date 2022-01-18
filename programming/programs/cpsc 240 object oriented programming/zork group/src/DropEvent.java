/**
  * DropEvent is triggered within ItemSpecificCommand, and its purpose is to
  * remove an item from the player's inventory and add it to the room.
  * @author JD
  */

class DropEvent extends Event {

	private String eventString;
	private Item droppedItem;
	
	/**
	  * The constructor is passed a String "Drop itemName" with Drop serving as an
	  * identifier in EventFactory and it stores the corresponding item to be dropped.
	  */
	DropEvent(String eventString){
		super(eventString);
		String[] split = eventString.split(" ");
		this.eventString = split[0];
		this.droppedItem = GameState.instance().getDungeon().getItem(split[1]);
	}
	
	/**
	  * execute() removes an item from the current player's inventory and adds it to the room's
	  * contents.
	  * return a null String to conform to superclass Event structure.
	  */
	String execute(){
		if(GameState.instance().getCurrentPlayer().getInventory().contains(droppedItem)){
			GameState.instance().getCurrentPlayer().getInventory().remove(droppedItem);
			GameState.instance().getCurrentPlayer().getCurrentRoom().add(droppedItem);
		}

		if (GameState.instance().getCurrentPlayer().getWeapon()==droppedItem){
			GameState.instance().getCurrentPlayer().setWeapon(null);	
			GameState.instance().getCurrentPlayer().getCurrentRoom().add(droppedItem);
		}

		if (GameState.instance().getCurrentPlayer().getArmor()==droppedItem){
			GameState.instance().getCurrentPlayer().setArmor(null);	
			GameState.instance().getCurrentPlayer().getCurrentRoom().add(droppedItem);
		}

		if (GameState.instance().getCurrentPlayer().getShield()==droppedItem){
			GameState.instance().getCurrentPlayer().setShield(null);	
			GameState.instance().getCurrentPlayer().getCurrentRoom().add(droppedItem);
		}




		return "";
	}
}
