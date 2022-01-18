
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;


/**
 * A <tt>Player</tt> represents a user's character in a Zork-like, text-based game.<p>
 * A player is controlled by the user. It can move from room to room, interact with items and NPCs, take damage and die.<p>
 * The Player class extends the {@link Character} class.<p>
 * Each player has a current room, score, current health and max health. Each player can equip a weapon, shield and armor.<p>
 * Each player has a {@link PlayerType} assigned to it to set the player's stats (endurance, dexterity, and strength).<p>
 * Endurance is used to calculate a player's max health.<p>
 * Dexterity is used to calculate a player's chance to hit with an attack and the chance to block with a shield.<p>
 * Strength is used to calculate a player's damage with or without a weapon.<p>
 * A player is dead when their health is 0 or below. When they die, they drop their inventory and equipped items and are removed from the game.
 * @author James Peacemaker
 */
class Player extends Character {


 	private PlayerType playerType;
	static String CURRENT_ROOM_LEADER = "current room:";
	//static String ADVENTURER_LEADER = "Adventurer:";
	static String INVENTORY_LEADER = "inventory:";





	/**
	 * Constructs a new player given a name and a room.<p>
	 * This constructor inherits from the {@link Character} constructor.<p>
	 * It sets the {@link PlayerType} of the Player to the default values of the PlayerType constructor until the {@link Player#setPlayerType} method is called.
	 * @param name The name for the new player.
	 * @param r The current room for the new player.
	 */
	Player(String name, Room r){
		super(name, r);	
		this.playerType = new PlayerType(); // sets type to default PlayerType
		this.setHealth(this.getEndurance()*10);//set health based on endurance
		this.setMaxHealth(this.getEndurance()*10);//set health based on endurance
	}




	/**
	 * Reads information from a .sav file that is used to set the player's name, player type, current health, score, current room, inventory and equipped items for a player.<p>
	 * Information for the player must be in the following format:<p>
	 *<blockquote>* 1. A line with the player's name followed by ":".<br>
	 * 2. A line starting with "class:" followed by the player's PlayerType. The listed PlayerType must be in the GameState.<br>
	 * 3. A line starting with "Current room:" followed by the name of the player's current room. The room name must match one of the rooms loaded in the GameState's Dungeon.<br>
	 * 4. A line starting with "inventory:" followed by a list of items separated by ",". These are the items in the player's inventory. The names of the items listed here must match items in the GameState.<br>
	 * 5. A line starting with "weapon:" followed by the name of an item. The item must be an item in the GameState's items.   <br>
	 * 6. A line starting with "armor:" followed by the name of an armor. The armor must be an armor in the GameState's items.   <br>
	 * 7. A line starting with "shield:" followed by the name of a shield. The shield must be a shield in the GameState's items.   <br>
	 * 8. A line starting with "health:" followed by an int.<br>
	 * 9. A line starting with "score:" followed by an int.<br>
	 * 10. A line with "---" which is a delimiter used to mark the end of the player's entry.</blockquote><p>
	 * If any of the lines are missing, the following default values will be assigned: name, Adventurer; player type, default as defined by PlayerType(); current room, the dungeon's entry room; inventory, empty; weapon, empty; armor, empty; shield, empty; health, maximum health as defined by Player constructor method; score, 0. 
	 * @throws NoCharacterException if the player information can't be hydrated or if the delimiter "===" is reached.
*/
	Player(Scanner s) throws Character.NoCharacterException {
		super(s);
		try {
			
			//get "Name of PLayer:" and throw error if not found
			String nameLine = s.nextLine();

			if (nameLine.equals("---")){
				nameLine = s.nextLine();
			}

			if (nameLine.equals("===")){
				throw new Character.NoCharacterException("Done hydrating players");
			}

			nameLine = nameLine.substring(0, nameLine.length()-1);//remove ":" from the end of name
			this.setName(nameLine);

			//get current room
			String currentRoomLine = s.nextLine();
			this.setCurrentRoom(GameState.instance().getDungeon().getRoom(currentRoomLine.substring(CURRENT_ROOM_LEADER.length())));

			//get inventory
			//remove "Inventory:" and split line into an array of strings
			String[] inventoryList = s.nextLine().substring(INVENTORY_LEADER.length()).split(",");
			//add each part of array as an item
			for (int i=0; i<inventoryList.length; i++){
				if (!inventoryList[i].equals("")){
					this.addToInventory(GameState.instance().getDungeon().getItem(inventoryList[i]));
					//System.out.println("adding to inventory" + inventoryList[i] + "o");
				}
			}
			
			//set default player type. this will be overwritten below if player type found when hydrating	
			this.playerType = new PlayerType();
			this.setHealth(this.getEndurance()*10);
			this.setMaxHealth(this.getEndurance()*10);
			
			String textLine = " ";

			//hydrate equipped items and player type if present	
			while (!textLine.equals("---")){
				try {
					textLine = s.nextLine();
					//break line of text into stat name and value
					String[] textListSplit = textLine.split(":");
					//set weapon
					if (textListSplit[0].equals("weapon")) {
						this.setWeapon(GameState.instance().getDungeon().getItem(textListSplit[1]));
					}
					//set armor
					if (textListSplit[0].equals("armor")) {
						this.setArmor(GameState.instance().getDungeon().getItem(textListSplit[1]));
					}
					//set shield
					if (textListSplit[0].equals("shield")) {
						this.setShield(GameState.instance().getDungeon().getItem(textListSplit[1]));
					}
					//set player type
					if (textListSplit[0].equals("class")) {
						this.setPlayerType(GameState.instance().getPlayerTypeNamed(textListSplit[1]));
					}
					//set health
					if (textListSplit[0].equals("health")) {
						this.setHealth(java.lang.Integer.valueOf(textListSplit[1]));
					}
					//set score
					if (textListSplit[0].equals("score")) {
						this.setScore(java.lang.Integer.valueOf(textListSplit[1]));
					}

				}
				catch (Exception e) { break; } //break loop if nextline throws error (as in end of file)
			}

			
		}
		catch (Exception e){
			throw new Character.NoCharacterException("Done hydrating players");
		}
}





