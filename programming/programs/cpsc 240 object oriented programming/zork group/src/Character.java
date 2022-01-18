import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;


/**
 * A <tt>Character</tt> represents a person, creature or other thing that has the ability to attack or move.<p>
 * Each character can have a shield, armor or weapon equipped. Each character has a name, score, current room, an inventory that drops when it dies, and a current health and max health. When health reaches 0 or below, the character is dead.
 * @author James Peacemaker
 */
class Character {

	private String name;
	private Item equippedArmor;
	private Item equippedWeapon;
	private Item equippedShield;
	private int score;
	protected Room currentRoom;
	protected ArrayList<Item> inventory; //ArrayList of Items held by the Adventurer
	private int maxHealth;
	private int currentHealth;
	private Player following;
	protected double hostility;
	private boolean hasJustTeleported;

	/**
	 * This exception is thrown when a Character can't be found or when a Character can't be hydrated from a file.
	 */
	public static class NoCharacterException extends Exception {
		/**
		 * Signals that there was an error hydrating a character's information or that the character could not be found.
		 * @param e The detail message.
		 */	
		public NoCharacterException(String e) {
			super(e);
		}
	}




	/**
	 * Constructs a new character object with the given name and room.
	 * @param name The name of the character being created.
	 * @param r The current room of the character being created.
	 */
	Character(String name, Room r){
		this.inventory = new ArrayList<Item>();
		this.name = name;
		this.currentRoom = r;
		this.maxHealth = 20; //PLACEHOLDERS TO TEST HEALTHCOMMAND
		this.currentHealth = 20; //^what he said
		this.hostility = 0;
	}


	//Constructor used to hydrate from scanner
	Character(Scanner s) throws Character.NoCharacterException {
		this.inventory = new ArrayList<Item>();
	}



	/**
	 * Adds an {@link Item} to the character's inventory.
	 * @param i An {@link Item} to be added to the character's inventory.
	 */
	void addToInventory (Item i){
		this.inventory.add(i);	
	}	




	/**
	 * Removes an {@link Item} from a character's inventory.<p>
	 * The method compares the name of the item to be removed with all aliases of items in the character's inventory to find the item to be removed. If the item is not found, the method does nothing.
	 * @param i An item that will be removed from a character's inventory.
	 */
	void removeFromInventory(Item i) {

		if(this.inventory.contains(i)){ //if there is a duplicate, that means it was just dropped
			this.inventory.remove(i); //and must be removed
		}

	}




	/**
	 * Returns an {@link Item} in the character's inventory when given the name (or alias) of the item.
	 * @param name The name of the item being searched for in the character's inventory.
	 * @return The item if it is found in the character's inventory
	 * @throws Item.NoItemException If the item can't be found in the character's inventory.
	 */
	Item getItemFromInventoryNamed(String name) throws Item.NoItemException {
		for (Item itemCheck : this.inventory){ //loops through all items in the current room
			if (name.equalsIgnoreCase(itemCheck.getPrimaryName())){
				return itemCheck; //if the command matches a primary name in the room, updates itemTake
			} else if (itemCheck.goesBy(name)){
				return itemCheck; //if the command matches an alias in the room, updates itemTake 
			}
		}
		throw new Item.NoItemException("No item found.");
	}




	/**
	 * Returns the inventory of the character.
	 * @return An ArrayList of items in the inventory
	 */
	ArrayList<Item> getInventory(){
		return this.inventory;
	}




	/**
	 * Returns the current room that the character is in.
	 * @return The current room that the character is in.
	 */
	Room getCurrentRoom() {
		return this.currentRoom;
	}



	/**
	 * Sets the character's current {@link Room}.
	 * @param room The room that will be set to the character's current room.
	 */
	void setCurrentRoom(Room room) {
		this.currentRoom = room;
	}




	/**
	 * Returns the character's name.
	 * @return The character's name.
	 */
	public String getName(){
		return this.name;
	}





	/**
	 * Sets the character's name.
	 * @param newName The String that will become the character's name
	 */
	public void setName(String newName){
		this.name = newName;
	}




	/**
	 * Returns the character's current health.
	 * @return The character's current health.
	 */
	public int getHealth(){
		return this.currentHealth;
	}




	/**
	 * Sets the character's current health.
	 * @param health The character's new health
	 */
	public void setHealth(int health){
		this.currentHealth = health;
	}




	/**
	 * Returns the character's maximum health.
	 * @return The character's maximum health.
	 */
	public int getMaxHealth(){
		return this.maxHealth;
	}



	/**
	 * Sets the character's maximum health.
	 * @param maxHealth The character's new maximum health.
	 */
	public void setMaxHealth(int maxHealth){
		this.maxHealth = maxHealth;
	}




	/**
	 * Sets the character's score.
	 * @param newScore The character's new score.
	 */	
	public void setScore(int newScore){
		this.score = newScore;
	}




	/**
	 * Returns the character's score.
	 * @return The character's score.
	 */	
	public int getScore(){
		return this.score;
	}




	/**
	 * Sets the character's armor.
	 * @param newArmor The character's new armor.
	 */	
	public void setArmor(Item newArmor) {
		this.equippedArmor = newArmor;
	}




	/**
	 * Returns the character's armor.
	 * @return The character's armor.
	 */	
	public Item getArmor() {
		return this.equippedArmor;
	}




	/**
	 * Sets the character's shield.
	 * @param newShield The character's new shield.
	 */	
	public void setShield(Item newShield) {
		this.equippedShield = newShield;
	}




	/**
	 * Returns the character's shield.
	 * @return The character's shield.
	 */	
	public Item getShield() {
		return this.equippedShield;
	}


	/**
	 * Sets the character's weapon.
	 * @param newWeapon The character's new weapon.
	 */	
	public void setWeapon(Item newWeapon) {
		this.equippedWeapon = newWeapon;
	}




	/**
	 * Returns the character's weapon.
	 * @return The character's weapon.
	 */	
	public Item getWeapon() {
		return this.equippedWeapon;
	}



	public void die() {
		//will be overwritten by NonPlayableCharacter or Player class method die()
	}


	//will be overwritten by NPC or Player method of same name
	public int getDexterity() {
		return 1;
	}


	//will be overwritten by NPC or Player method of same name
	public int getStrength() {
		return 1;
	}


	//will be overwritten by NPC or Player method of same name
	public int getEndurance() {
		return 1;
	}


	public void setHostility(double h){
		this.hostility = h;
	}


	public double getHostility(){
		return this.hostility;
	}


	public void setFollowing(Player p){
		this.following = p;
	}

	public Player isFollowing(){
		return this.following;
	}
	
	public void setJustTeleported(boolean b){
		this.hasJustTeleported = b;
	}

	public boolean getJustTeleported(){
		return this.hasJustTeleported;
	}	
}

