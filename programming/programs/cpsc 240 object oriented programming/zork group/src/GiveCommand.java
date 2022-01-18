/**
  * An object of class GiveCommand represents an instance where the user
  * enters "give" into the command prompt.
  * @author JD
  */
class GiveCommand extends Command{
	
	private String cmd; //"give itemName to charName"
	private String itemName;
	private String charName;

	/**
	  * The constructor is passed a String that starts with "give" as an identifier
	  * in CommandFactory. The ideal case is "give itemName to charName" where
	  * both the itemName and charName are saved, though alternative cases due to
	  * incorrect user input are handled appropriately.
	  */
	GiveCommand(String cmd){
		super(cmd);
		try{
			String[] cmdSplit = cmd.split(" ");
			this.cmd = cmdSplit[0]; //"give" can be ignored
			this.charName = cmdSplit[3];
		} catch (ArrayIndexOutOfBoundsException e){
			this.charName = null; //give to who?
		}
		try{
			String[] cmdSplit = cmd.split(" ");
			this.cmd = cmdSplit[0]; //"give" can be ignored
			this.itemName = cmdSplit[1];
		} catch (ArrayIndexOutOfBoundsException e){
			this.itemName = null; //give what?
		}
	}

	/**
	  * This method removes the item from the current Player's inventory,
	  * adds it to the target Character's inventory, changes the hostility of
	  * the Character proportionally to the damage of the Item given, and
	  * increments the turn.
	  * @return a feedback String either prompting for correct input or informing
	  * the user of a successful exchange, and the new hostility.
	  */
	String execute(){
		if(itemName == null){ //"give"
			return "Give what to whom?\n";
		}

		if(itemName.equalsIgnoreCase("to")){ //"give to" OR "give to char"
			return "Give what?\n";
		}

		if(charName == null){ //"give item" OR "give item to"
			return "Give " + itemName + " to whom?\n";
		}

		Player currentPlayer = GameState.instance().getCurrentPlayer();
		Item itemGive = null;
		try{
			NonPlayableCharacter target = GameState.instance().getNPCNamed(charName);
			if(GameState.instance().getCurrentPlayer().getWeapon() != null){
				if (GameState.instance().getCurrentPlayer().getWeapon().goesBy(itemName)){
					itemGive = GameState.instance().getCurrentPlayer().getWeapon();
					GameState.instance().getCurrentPlayer().setWeapon(null);
					target.addToInventory(itemGive);
					target.setHostility(target.getHostility() + itemGive.getWeight());
					GameState.instance().nextPlayer();
					return itemGive.getPrimaryName() + " given to " + charName + ".\n";
				}
			}
			if(GameState.instance().getCurrentPlayer().getArmor() != null){
				if (GameState.instance().getCurrentPlayer().getArmor().goesBy(itemName)){
					itemGive = GameState.instance().getCurrentPlayer().getArmor();
					GameState.instance().getCurrentPlayer().setArmor(null);
					target.addToInventory(itemGive);
					target.setHostility(target.getHostility() + itemGive.getWeight());
					GameState.instance().nextPlayer();
					return itemGive.getPrimaryName() + " given to " + charName + ".\n";
				}
			}
			if(GameState.instance().getCurrentPlayer().getShield() != null){
				if (GameState.instance().getCurrentPlayer().getShield().goesBy(itemName)){
					itemGive = GameState.instance().getCurrentPlayer().getShield();
					GameState.instance().getCurrentPlayer().setShield(null);
					target.addToInventory(itemGive);
					target.setHostility(target.getHostility() + itemGive.getWeight());
					GameState.instance().nextPlayer();
					return itemGive.getPrimaryName() + " given to " + charName + ".\n";
				}
			} 
		}catch (Character.NoCharacterException x){
			try{
				Player target = GameState.instance().getPlayerNamed(charName);
				if(GameState.instance().getCurrentPlayer().getWeapon() != null){
					if (GameState.instance().getCurrentPlayer().getWeapon().goesBy(itemName)){
						itemGive = GameState.instance().getCurrentPlayer().getWeapon();
						GameState.instance().getCurrentPlayer().setWeapon(null);
						target.addToInventory(itemGive);
						GameState.instance().nextPlayer();
						return itemGive.getPrimaryName() + " given to " + charName + ".\n";
					}
				}
				if(GameState.instance().getCurrentPlayer().getArmor() != null){
					if (GameState.instance().getCurrentPlayer().getArmor().goesBy(itemName)){
						itemGive = GameState.instance().getCurrentPlayer().getArmor();
						GameState.instance().getCurrentPlayer().setArmor(null);
						target.addToInventory(itemGive);
						GameState.instance().nextPlayer();
						return itemGive.getPrimaryName() + " given to " + charName + ".\n";
					}
				}
				if(GameState.instance().getCurrentPlayer().getShield() != null){
					if (GameState.instance().getCurrentPlayer().getShield().goesBy(itemName)){
						itemGive = GameState.instance().getCurrentPlayer().getShield();
						GameState.instance().getCurrentPlayer().setShield(null);
						target.addToInventory(itemGive);
						GameState.instance().nextPlayer();
						return itemGive.getPrimaryName() + " given to " + charName + ".\n";
					}
				} 
			}catch (Character.NoCharacterException e1){
				return "I don't know who " + charName + " is.\n";
			}
		}

		try{
			itemGive = currentPlayer.getItemFromInventoryNamed(itemName);
			int dmg = itemGive.getDamage();
			try{
				NonPlayableCharacter target = GameState.instance().getNPCNamed(charName);
				target.addToInventory(itemGive);
				currentPlayer.removeFromInventory(itemGive);
				target.setHostility(target.getHostility() + itemGive.getWeight());
				GameState.instance().nextPlayer();
				return itemName + " given to " + charName + ".\n";
			} catch (Character.NoCharacterException e){
				try{
					Player target = GameState.instance().getPlayerNamed(charName);
					target.addToInventory(itemGive);
					currentPlayer.removeFromInventory(itemGive);
					return itemName + " given to " + charName + "." + GameState.instance().nextPlayer();
				}catch (Character.NoCharacterException e1){
					return "I don't know who " + charName + " is.\n";
				}
			}
		} catch (Item.NoItemException e0){
			return "You don't have the " + itemName + ".\n";
		}
	}
}















