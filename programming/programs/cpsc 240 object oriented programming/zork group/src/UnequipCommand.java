import java.util.ArrayList;

class UnequipCommand extends Command {
	
	private String cmd;
	private String itemName;
	
	/**
	  * The constructor takes a String that starts with "unequip" and may or may not be
	  * followed by a space and an Item name. If it is followed by a name, the constructor
	  * stores it, if not, it stores it as null and that potential error is handled in execute().
	  */
	UnequipCommand(String cmd){
		super(cmd);
		try{
			String[] cmdSplit = cmd.split(" ");
			this.cmd = cmdSplit[0]; //"equip" can be ignored
			this.itemName = cmdSplit[1];
		} catch (ArrayIndexOutOfBoundsException e){
			this.itemName = null;
		}
	}
	
	
	
	
	
	String execute(){
		if(itemName == null){ //case where user types no name
			return "Unequip what?\n";
		}
		
		ArrayList<Item> inventory = GameState.instance().getCurrentPlayer().getInventory();
		Item itemEquip = null;

		//Check equipped items 
		if (GameState.instance().getCurrentPlayer().getWeapon() != null){
			itemEquip = GameState.instance().getCurrentPlayer().getWeapon();
			if(itemEquip.getPrimaryName().equals(itemName) || itemEquip.goesBy(itemName)){
				GameState.instance().getCurrentPlayer().addToInventory(itemEquip);
				GameState.instance().getCurrentPlayer().setWeapon(null);
				return itemEquip.getPrimaryName() + " unequipped.\n\n" + GameState.instance().nextPlayer() + GameState.instance().getCurrentPlayer().getCurrentRoom().describe();
			}
		}		

		if (GameState.instance().getCurrentPlayer().getArmor() != null){
			itemEquip = GameState.instance().getCurrentPlayer().getArmor();
			if(itemEquip.getPrimaryName().equals(itemName) || itemEquip.goesBy(itemName)){
				GameState.instance().getCurrentPlayer().addToInventory(itemEquip);
				GameState.instance().getCurrentPlayer().setArmor(null);
				return itemEquip.getPrimaryName() + " unequipped\n\n" + GameState.instance().nextPlayer() + GameState.instance().getCurrentPlayer().getCurrentRoom().describe();
			}
		}		

		if (GameState.instance().getCurrentPlayer().getShield() != null){
			itemEquip = GameState.instance().getCurrentPlayer().getShield();
			if(itemEquip.getPrimaryName().equals(itemName) || itemEquip.goesBy(itemName)){
				GameState.instance().getCurrentPlayer().addToInventory(itemEquip);
				GameState.instance().getCurrentPlayer().setShield(null);
				return itemEquip.getPrimaryName() + " unequipped.\n\n" + GameState.instance().nextPlayer() + GameState.instance().getCurrentPlayer().getCurrentRoom().describe();
			}
		}		

		//if item is not equipped
		return "You dont't have the " + itemName + " equipped.\n";
		
	}
}
