
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Scanner;
import java.io.FileReader;

/**
 * An Item represents any physical thing that a character can add to their 
 * inventory. Items have an associated weight, and damage. Items can have 
 * their own messages associated with a verb. When entered by the user, 
 * these verbs may or may not have an associated {@link Event}. Items can
 * be equipped and used as a weapon, or in the case of the {@link Shield}
 * and {@link Armor} subclasses, equipped to block and reduce damage
 * respectively.   
 * @author Michael Goyer
 */
public class Item {

	//---Instance Variables---
	protected String primaryName;
	protected int weight;
	protected int damage;
	protected Hashtable<String,String> messages; //String verb, String Message 
	protected ArrayList<String> aliases;
	static ArrayList<String> VERBS= new ArrayList<String>();
	protected ArrayList<String> verbsWithEvents;
	//---Methods---

	/**
	 * Given a scanner positioned at the beginning of an Item file entry, constructs 
	 * an Item object with the associated values. Hydrates the damage and weight statistics for 
	 * the Item, as well as any associated verbs and their corresponding messages. 
	 * @param s The scanner used to hydrate the Item from a file.
	 * @throws NoItemException if and when the scanner is not positioned at an Item entry in it's file.    
	 */
	public Item(Scanner s) throws NoItemException
	{
		this.aliases = new ArrayList<String>();
		this.messages = new Hashtable<String,String>();
		String itemNames = s.nextLine(); 
		this.verbsWithEvents = new ArrayList<String>();
		this.damage = 0;
		//if next line is not the delimiter, go through list of items in the room
		if (!itemNames.equals("===")){
			
			//get Primary Name
			String[] itemsSplitNames = itemNames.split(",");
			this.primaryName = itemsSplitNames[0];
			
			//System.out.println("Hydrating " +this.getPrimaryName());

			//get aliases
			for (int i=1; i<itemsSplitNames.length; i++){
				this.aliases.add(itemsSplitNames[i]);
			}
			
			//get weight and damage
			String[] weightDamageSplit = s.nextLine().split(",");
			this.weight = java.lang.Integer.valueOf(weightDamageSplit[0]);
			if (weightDamageSplit.length==1){
				this.damage = 1;
			} else {
				this.damage = java.lang.Integer.valueOf(weightDamageSplit[1]);
			}

			//get verbs and responses and events
			String itemVerb = s.nextLine();
			while (!itemVerb.equals("---")){
				String[] itemSplitVerb = itemVerb.split(":");
				try{ //try to split at "[" to separate verbs from events
					String[] verbEventSplit = itemSplitVerb[0].split("\\[");
					this.messages.put(verbEventSplit[0],itemSplitVerb[1]);
					VERBS.add(verbEventSplit[0]); //static list of verbs CommandFactory uses to check ItemSpecific vs Unknown
					this.verbsWithEvents.add(itemSplitVerb[0]); //list for each item used within ItemSpecific to initiate necessary events
					itemVerb = s.nextLine();
				}catch(Exception e){ //caught if there is no "[" to split at
					this.messages.put(itemSplitVerb[0],itemSplitVerb[1]);
					VERBS.add(itemSplitVerb[0]);
					this.verbsWithEvents.add(itemSplitVerb[0]);
					itemVerb = s.nextLine();
				}
			}

		} else {
			throw new NoItemException("No more items in file to create.");
		}		
	}


	/**
	 * Returns a boolean representing whether the passed string is an alias associated with the Item.
	 * Items hav one primary name, and can have many aliases by which they can be referred to by the user.
	 * If the passed string matches any strings in the item's list of aliases, returns true. Otherwise, returns false.
	 * @param name The string being checked to see if it is a valid alias for the Item.
	 */
	public boolean goesBy(String name){
		if(primaryName.equalsIgnoreCase(name)){
			return true;
		}
		//for loop through aliases, return true if name.equals any of those strings.
		for (int i = 0; i < aliases.size(); i++){
			if (aliases.get(i).equalsIgnoreCase(name)){
				return true;
			}
		}
		return false;
	}

	/**
	 * Returns a string containing the item's primary name. Items have one primary name, 
	 * and can have many aliases. This method returns the primary name. 
	 */
	public String getPrimaryName(){
		return this.primaryName;
	}

	/**
	 * Returns the message String associated with the passed string, given that the 
	 * passed string is a valid verb for the Item.
	 * @param verb A string containing a verb associated with a message for the Item. 
	 */
	public String getMessageForVerb(String verb){
		//if(!this.messages.keySet().contains(verb)){
		//	throw new Exception();
		//}
		return messages.get(verb);
	}

	/**
	 * Returns a string containing a brief description of the Item. Includes the 
	 * primary name of the Item, and it's weight.
	 */ 
	public String toString(){
		return "A " + this.primaryName + " with a weight of " + this.weight;		
	}
	
	public ArrayList<String> getVerbsWithEvents(){
		return this.verbsWithEvents;
	}

	/**
	 * Returns an int representing the space in a Character's inventory that an Item occupies. Characters
	 * have a set amount of weight that they can carry, based on their strength statistic. Items will 
	 * each occupy a portion of that total weight when in a character's inventory, or equipped.
	 */
	public int getWeight(){
		return this.weight;
	}

	/**
	 * Returns an int representing the amount of damage that the Item inflicts when used as a weapon. 
	 * An Item's base damge is added to the product of the character's strength and score statistics
	 * to find that character's damage with that Item. 
	 */
	public int getDamage(){
		return this.damage;
	}

	public int getChanceToBlock(){
		return 0;
	}
	
	public int getDamageReduction(){
		return 0;
	}
	

	
	/**
	 * Moves an Item from a character's inventory to their equippedWeapon slot. A character's 
	 * equipped weapon is the Item that they will use in combat, inflicting damage based upon 
	 * the player's specific statistics. See {@link Item#getDamage()} method.  
	 */
	public void equip(){
		//move current weapon to player's inventory
		if (GameState.instance().getCurrentPlayer().getWeapon() != null) {
			GameState.instance().getCurrentPlayer().addToInventory(GameState.instance().getCurrentPlayer().getWeapon());
		}	

		//equip new weapon
		GameState.instance().getCurrentPlayer().setWeapon(this);

	}
	

	public void unequip(){

	}
	

	
	/**
	 * Extension of Exception used to indicate when all of the Items in a file have been hydrated. This 
	 * Exception is thrown by the Item constructor when it finishes hydrating all of the  items in a file. 
	 */
	public static class NoItemException extends Exception {
		public NoItemException(String e) {
			super(e);
		}
	}
}






