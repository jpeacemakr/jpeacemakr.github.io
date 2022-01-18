
import java.util.Random;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * Room objects represent a contained area within a {@link Dungeon}. Each Room
 * can contain {@link Exit} objects, and {@link Item} objects. Characters can 
 * move from one room to another using the room's exits.  
 * @author Michael Goyer
 */
public class Room {

	class NoRoomException extends Exception {}

	private String title;
	private String desc;
	private boolean beenHere;
	private ArrayList<Exit> exits;
	private ArrayList<Item> contents;
	public static String CONTENTS_MARKER = "contents:";

	public Room(String title) {
		this.init();
		this.title = title;
	}


	/** Given a Scanner object positioned at the beginning of a "room" file
	  entry, read and return a Room object representing it. 
	  @throws NoRoomException The reader object is not positioned at the
	  start of a room entry. A side effect of this is the reader's cursor
	  is now positioned one line past where it was.
	  @throws IllegalDungeonFormatException A structural problem with the
	  dungeon file itself, detected when trying to read this room.
	  initState is true if loading file from scatch, using item locations of .zork file.
	  initState is false if loading from .sav file and using its locations of items.
	  */
	public Room(Scanner s, Dungeon d, boolean initState) throws NoRoomException, Dungeon.IllegalDungeonFormatException {

		this.init();
		this.title = s.nextLine();
		this.desc = "";
		if (this.title.equals(Dungeon.TOP_LEVEL_DELIM)) {
			throw new NoRoomException();
		}

		String lineOfDesc = s.nextLine();

		//if first line of description starts with "Contents:"
		if (lineOfDesc.startsWith(CONTENTS_MARKER)){
			//if initState is true then load contents, otherwise ignore
			if (initState == true){
				//remove "Contents: " from string and split contents lost into array of strings
				lineOfDesc = lineOfDesc.substring(CONTENTS_MARKER.length());

				String[] contentsSplit = lineOfDesc.split(",");
				for (int i=0; i<contentsSplit.length; i++){
					//get item from dungeon and add to the room
					this.add(d.getItem(contentsSplit[i]));
				}
			}
			lineOfDesc = s.nextLine();
		}
		//if room has no contents (no items)
		while (!lineOfDesc.equals(Dungeon.SECOND_LEVEL_DELIM) &&
			!lineOfDesc.equals(Dungeon.TOP_LEVEL_DELIM)) {
				this.desc += lineOfDesc + "\n";
				lineOfDesc = s.nextLine();
		}

		// throw away delimiter
		if (!lineOfDesc.equals(Dungeon.SECOND_LEVEL_DELIM)) {
			throw new Dungeon.IllegalDungeonFormatException("No '" +
					Dungeon.SECOND_LEVEL_DELIM + "' after room.");
		}
	}


	/**
	 * Adds the specified Item object to the Room's collection of Item objects, given that it
	 * has been instantiated.
	 * @param i Item to be added to the Room's collection of Items.
	 */
	void add(Item i){
		this.contents.add(i);	
	}



	/**
	 * Removes the specified Item from the Room's collection of Items, given that it is in the
	 * room's collection of items.
	 * @param i Item to be removed from the Room's collection of Items.
	 */
	void remove(Item i){
		this.contents.remove(i);	
	}



	/**
	 * Returns the Item of the passed name, given that it exists, and is
	 * in the Room's collection of Items. 
	 * @param name A string representing the name of the desired Item.
	 * @throws NoItemException if the passed string does not match the name of an Item in the Room.
	 */
	Item getItemNamed(String name) throws Item.NoItemException {
		
		for (int i=0; i<this.contents.size();i++){ 
			if (contents.get(i).getPrimaryName().equals(name)){		
				return contents.get(i);	
			}
		}
		//if item not found
		throw new Item.NoItemException("Item not found in room.");		

	}


	/**
	 * Returns an ArrayList containing all Items in the Room's collection of Items. 
	 */
	ArrayList<Item> getContents(){
		return this.contents;
	}


	// Common object initialization tasks.
	private void init() {
		this.exits = new ArrayList<Exit>();
		this.contents = new ArrayList<Item>();
		this.beenHere = false;
	}


	/**
	 * Returns a String containing the name of the Room.
	 */
	String getTitle() { return this.title; }


	/**
	 * Replaces the room's current description with the string passed.
	 * @param desc A string containing the new description of the room. 
	 */
	void setDesc(String desc) { this.desc = desc; }


