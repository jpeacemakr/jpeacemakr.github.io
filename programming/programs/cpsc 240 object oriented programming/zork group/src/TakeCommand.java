/**
  * An object of TakeCommand represents an instance when the user enters "take" into the
  * command prompt. Its purpose is to add the Item specified by the user into the current
  * player's inventory and remove it from the room.
  * @author JD
  */
class TakeCommand extends Command {
	
	private String cmd;
	private String itemName;
	
	/**
	  * The constructor takes a String that starts with "take" and may or may not be
	  * followed by a space and an Item name. If it is followed by a name, the constructor
	  * stores it, if not, it stores it as null and that potential error is handled in execute().
	  */
	TakeCommand(String cmd){
		super(cmd);
		try{
			//String[] cmdSplit = cmd.split(" ");
			String[] cmdSplit = cmd.split(" ");
			
			this.cmd = cmdSplit[0]; //"take" can be ignored
			this.itemName = cmdSplit[1];
		} catch (ArrayIndexOutOfBoundsException e){
			this.itemName = null;
		}
	}
	
	/**
	  * This method handles many cases of what can follow "take" in the user's input; including null,
	  * all, an item in the room, and an item not in the room. In addition, this method accounts for all known
	  * aliases and enforces a "weight" constraint of 40 on a player's inventory.
	  * @return a String containing feedback to the user of what happened.
	  */
	String execute(){
		if(itemName == null){ //case where user types no name
			return "Take what?\n";
		}

		int load = GameState.instance().getCurrentPlayer().getInventoryWeight();
		Room currentRoom = GameState.instance().getCurrentPlayer().getCurrentRoom();
		Item itemTake = null;
		
		if(itemName.equalsIgnoreCase("all")){ //case where user types all
			String cmdStatement = "";
			for(Item i : currentRoom.getContents()){ //loops through all items in the current room
				if(load + i.getWeight() > (10+(GameState.instance().getCurrentPlayer().getStrength()*5))){
					cmdStatement += "Load too heavy to take " + i.getPrimaryName() + ".\n";
				} else {
					GameState.instance().getCurrentPlayer().addToInventory(i);
					cmdStatement += i.getPrimaryName() + " taken.\n";
					load += i.getWeight();
				}
			}
			if(cmdStatement.equals("")){
				return "There are no items here.\n";
			}
			//Here, a second loop  is used because the iterator throws a ConcurrentModificationException-
			//Reducing the size of currentRoom.contents while iterating through them is a no no
			for(Item i : GameState.instance().getCurrentPlayer().getInventory()){
				if(currentRoom.getContents().contains(i)){
					currentRoom.remove(i);
				}
			}

			return cmdStatement + GameState.instance().nextPlayer();
		}
		//all other cases
		for(Item itemCheck : currentRoom.getContents()){ //loops through all items in the current room
			if(itemName.equalsIgnoreCase(itemCheck.getPrimaryName())){
				itemTake = itemCheck; //if the command matches a primary name in the room, updates itemTake
			} else if(itemCheck.goesBy(itemName)){
				itemTake = itemCheck; //if the command matches an alias in the room, updates itemTake 
			}
		}

		if(itemTake == null){ //meaning it did not match a primary or an alias in the loop
			return "There is no " + itemName + " here.\n";
		} else if(GameState.instance().getCurrentPlayer().getInventory().contains(itemTake)){
			return "You already have the " + itemName + ".\n";
		}
		
		if(load + itemTake.getWeight() > (10+(GameState.instance().getCurrentPlayer().getStrength()*5))){
			return "Load too heavy.\n";
		}
		GameState.instance().getCurrentPlayer().addToInventory(itemTake);
		currentRoom.remove(itemTake);
	
		return itemTake.getPrimaryName() + " taken.\n" + GameState.instance().nextPlayer();
	}	
}
