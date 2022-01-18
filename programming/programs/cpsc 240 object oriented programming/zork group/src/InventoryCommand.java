import java.util.ArrayList;

/**
  * This class represents an instance when the user enters "i" in the command
  * prompt. Its purpose is to return the contents of the current player's
  * inventory.
  * @author JD
  */
class InventoryCommand extends Command {
	
	private String cmd;
	
	/**
	  * The contructor is passed a String "i" which only serves as an
	  * identifier in CommandFactory.
	  */
	InventoryCommand(String cmd) {
		super (cmd);
		this.cmd = cmd;
	}
	
	/**
	  * This method simply returns the primary names of all the items in
	  * the current player's inventory, and an appropriate message if
	  * the inventory is empty.
	  */
	String execute() {
		ArrayList<Item> inventory = GameState.instance().getCurrentPlayer().getInventory();
		String cmdStatement = ""; //append to empty string
		String inventoryList = "";

		//print list of inventory items
		if (!inventory.isEmpty()){
			for(Item i : inventory){
				inventoryList += i.getPrimaryName();
				if (inventory.indexOf(i)!=(inventory.size()-1)){
					inventoryList += ", ";
				}
				//System.out.println(i.getPrimaryName() + "\n");
			}
		}

		//print equipped items
		if (!(GameState.instance().getCurrentPlayer().getWeapon()==null)){
			//System.out.println("Weapon: " + GameState.instance().getCurrentPlayer().getWeapon().getPrimaryName() + "\n");
			cmdStatement += "Weapon: " + GameState.instance().getCurrentPlayer().getWeapon().getPrimaryName() +
			       " (Damage: " + GameState.instance().getCurrentPlayer().getWeapon().getDamage() + ")\n";
		}

		if (!(GameState.instance().getCurrentPlayer().getArmor()==null)){
			//System.out.println("Armor: " + GameState.instance().getCurrentPlayer().getArmor().getPrimaryName() + "\n");
			cmdStatement += "Armor: " + GameState.instance().getCurrentPlayer().getArmor().getPrimaryName() +
			       " (Damage reduction: " + GameState.instance().getCurrentPlayer().getArmor().getDamageReduction() + ")\n";
		}

		if (!(GameState.instance().getCurrentPlayer().getShield()==null)){
			//System.out.println("Shield: " + GameState.instance().getCurrentPlayer().getShield().getPrimaryName() + "\n");
			cmdStatement += "Shield: " + GameState.instance().getCurrentPlayer().getShield().getPrimaryName() +
			       " (Chance to block: " + GameState.instance().getCurrentPlayer().getShield().getChanceToBlock() + ")\n";
		}


		if(cmdStatement.equals("") && inventoryList.equals("")){
			return "\nYou have no items in your inventory.\n";
		}

		if(!inventoryList.equals("")){
			inventoryList = "Inventory: " + inventoryList + "\n";
		}
		
		int carryWeight = 10+(GameState.instance().getCurrentPlayer().getStrength()*5);
		String weightStatement = "Carrying capacity: " + GameState.instance().getCurrentPlayer().getInventoryWeight() + "/" + carryWeight + "\n";

		return "\n" + cmdStatement + inventoryList + weightStatement;
	}
}
