
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;


/**
 * A <tt>NonPlayableCharacter</tt> represents an NPC in a Zork-style, text-based game.<p> 
 * NPCs are controlled by the computer, not the players. They have multiple attributes: name, strength, endurance, dexterity, current health, maximum health, score, current room, hostility, whether they can follow a player, whether they can move, inventory, weapon, armor, shield and dialogue. <p>
 * Except for name and current room, NPCs are given default values when created using the NonPlayableCharacter constructor. Values can then be modified with methods of this class.
 * @author James Peacemaker
 */
class NonPlayableCharacter extends Character {

	int endurance; //health = score x endurance
	int strength; //damage = score x strength
	int dexterity; //speed = score x dexterity. speed effects chance to block and chance to hit/dodge
	boolean canMove;
	boolean canFollow;
	Player following;
	String dialogue;



	/**
	 * Constructs a new NPC with the name and room given.<p>
	 * Other attributes of the NPC should be assigned using the NonPlayableCharacter.restore method.<p>
	 * Default values for attributes: Dexterity, endurance and strength are 0. Hostility is -1.0. Current and maximum health are set to 10*endurance. Score (which represents the amount of score a player will get if they kill this NPC) is 10. NPCs are set to not move and not follow players.
	 * @param name The name of the NPC.
	 * @param r The current room of the NPC.
	 */
	NonPlayableCharacter(String name, Room r){
		super(name, r);
		this.inventory = new ArrayList<Item>();
		this.dexterity = 1;
		this.endurance = 1;
		this.strength = 1;
		this.hostility = -1.0;
		this.canFollow = false;
		this.canMove = false;
		this.setScore(1);
		this.setHealth(10*getEndurance());
		this.setMaxHealth(10*getEndurance());
	}





	/**
	 * Reads information from a .sav or .zork file that is used to set the NPC's information.<p>
	 * Information includes name, current room, hostility, whether they can follow a player, whether they can move, weapon, armor, shield, inventory, strength, endurance, dexterity, dialogue text, score, current health, and the name of the player they are following.<p>
	 * Information for the NPC must be in the following format:<p>
	 *<blockquote> 1. A line with the NPC's name.<br>
	 * 2. A line starting with "Current room:" followed by the name of the NPC's current room. The room name must match one of the rooms loaded in the GameState's Dungeon.<br>
	 * 3. A line starting with "hostility:" followed by the NPC's hostility number. A negative number means the NPC is hostile to players. A zero or positive number mean the NPC is friendly.<br>
	 * 4. A line starting with "canfollow:" followed by a 1 for true or 0 for false. The NPC will follow the player it encounters first if 1.<br>
	 * 5. A line starting with "canmove:" followed by a 1 for true or 0 for false. The NPC can move if true.<br>
	 * 6. A line starting with "weapon:" followed by the name of an item. The item must be an item in the GameState's items.   <br>
	 * 7. A line starting with "armor:" followed by the name of an armor. The armor must be an armor in the GameState's items.   <br>
	 * 8. A line starting with "shield:" followed by the name of a shield. The shield must be a shield in the GameState's items.   <br>
	 * 9. A line starting with "inventory:" followed by a list of items separated by ",". These are the items in the NPC's inventory. The names of the items listed here must match items in the GameState.<br>
	 * 10. A line starting with "stats:" followed by three ints separated by commas with no spaces. The first number is the NPC's dexterity. The second number is the NPC's endurance. The third number is the NPC's strength.	<br>
	 * 11. A line starting with "dialogue:" followed by a String that will be said by the NPC when the TalkCommand is used by a player.<br>
	 * 12. A line starting with "score:" followed by an int.<br>
	 * 13. A line starting with "health:" followed by an int. If field is empty, the current health is calculated using the NPC's endurance.<br>
	 * 14. A line starting with "following:" followed by a player's name. If the field is empty, then the NPC is not following a player. <br>
	 * 15. A line with "---" which is a delimiter used to mark the end of the NPC's entry.</blockquote>
	 * @throws NoCharacterException if the player information can't be hydrated or if the delimiter "===" is reached.
	 */