	/**
	 * Resets the Room's beenHere boolean to false. The beenHere boolean represents 
	 * whether or not the user has interacted with a Room already.
	 */
	void resetBeenHere(){ //for LookCommand::execute()
		this.beenHere = false;	
	}


	boolean getBeenHere(){ //for LookCommand::execute()
		return this.beenHere;	
	}




	/**
	 * Writes the state of the room to a file using a PrintWriter. The state of 
	 * a Room includes the Items within it, and whether or not it has been visited 
	 * by the user already. 
	 * @param w The printwriter used to write the state to a .sav file.
	 * @throws IOException if a file writing error occurs.
	 */
	void storeState(PrintWriter w) throws IOException {

		w.println(title + ":");
		if (this.beenHere) {
			w.println("beenHere=true");
		} else {
			w.println("beenHere=false");
		}

		
		//if room has contents, print them
		if(!(this.contents.size()==0)){
			//print Contents: xxx,xxx,xxxx
			w.print(CONTENTS_MARKER);
			for (int i=0; i<this.contents.size();i++){
				w.print(this.contents.get(i).getPrimaryName());
				//print the comma except after the last word
				if (!(i+1==this.contents.size())){
					w.print (",");
				}
			}
			w.println();
		}
		w.println(Dungeon.SECOND_LEVEL_DELIM);
	}


	/**
	 * Returns a room to the state it was saved in. The state of the Room includes the Items 
	 * in the room's collection of items, and whether or not the user has visited it already.
	 * @param s The scanner used to read the .sav file.
	 * @param d The Dungeon in which the Room is contained.
	 * @param initState A boolean representing whether the state of the Room is hydrated from a .zork file (true) or a .sav file (false).
	 * @throws IllegalSaveFormatException if the .sav file is improperly formatted. 
	 */
	void restoreState(Scanner s, Dungeon d, boolean initState) throws GameState.IllegalSaveFormatException {
		
		String line = s.nextLine();
		if (!line.startsWith("beenHere")) {
			throw new GameState.IllegalSaveFormatException("No beenHere.");
		}
		beenHere = Boolean.valueOf(line.substring(line.indexOf("=")+1));

		String itemsList=s.nextLine();  
		//if next line is not the delimiter, go through list of items in the room
		if (!itemsList.equals("---")){
			
			//remove "Contents:" and split line into an array of strings
			String[] itemsSplitList = itemsList.substring(CONTENTS_MARKER.length()).split(",");
			//add each part of array as an item to the room
			for (int i=0; i<itemsSplitList.length; i++){
				this.add(d.getItem(itemsSplitList[i]));
			}
			s.nextLine();//get and discard delimiter

		} else {
			//end of room
		}	
	}


	/**
	 * Returns the name and description of the Room, as well as it's exits, characters 
	 * and items, if it has any. If the room has already been visited, returns only the 
	 * name, plus any exits, characters and items. 
	 */
	public String describe() {
		String description;

		//Give title and description if not visited before
		if (this.beenHere) {
			description = GameState.instance().getCurrentPlayer().getName()+ " is in " + this.title + "\n";
		} else {
			description = GameState.instance().getCurrentPlayer().getName()+ " is in " + this.title + "\n" + this.desc;
		}
		
		//List items in the room
		if (!(this.contents.size()==0)){
			for (Item item : this.contents) {
				description += "There is a " + item.getPrimaryName() + " here.\n"; 	
			}
		}

		//Add NPCs in room to description
		description += GameState.instance().getDescriptionOfNPCs(this);	


		//List exits for the room
		for (Exit exit : this.exits) {
			description += exit.describe() + "\n";
		}
		this.beenHere = true;
	
		return description;
	}


	/**
	 * Returns the Room directly connected to the current Room in the direction specified. Returns
	 * null if there is no exit in the specified direction.
	 * @param dir The direction of the desired Exit.
	 */
	public Room leaveBy(String dir) {
		for (Exit exit : exits) {
			if (exit.getDir().equals(dir)) {
				return exit.getDest();
			}
		}
		return null;
	}


	/**
	 * Adds an instantiated Exit object to the room's collection of Exit objects.
	 */
	void addExit(Exit exit) {
		exits.add(exit);
	}

	public Room getRandomConnectedRoom() {
		//returns the current room if there are no exits
		if(exits.get(0) == null){
			return this;
		}
		//returns a random connected room
		Random rand = new Random();
		int randNum = rand.nextInt(exits.size());
		Room r = this.exits.get(randNum).getDest();
		return r;

	}
}
