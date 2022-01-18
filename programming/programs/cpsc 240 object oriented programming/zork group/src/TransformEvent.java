import java.util.ArrayList;

/**
  * TransformEvent is triggered within ItemSpecificCommand, its purpose being
  * adding an Item to the room and making the original Item disappear with a
  * DisappearEvent.
  * @author JD
  */
class TransformEvent extends Event {
	
	private String eventString;
	private Item oldItem;
	private Item newItem;

	/**
	  * The constructor takes a String "Transform(newItem) oldItem" where Transform
	  * is an identifier in EventFactory, newItem is the name of the Item to add to
	  * the room, and oldItem is the name of the Item that will disappear.
	  */
	TransformEvent(String eventString){
		super(eventString);
		String[] splitA = eventString.split(" ");
		this.eventString = splitA[0];
		this.oldItem = GameState.instance().getDungeon().getItem(splitA[1]);
		String newItemName = splitA[0].substring(10, splitA[0].length() - 1);
		this.newItem = GameState.instance().getDungeon().getItem(newItemName);
	}
	
	/**
	  * This method adds the Item newItem to the current Player's current Room's
	  * contents, and then creates a new DisappearEvent (through EventFactory) to
	  * remove the Item oldItem.
	  * @return a null String
	  */
	String execute(){
		Player p = GameState.instance().getCurrentPlayer();
		ArrayList<Item> inventory = p.getInventory();
		ArrayList<Item> roomContents = p.getCurrentRoom().getContents();
		if(inventory.contains(oldItem)){
			p.addToInventory(newItem);
			if(p.getInventoryWeight() > (10+(p.getStrength()*5))){
				EventFactory.instance().parse("Drop " + newItem.getPrimaryName()).execute();
			}
		}
		
		else if(roomContents.contains(oldItem)){
			p.getCurrentRoom().add(newItem);
		}
		
		if (p.getWeapon()==oldItem){
			p.setWeapon(newItem);	
			if(p.getInventoryWeight() > (10+(p.getStrength()*5))){
				EventFactory.instance().parse("Drop " + newItem.getPrimaryName()).execute();
			}
		}

		if (p.getArmor()==oldItem){
			p.setArmor(newItem);	
			if(p.getInventoryWeight() > (10+(p.getStrength()*5))){
				EventFactory.instance().parse("Drop " + newItem.getPrimaryName()).execute();
			}
		}

		if (p.getShield()==oldItem){
			p.setShield(newItem);	
			if(p.getInventoryWeight() > (10+(p.getStrength()*5))){
				EventFactory.instance().parse("Drop " + newItem.getPrimaryName()).execute();
			}
		}

		





		
		
		
		
		
		
		EventFactory.instance().parse("Disappear " + oldItem.getPrimaryName()).execute();
		return "";
	}

}