	NonPlayableCharacter(Scanner s, Dungeon d) throws Character.NoCharacterException {
		super(s);
		//set defaults. they will be overwritten below if lines are found when hydrating
		this.inventory = new ArrayList<Item>();
		this.dexterity = 1;
		this.endurance = 1;
		this.strength = 1;
		this.hostility = -1.0;
		this.canFollow = false;
		this.canMove = false;
		this.setScore(1);
		this.setHealth(10*getEndurance());
		this.setMaxHealth(10*getEndurance());


		try {

			//get "Name of NPC:" and throw error if not found
			String nameLine = s.nextLine();

			if (nameLine.equals("---")){
				nameLine = s.nextLine();
			}

			if (nameLine.equals("===")){
				throw new Character.NoCharacterException("Done hydrating NPCs");
			}

			nameLine = nameLine.substring(0, nameLine.length()-1);//remove ":" from the end of name
			this.setName(nameLine);

			String textLine = " ";

			//System.out.println("\nHydrating " + this.getName());

			//hydrate equipped items and player type if present	
			while (!textLine.equals("---")){
				try {

					textLine = s.nextLine();

					//System.out.println(textLine);

					//break line of text into stat name and value
					String[] textListSplit = textLine.split(":");

					//set current room
					if (textListSplit[0].equals("current room")) {
						//System.out.println(textListSplit[1]);
						//System.out.println(d.getRoom(textListSplit[1]).getTitle());
						this.setCurrentRoom(d.getRoom(textListSplit[1]));
					}

					//set inventory
					else if (textListSplit[0].equals("inventory")) {
				
						if (textListSplit.length > 1)
						{		
								String[] inventoryList = textListSplit[1].split(",");
						for (int i=0; i<inventoryList.length; i++){
							if (!inventoryList[i].equals("")){
								this.addToInventory(d.getItem(inventoryList[i]));
								//System.out.println("adding to inventory" + inventoryList[i] + "o");
							}
						}
					}

					}

					//set stats
					else if (textListSplit[0].equals("stats")) {
						String[] dexterityEnduranceStrength = textListSplit[1].split(",");
						this.dexterity = java.lang.Integer.valueOf(dexterityEnduranceStrength[0]);
						this.endurance = java.lang.Integer.valueOf(dexterityEnduranceStrength[1]);	
						this.strength = java.lang.Integer.valueOf(dexterityEnduranceStrength[2]);
					}

					//set weapon
					else if (textListSplit[0].equals("weapon")) {
						this.setWeapon(d.getItem(textListSplit[1]));
					}

					//set armor
					else if (textListSplit[0].equals("armor")) {
						this.setArmor(d.getItem(textListSplit[1]));
					}
					//set shield
					else if (textListSplit[0].equals("shield")) {
						this.setShield(d.getItem(textListSplit[1]));
					}

					//set health. if no health given then set health to max health (endurance*10)
					else if (textListSplit[0].equals("health")) {
						if (textListSplit.length == 1){
							this.setHealth(this.endurance*10);
						} else {
							this.setHealth(java.lang.Integer.valueOf(textListSplit[1]));
						}
					}

					//set score
					else if (textListSplit[0].equals("score")) {
						this.setScore(java.lang.Integer.valueOf(textListSplit[1]));
					}

					//set hostility
					else if (textListSplit[0].equals("hostility")) {
						this.setHostility(java.lang.Double.valueOf(textListSplit[1]));
					}

					//set dialogue
					else if (textListSplit[0].equals("dialogue")) {
						this.dialogue = textListSplit[1];
					}

					//set move/follow
					else if (textListSplit[0].equals("move/follow")) {

						String[] moveAndFollow = textListSplit[1].split(",");

						if (moveAndFollow[0].equals("1")){
							this.canMove = true;
						}
						if (moveAndFollow[1].equals("1")){
							this.canFollow = true;
						}

					}


				}
				catch (Exception e) { break; 
				} //break loop if nextline throws error (as in end of file)

			}
		}
		catch (Exception e){
			throw new Character.NoCharacterException("Done hydrating players");
		}
	}