	/**
	 * Makes the player die. <p>
	 * All items in the player's inventory and equipped items are dropped into the player's current room. The player is then removed from the game.
	 */
	public void die(){

		if (this.getWeapon() != null){
			this.currentRoom.add(this.getWeapon());
		}		

		if (this.getArmor() != null){
			this.currentRoom.add(this.getArmor());
		}		

		if (this.getShield() != null){
			this.currentRoom.add(this.getShield());
		}		

		for(Item i : this.inventory){
			this.currentRoom.add(i);
		}
		GameState.instance().removePlayer(this);
	}



	/**
	 * Sets the player's {@link PlayerType}.
	 * @param newType The new PlayerType that will be assigned to the player. Health is set based on endurance. 
	 */
	public void setPlayerType(PlayerType newType){
		this.playerType = newType;
		this.setHealth(this.getEndurance()*10);
		this.setMaxHealth(this.getEndurance()*10);
	}




	/**
	 * Returns the player's endurance based on the player's {@link PlayerType}.
	 * @return The player's endurance.
	 */
	public int getEndurance() {
		return this.playerType.getEndurance();
	}


	/**
	 * Returns the player's dexterity based on the player's {@link PlayerType}.
	 * @return The player's dexterity.
	 */
	public int getDexterity() {
		return this.playerType.getDexterity();
	}


	/**
	 * Returns the player's strength based on the player's {@link PlayerType}.
	 * @return The player's strength.
	 */
	public int getStrength() {
		return this.playerType.getStrength();
	}



	/*THIS METHOD CAN BE DELETED?
	 * Returns the item in the player's current room or inventory that has a name or alias that matches the given String. It will return only one item with the matching name, first checking the player's inventory then the player's room. If the item is not found in either place, it will throw an {@link Item.NoItemException}.
	 * @param name The name of the item being searched for.
	 * @return The Item with a name or alias that matches.
	 * @throws Item.NoItemException if the Item can't be found in the current player's inventory or room
	 */
/*Item getItemInVicinityNamed(String name) throws Item.NoItemException {
		///////////////////////////NEEDS TO CHECK PLAYER'S INVENTORY FOR ITEM TOO
		for(Item itemCheck : this.getCurrentRoom().getContents()){ //loops through all items in the current room
			if(name.equalsIgnoreCase(itemCheck.getPrimaryName())){
				return itemCheck; //if the command matches a primary name in the room, updates itemTake
			} else if (itemCheck.goesBy(name)){
				return itemCheck; //if the command matches an alias in the room, updates itemTake 
			}
		}	
		throw new Item.NoItemException("No item found.");
	}
*/




	/**
	 * Returns the combined weight of all items in the player's inventory, including equipped items.
	 * @return the combined weight of all items in the player's inventory, including equipped items. 
	 */
	int getInventoryWeight(){
		int sum = 0;
		for(Item i : this.inventory){
			sum += i.getWeight();
		}

		if (this.getWeapon()!=null){
			sum += this.getWeapon().getWeight();
		}
		
		if (this.getArmor()!=null){
			sum += this.getArmor().getWeight();
		}	
		
		if (this.getShield()!=null){
			sum += this.getShield().getWeight();
		}
		
		return sum;

	}




