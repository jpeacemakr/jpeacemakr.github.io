import java.util.ArrayList;

/**
  * An object of ItemSpecificCommand represents an instance when the user enters
  * a verb associated with any Item in the .zork file (like "kick can").
  * @author JD
  */
class ItemSpecificCommand extends Command {
	
	private String verb;
	private String noun;
	private String cmd;
	
	/**
	  * The constructor is passed a String "verb" or "verb noun" where the fact
	  * that verb is a verb associated with some Item is an identifier in CommandFactory.
	  * The first case is appropriately handled in execute, while the verb is saved along
	  * with the noun.
	  */
	ItemSpecificCommand(String cmd) {
		super(cmd);
		this.cmd = cmd;
		try {
			String[] cmdSplit = cmd.split(" ");
			this.verb = cmdSplit[0];
			this.noun = cmdSplit[1];
		} catch (ArrayIndexOutOfBoundsException e){
			this.noun = null;
		}
	}
	
	/**
	  * This method triggers any events associated with the command and returns
	  * the command's message (found in the .zork file). In the many cases where
	  * the user may not provide the correct input, appropriate feedback
	  * messages are returned.
	  */
	String execute(){
		if(this.noun == null){
			return verb.substring(0,1).toUpperCase() + verb.substring(1).toLowerCase() + " what?\n";
		}
		
		Room currentRoom = GameState.instance().getCurrentPlayer().getCurrentRoom();
		ArrayList<Item> currentRoomContents = currentRoom.getContents();
		ArrayList<Item> inventory = GameState.instance().getCurrentPlayer().getInventory();
		
		//FOLLOWING IS HANDLING NOUN
		Item item = null;
		//loop through currentRoomContents to define item
		for(Item itemCheck : currentRoomContents){
			if(noun.equalsIgnoreCase(itemCheck.getPrimaryName())){
				item = itemCheck;
			} else if(itemCheck.goesBy(noun)){
				item = itemCheck;
			}
		}
		//loop through inventory to define item IF it is still null
		if(item == null){
			for(Item itemCheck : inventory){
				if(noun.equalsIgnoreCase(itemCheck.getPrimaryName())){
					item = itemCheck;
				} else if(itemCheck.goesBy(noun)){
					item = itemCheck;
				}
			}
		}

		//check armor slot	
		if(item == null){
			if (GameState.instance().getCurrentPlayer().getArmor()!=null){
				Item armorCheck = GameState.instance().getCurrentPlayer().getArmor();
				if(noun.equalsIgnoreCase(armorCheck.getPrimaryName())){
					item = armorCheck;
				} else if(armorCheck.goesBy(noun)){
					item = armorCheck;
				}
			}
		}

		//check weapon slot
		if(item == null){
			if (GameState.instance().getCurrentPlayer().getWeapon()!=null){
				Item weaponCheck = GameState.instance().getCurrentPlayer().getWeapon();
				if(noun.equalsIgnoreCase(weaponCheck.getPrimaryName())){
					item = weaponCheck;
				} else if(weaponCheck.goesBy(noun)){
					item = weaponCheck;
				}
			}
		}

		//check shield slot
		if(item == null){
			if (GameState.instance().getCurrentPlayer().getShield()!=null){
				Item shieldCheck = GameState.instance().getCurrentPlayer().getShield();
				if(noun.equalsIgnoreCase(shieldCheck.getPrimaryName())){
					item = shieldCheck;
				} else if(shieldCheck.goesBy(noun)){
					item = shieldCheck;
				}
			}
		}


		//if item is still null, then it is not in currentRoom or inventory
		if(item == null){
			return "There is no " + this.noun + " here.\n";
		}

		
		//NOW HANDLING VERB
		String message = item.getMessageForVerb(verb);
		if(message == null){
			return "You can't " + verb + " the " + item.getPrimaryName() + ".\n";
		} else {

			/* JOEY'S EVENT NOTE
		 	* At this point, ItemSpecficCommand knows what Item it's being performed on
		 	* So, it should check to see if the Command has any events like [Drop] or [Transform(squishedCan)]
		 	* And if it does, have EventFactory parse a string structured
		 	* "EventString + ItemPrimaryName"
		 	*/

			for(String v : item.getVerbsWithEvents()){
				if(v.startsWith(verb)){ //"stomp[Score(5),Transform(squishedCan)]"
					try{
						String[] verbEventSplit = v.split("\\["); //"Score(5),Transform(squishedCan)]"
						String minusLastBracket = verbEventSplit[1].substring(0,verbEventSplit[1].length() - 1);
						try{
							String[] events = minusLastBracket.split(","); //"Score(5)" and "Transform(squishedCan)
							for(String e : events){
								message += EventFactory.instance().parse(e + " " + item.getPrimaryName()).execute();
							}
						}catch(Exception e){ //just one event
							message += EventFactory.instance().parse(minusLastBracket + " " + item.getPrimaryName()).execute();
						}	
					}catch (Exception e){ //no events
					}
				}
			}
			try{
				return message + "\n" + GameState.instance().nextPlayer();
			}catch(IndexOutOfBoundsException e){ //no next player because they dead af
				return message;
			}
		}
	}
}