	/**
	 * Stores information into a .sav or .zork file that is used to represent the NPC.<p>
	 * Information includes name, current room, hostility, whether they can follow a player, whether they can move, weapon, armor, shield, inventory, strength, endurance, dexterity, dialogue text, score, current health, and the name of the player they are following.<p>
	 * Information for the NPC must be in the following format:<p>
	 * <blockquote>1. A line with the NPC's name.<br>
	 * 2. A line starting with "Current room:" followed by the name of the NPC's current room. The room name must match one of the rooms loaded in the GameState's Dungeon.<br>
	 * 3. A line starting with "hostility:" followed by the NPC's hostility number. A negative number means the NPC is hostile to players. A zero or positive number mean the NPC is friendly.<br>
	 * 4. A line starting with "canfollow:" followed by a 1 for true or 0 for false. The NPC will follow the player it encounters first if 1.<br>
	 * 5. A line starting with "canmove:" followed by a 1 for true or 0 for false. The NPC can move if true.<br>
	 * 6. A line starting with "weapon:" followed by the name of an item. The item must be an item in the GameState's items.   <br>
	 * 7. A line starting with "armor:" followed by the name of an armor. The armor must be an armor in the GameState's items.   <br>
	 * 8. A line starting with "shield:" followed by the name of a shield. The shield must be a shield in the GameState's items.   <br>
	 * 9. A line starting with "inventory:" followed by a list of items separated by ",". These are the items in the NPC's inventory. The names of the items listed here must match items in the GameState.<br>
	 * 10. A line starting with "stats:" followed by three ints separated by commas with no spaces. The first number is the NPC's dexterity. The second number is the NPC's endurance. The third number is the NPC's strength.	<br>
	 * 11. A line starting with "dialogue:" followed by a String that will be said by the NPC when the TalkCommand is used by a player.<br>
	 * 12. A line starting with "score:" followed by an int.<br>
	 * 13. A line starting with "health:" followed by an int. If field is empty, the current health is calculated using the NPC's endurance.<br>
	 * 14. A line starting with "following:" followed by a player's name. If the field is empty, then the NPC is not following a player. <br>
	 * 15. A line with "---" which is a delimiter used to mark the end of the NPC's entry.</blockquote>
	 * @throws IOException If the NPC information can't be written to the file.
	 */
	void store(PrintWriter p) throws IOException {


		//print name of character followed by ":". 
		p.println(this.getName() + ":");
		//System.out.println(this.getName());

		//print move follow
		p.print("move/follow:");
		if (canMove) 
		{p.print("1");}
		else
		{p.print("0");}
		p.print(",");
		if (canFollow) 
		{p.print("1");}
		else
		{p.print("0");}
		p.println();

		//print current room
		p.println("current room:" + this.getCurrentRoom().getTitle());

		//print inventory items separated by commas
		p.print("inventory:");
		for (int i=0; i<this.getInventory().size(); i++){
			p.print(this.getInventory().get(i).getPrimaryName());
			//System.out.println(this.getInventory().get(i).getPrimaryName());
			if (!(i+1==this.getInventory().size())){
				p.print (",");
			}
		}
		p.println();

		//print equipped items
		if (!(this.getWeapon()==null)){
			p.println("weapon:" + this.getWeapon().getPrimaryName());
		}
		
		if (!(this.getArmor()==null)){
			p.println("armor:" + this.getArmor().getPrimaryName());
		}
		
		if (!(this.getShield()==null)){
			p.println("shield:" + this.getShield().getPrimaryName());
		}	

		//dialogue
		if (!(this.getDialogue()==null)){
			p.println("dialogue:" + this.getDialogue());
		}	

		////hostility
		p.println("hostility:" + this.getHostility());
		
		//stats
		p.println("stats:" + this.getDexterity() + "," + this.getEndurance() + "," + this.getStrength());

		p.println("health:" + this.getHealth());
		p.println("score:" + this.getScore());
		p.println("---");

	}



	/**
	 * Kills the NPC. <p>
	 * All equipped items and the NPC's inventory are dropped into the NPC's current room. Then the NPC is removed from the game.
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
		
		GameState.instance().getCurrentPlayer().setScore(GameState.instance().getCurrentPlayer().getScore() + this.getScore());
		
		GameState.instance().removeNPC(this);
		
	}





	/**
	 * Returns a string that describes the NPC.<p>
	 * The text gives the name, hostility, and current health of the NPC.<p>
	 * Examples: "There is a hostile cat with 99 health." or "There is a friendly dog with 34 health."	
	 * @return The description of the NPC.
	 */
	public String getDescription(){
		String hostilityString;
		if (this.hostility<0.0){
			hostilityString = "hostile";
		} else {
			hostilityString = "friendly";
		}
		return "There is a " + hostilityString + " " + this.getName() + " with " + this.getHealth() + " health."; 
	}




	/**
	 * Has an NPC take one turn that varies depending on circumstances.<p>
	 * Each turn consists of either an attack or a movement from one room to another. <p>
	 * If no player is in the same room, NPCs that can move will move to a random adjacent room.<p>
	 * If NPCs can move and can follow players, they will follow the first player they encounter until one of them is dead.<p>
	 * If a player is in the same room, hostile NPCs will attack the NPC. Friendly NPCs will attack hostile NPCs.<p>
	 * If they can't move and have no one to attack, the NPC will take no action but it will count as a turn.
	 */
	public void takeTurn(){

	}




	/**
	 * Returns the dexterity for this NPC.
	 * Dexterity is used to calculate if attacks hit or miss and chance to block with a shield.
	 * @return The NPC's dexterity.
	 */
	public int getDexterity(){
		return this.dexterity;
	}




	/**
	 * Returns the endurance for this NPC.
	 * Endurance is used to calculate the NPC's maximum health.
	 * @return The NPC's endurance.
	 */
	public int getEndurance(){
		return this.endurance;
	}



	/**
	 * Returns the Strength for this NPC.
	 * Strength is used to calculate the damage by the NPC.
	 * @return The NPC's strength.
	 */
	public int getStrength(){
		return this.strength;
	}




	/**
	 * Returns the dialogue given by the NPC.
	 * Dialogue is given when a {@link Player} uses a {@link TalkCommand}.
	 * @return The NPC's dialogue.
	 */
	public String getDialogue(){
		return this.dialogue;
	}

	public boolean canMove(){
		return this.canMove;
	}

	public boolean canFollow(){
		return this.canFollow;
	}

	public void setFollowing(Player p){
		this.following = p;
	}
	public Player isFollowing(){
		return this.following;
	}	
	
		
		
	

}
