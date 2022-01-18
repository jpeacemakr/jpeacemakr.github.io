import java.util.ArrayList;

/**
  * An object of DropCommand represents an instance when the user enters "take" into the
  * command prompt. Its purpose is to remove the Item specified by the user from the current
  * player's inventory and add it into the room.
  * @author JD
  */
class DropCommand extends Command {
	
	private String cmd;
	private String itemName;
	
	/**
	  * The constructor takes a String that starts with "drop" and may or may not be
	  * followed by a space and an Item name. If it is followed by a name, the constructor
	  * stores it, if not, it stores it as null and that potential error is handled in execute().
	  */
	DropCommand(String cmd){
		super(cmd);
		try{
			String[] cmdSplit = cmd.split(" ", 2);
			this.cmd = cmdSplit[0]; //"drop" can be ignored
			this.itemName = cmdSplit[1];
		} catch (ArrayIndexOutOfBoundsException e){
			this.itemName = null;
		}
	}

	/**
	  * This method handles many cases of what can follow "drop" in the user's input; including null,
	  * all, an item in the room, and an item not in the room. In addition, this method accounts for all known
	  * aliases.
	  * @return a String containing feedback to the user of what happened.
	  */
	String execute(){
		if(itemName == null){
			return "Drop what?\n";
		}
		
		Room currentRoom = GameState.instance().getCurrentPlayer().getCurrentRoom();
		ArrayList<Item> inventory = GameState.instance().getCurrentPlayer().getInventory();
		Item itemDrop = null;

		if(itemName.equalsIgnoreCase("all")){
			String cmdStatement = ""; //blank string to append to
			for(Item i : inventory){
				currentRoom.add(i);
				cmdStatement += i.getPrimaryName() + " dropped.\n";
			}
			//following loop avoids ConcurrentModificationException
			for(Item i : currentRoom.getContents()){
				if(inventory.contains(i)){ //if there is a duplicate, that means it was just dropped
					inventory.remove(i); //and must be removed
				}
			}
			if(cmdStatement.equals("")){
				return "You have nothing to drop, silly!\n";
			}
			return cmdStatement + "\n" + GameState.instance().nextPlayer() + GameState.instance().getCurrentPlayer().getCurrentRoom().describe();
		}

		for(Item itemCheck : inventory){
			if(itemCheck.getPrimaryName().equals(itemName)){ //checks to see if there is a primary name match
				itemDrop = itemCheck;
			}else if (itemCheck.goesBy(itemName)){ //checks to see if there is an alias match
				itemDrop = itemCheck;
			}
		}
		

		//Check equipped items 
		if (GameState.instance().getCurrentPlayer().getWeapon() != null){
			Item itemEquip = GameState.instance().getCurrentPlayer().getWeapon();
			if(itemEquip.getPrimaryName().equals(itemName) || itemEquip.goesBy(itemName)){
				currentRoom.add(itemEquip);
				GameState.instance().getCurrentPlayer().setWeapon(null);
				return itemEquip.getPrimaryName() + " dropped.\n\n" + GameState.instance().nextPlayer() + GameState.instance().getCurrentPlayer().getCurrentRoom().describe();
			}
		}		

		if (GameState.instance().getCurrentPlayer().getArmor() != null){
			Item itemEquip = GameState.instance().getCurrentPlayer().getArmor();
			if(itemEquip.getPrimaryName().equals(itemName) || itemEquip.goesBy(itemName)){
				currentRoom.add(itemEquip);
				GameState.instance().getCurrentPlayer().setArmor(null);
				return itemEquip.getPrimaryName() + " dropped.\n\n" + GameState.instance().nextPlayer() + GameState.instance().getCurrentPlayer().getCurrentRoom().describe();
			}
		}		

		if (GameState.instance().getCurrentPlayer().getShield() != null){
			Item itemEquip = GameState.instance().getCurrentPlayer().getShield();
			if(itemEquip.getPrimaryName().equals(itemName) || itemEquip.goesBy(itemName)){
				currentRoom.add(itemEquip);
				GameState.instance().getCurrentPlayer().setShield(null);
				return itemEquip.getPrimaryName() + " dropped.\n\n" + GameState.instance().nextPlayer() + GameState.instance().getCurrentPlayer().getCurrentRoom().describe();
			}
		}		


		if(itemDrop == null){ //i.e. was never updated in loop
			return "You dont't have the " + itemName + ".\n";
		}
		
		currentRoom.add(itemDrop);
		inventory.remove(itemDrop);
		return itemDrop.getPrimaryName() + " dropped.\n\n" + GameState.instance().nextPlayer()+ "\n" + GameState.instance().getCurrentPlayer().getCurrentRoom().describe();
	}
}
