import java.util.ArrayList;

/**
  * An object of EquipCommand represents an instance when the user enters "equip" into the
  * command prompt. Its purpose is to call the Item's equip method, which sets the current
  * weapon/shield/armor as the current player's selected to be used in calculating damage
  * in combat.
  * @author JD
  */
class EquipCommand extends Command {
	
	private String cmd;
	private String itemName;
	
	/**
	  * The constructor takes a String that starts with "equip" and may or may not be
	  * followed by a space and an Item name. If it is followed by a name, the constructor
	  * stores it, if not, it stores it as null and that potential error is handled in execute().
	  */
	EquipCommand(String cmd){
		super(cmd);
		try{
			String[] cmdSplit = cmd.split(" ");
			this.cmd = cmdSplit[0]; //"equip" can be ignored
			this.itemName = cmdSplit[1];
		} catch (ArrayIndexOutOfBoundsException e){
			this.itemName = null;
		}
	}
	
	/**
	  * This method first checks if the item name is given, if the item name given is
	  * in the current player's current room, and then whether or not the Item is a
	  * Shield or Armor. It calls the equip()::Item method on it.
	  * @return a String containing feedback of what was equipped, whether it is a weapon,
	  * shield, or armor, and what (if anything) was unequipped.
	  */
	String execute(){
		if(itemName == null){ //case where user types no name
			return "Equip what?\n";
		}
		
		Room currentRoom = GameState.instance().getCurrentPlayer().getCurrentRoom();
		ArrayList<Item> inventory = GameState.instance().getCurrentPlayer().getInventory();
		Item itemEquip = null;
		Item itemTake = null;
		
		//check inventory for item
		for(Item itemCheck : inventory){
			if(itemCheck.getPrimaryName().equals(itemName)){ //checks to see if there is a primary name match
				itemEquip = itemCheck;
			} else if (itemCheck.goesBy(itemName)){ //checks to see if there is an alias match
				itemEquip = itemCheck;
			}
		}
		
		if (itemEquip != null){
			//equip item from inventory
			itemEquip.equip();
			//remove item from inventory
			GameState.instance().getCurrentPlayer().removeFromInventory(itemEquip);
			return itemEquip.getPrimaryName() + " equipped.\n\n" + GameState.instance().nextPlayer() + GameState.instance().getCurrentPlayer().getCurrentRoom().describe();
		}

		//check room for item
		for(Item itemCheck : currentRoom.getContents()){ //loops through all items in the current room
			if(itemName.equalsIgnoreCase(itemCheck.getPrimaryName())){
				itemTake = itemCheck; //if the command matches a primary name in the room, updates itemTake
			} else if(itemCheck.goesBy(itemName)){
				itemTake = itemCheck; //if the command matches an alias in the room, updates itemTake 
			}
		}

		if (itemTake!=null){
			
			//check that load is not too heavy
			if(GameState.instance().getCurrentPlayer().getInventoryWeight() + itemTake.getWeight() > (10+(GameState.instance().getCurrentPlayer().getStrength()*5))){
				return "Load too heavy.\n";
			}

			//equip item from inventory
			itemTake.equip();
			//remove item from inventory
			currentRoom.remove(itemTake);

			return itemTake.getPrimaryName() + " equipped.\n\n" + GameState.instance().nextPlayer() + "\n" + GameState.instance().getCurrentPlayer().getCurrentRoom().describe() ;
		}

		
		//if not found in inventory or room (both itemTake and itemEquip are null)
		return "There is no " + itemName + "\n";
		
		


	}
}