	/*THIS METHOD AN BE DELETED?
	 * Reads information from a .sav file that is used to set the player's name, player type, current health, score, current room, inventory and equipped items for a player.<p>
	 * Information for the player must be in the following format:<p>
	 *<blockquote>* 1. A line with the player's name followed by ":".<br>
	 * 2. A line starting with "class:" followed by the player's PlayerType. The listed PlayerType must be in the GameState.<br>
	 * 3. A line starting with "Current room:" followed by the name of the player's current room. The room name must match one of the rooms loaded in the GameState's Dungeon.<br>
	 * 4. A line starting with "inventory:" followed by a list of items separated by ",". These are the items in the player's inventory. The names of the items listed here must match items in the GameState.<br>
	 * 5. A line starting with "weapon:" followed by the name of an item. The item must be an item in the GameState's items.   <br>
	 * 6. A line starting with "armor:" followed by the name of an armor. The armor must be an armor in the GameState's items.   <br>
	 * 7. A line starting with "shield:" followed by the name of a shield. The shield must be a shield in the GameState's items.   <br>
	 * 8. A line starting with "health:" followed by an int.<br>
	 * 9. A line starting with "score:" followed by an int.<br>
	 * 10. A line with "---" which is a delimiter used to mark the end of the player's entry.</blockquote><p>
	 * If any of the lines are missing, the following default values will be assigned: name, Adventurer; player type, default as defined by PlayerType(); current room, the dungeon's entry room; inventory, empty; weapon, empty; armor, empty; shield, empty; health, maximum health as defined by Player constructor method; score, 0. 
	 * @throws NoCharacterException if the player information can't be hydrated or if the delimiter "===" is reached.
*/
	/*void restore(Scanner s) throws Character.NoCharacterException {

		     /*	//get current room
		     //String currentRoomLine = s.nextLine();
		     //this.currentRoom = dungeon.getRoom(currentRoomLine.substring(CURRENT_ROOM_LEADER.length()));

		     //get inventory
		     //remove "Inventory:" and split line into an array of strings
		     //String[] inventoryList = s.nextLine().substring(INVENTORY_LEADER.length()).split(",");
		     //add each part of array as an item
		     for (int i=0; i<inventoryList.length; i++){
		     if (!inventoryList[i].equals("")){
		     this.addToInventory(getDungeon().getItem(inventoryList[i]));
		     //System.out.println("adding to inventory" + inventoryList[i] + "o");
		     }
		     }
		     i*/
//	}



	/**
	 * Writes information into a .sav file that is used to save the player's name, player type, current health, score, current room, inventory and equipped items for a player.<p>
	 * Information for the player must be written in the following format:<p>
	 * <blockquote>1. A line with the player's name followed by a ":".<br>
	 * 2. A line starting with "class:" followed by the player's PlayerType. The listed PlayerType must be in the GameState.<br>
	 * 3. A line starting with "Current room:" followed by the name of the player's current room. The room name must match one of the rooms loaded in the GameState's Dungeon.<br>
	 * 4. A line starting with "inventory:" followed by a list of items separated by ",". These are the items in the player's inventory. The names of the items listed here must match items in the GameState.<br>
	 * 5. A line starting with "weapon:" followed by the name of an item. The item must be an item in the GameState's items.   <br>
	 * 6. A line starting with "armor:" followed by the name of an armor. The armor must be an armor in the GameState's items.   <br>
	 * 7. A line starting with "shield:" followed by the name of a shield. The shield must be a shield in the GameState's items.   <br>
	 * 8. A line starting with "health:" followed by an int.<br>
	 * 9. A line starting with "score:" followed by an int.<br>
	 * 10. A line with "---" which is a delimiter used to mark the end of the player's entry.</blockquote><p>
	 * If any of these attributes do not have a value, then they will not be written to the file and will be skipped. 
	 * @param p is a .sav file that has been opened to write to.
	 * @throws IOException if there is an error writing to the file.
	 */
	void store(PrintWriter p) throws IOException {
		
		//print name of character followed by ":". Adventurer is is used as default name for single player
		p.println(this.getName() + ":");

		//print current room
		p.println("current room:" + this.getCurrentRoom().getTitle());

		//print inventory items separated by commas
		p.print("inventory:");
		for (int i=0; i<this.getInventory().size(); i++){
			p.print(this.getInventory().get(i).getPrimaryName());
			if (!(i+1==this.getInventory().size())){
				p.print (",");
			}
		}
		p.println();

		p.println("class:" + this.playerType.getTypeName());
		
		if (!(this.getWeapon()==null)){
			p.println("weapon:" + this.getWeapon().getPrimaryName());
		}
		
		if (!(this.getArmor()==null)){
			p.println("armor:" + this.getArmor().getPrimaryName());
		}
		
		if (!(this.getShield()==null)){
			p.println("shield:" + this.getShield().getPrimaryName());
		}	

		p.println("health:" + this.getHealth());
		p.println("score:" + this.getScore());
		p.println("---");

	}

}
