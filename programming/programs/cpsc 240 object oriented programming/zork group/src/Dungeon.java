import java.util.Random;
import java.util.Hashtable;
import java.util.Scanner;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Iterator;

/**
 * A Dungeon represents a group of interconnected Rooms. Each Dungeon 
 * object contains a number of {@link Room} objects, which may or may not
 * be connected by {@link Exit} objects, and may or may not contain {@link Item} 
 * objects. Dungeons can be navigated by the user, as they move through rooms, 
 * collect Items, and Interact with nonPlayerCharacters as well as other Players.
 *
 * @author Michael Goyer   
 */

public class Dungeon {

	public static class IllegalDungeonFormatException extends Exception {
		public IllegalDungeonFormatException(String e) {
			super(e);
		}
	}

	// Variables relating to both dungeon file and game state storage.
	public static String TOP_LEVEL_DELIM = "===";
	public static String SECOND_LEVEL_DELIM = "---";

	// Variables relating to dungeon file (.zork) storage.
	public static String ROOMS_MARKER = "Rooms:";
	public static String EXITS_MARKER = "Exits:";
	public static String ITEMS_MARKER = "Items:";

	// Variables relating to game state (.sav) storage.
	static String FILENAME_LEADER = "Dungeon file: ";
	static String ROOM_STATES_MARKER = "Room states:";

	private String name;
	private Room entry;
	private Hashtable<String,Room> rooms;
	private Hashtable<String,Item> items;
	private String filename;


	/**
	 * Constructor for non-hydrated Dungeons.  
	 * @param name A string representing the Dungeon's name. 
	 * @param entry The first Room in the Dungeon that the user interacts with.
	 */
	Dungeon(String name, Room entry) {
		init();
		this.filename = null;    // null indicates not hydrated from file.
		this.name = name;
		this.entry = entry;
		rooms = new Hashtable<String,Room>();
	}


	/**
	 * Constructs a new Dungeon object using the information in the file of the passed name. .sav 
	 * or .zork files can be used, depending on whether the user wants to continue a previous 
	 * saved game, or start a new one. 
	 * @param filename A string matching the name of the .zork file used to create the dungeon.
	 * @param initState A boolean used to indicate the type of file is being hydrated from, true if from scratch (a .zork file) and false if from a previous save (a .sav file). 
	 * @throws FileNotFoundException if there is no file with the name of the passed string. 
	 */   
	public Dungeon(String filename, boolean initState) throws FileNotFoundException,
	       IllegalDungeonFormatException {

		       init();
		       this.filename = filename;

		       Scanner s = new Scanner(new FileReader(filename));
		       name = s.nextLine();

		       s.nextLine();   // Throw away version indicator.


		       //hydrate min and max players and player types if present
			String textLine = s.nextLine();
			
			if (!textLine.equals(TOP_LEVEL_DELIM)){// ===
				
				//set minimum and maximum players. 
				//GameState has default of 1 for min and max players 
				//if this part of .zork file is not found
				String[] minMaxSplit = textLine.split(",");
				GameState.instance().setMinPlayers(java.lang.Integer.parseInt(minMaxSplit[0]));
				GameState.instance().setMaxPlayers(java.lang.Integer.parseInt(minMaxSplit[1]));

				//hydrate PlayerTypes until === reached
				//player assigned default PlayerType if this part of file not found
				try {
					// Instantiate and add player types.
					while (true) {
						GameState.instance().addPlayerType(new PlayerType(s));
					}
				} catch (PlayerType.NoPlayerTypeException e) {  /* end of player types */ }
			}



			//hydrate items
		       // Throw away Items starter.
		       if (!s.nextLine().equals(ITEMS_MARKER)) {
			       throw new IllegalDungeonFormatException("No '" +
					       ITEMS_MARKER + "' line where expected.");
		       }

		       try {
			       // Instantiate and add items.
			       while (true) {
				       add(new Item(s));
			       }
		       } catch (Item.NoItemException e) {  /* end of items */ }




			//hydrate items
		       // Throw away Items starter.
		       if (!s.nextLine().equals("Shields:")) {
			       throw new IllegalDungeonFormatException("No Shields: line where expected.");
		       }

		       try {
			       // Instantiate and add items.
			       while (true) {
				       add(new Shield(s));
			       }
		       } catch (Item.NoItemException e) {  /* end of items */ }



			//hydrate items
		       // Throw away Items starter.
		       if (!s.nextLine().equals("Armor:")) {
			       throw new IllegalDungeonFormatException("No Armor: line where expected.");
		       }

		       try {
			       // Instantiate and add items.
			       while (true) {
				       add(new Armor(s));
			       }
		       } catch (Item.NoItemException e) {  /* end of items */ }




		       // Throw away Rooms starter.
		       if (!s.nextLine().equals(ROOMS_MARKER)) {
			       throw new IllegalDungeonFormatException("No '" +
					       ROOMS_MARKER + "' line where expected.");
		       }

		       try {
			       // Instantiate and add first room (the entry).
			       entry = new Room(s, this, initState);
			       add(entry);

			       // Instantiate and add other rooms.
			       while (true) {
				       add(new Room(s, this, initState));
			       }
		       } catch (Room.NoRoomException e) {  /* end of rooms */ }


		       //Get Exits from file
		       // Throw away Exits starter.
		       if (!s.nextLine().equals(EXITS_MARKER)) {
			       throw new IllegalDungeonFormatException("No '" +
					       EXITS_MARKER + "' line where expected.");
		       }

		       try {
			       // Instantiate exits.
			       while (true) {
				       // (Note that the Exit constructor takes care of adding itself
				       // to its source room.)
				       Exit exit = new Exit(s, this);
			       }
		       } catch (Exit.NoExitException e) {  /* end of exits */ }


			//hydrate NPCs
 		       if (!s.nextLine().equals("NPCs:")) {
			       throw new IllegalDungeonFormatException("No NPCs marker line where expected.");
		       }

		       try {
			     // Instantiate and add NPCs.
			     while (true) {
				     GameState.instance().addNPC(new NonPlayableCharacter(s, this));
			     }
		     } catch (Character.NoCharacterException e) {  /* end of players*/ }


		       s.close();
	}




	/**
	 * Adds an instantiated Item object to the Dungeon's collection of Items. 
	 * Items within a Dungeon's collection of items are  referrable by name. 
	 * @param i The name of the Item, used to refer to that specific Item.
	 */
	public void add (Item i){
		this.items.put(i.getPrimaryName(), i);
	}


	/**
	 * Returns an Item object, given that the passed string matches the name of
	 * an Item within the Dungeon's collection of Items. 
	 * @param itemName A string representing an Item in the Dungeon's collection of Items.
	 */
	public Item getItem(String itemName){
		return this.items.get(itemName);
	}



	// Common object initialization tasks, regardless of which constructor
	// is used.
	private void init() {
		rooms = new Hashtable<String,Room>();
		items = new Hashtable<String,Item>();
	}



	/**
	 * Stores the current state of the Dungeon to the PrintWriter passed. The state
	 * of the Dungeon includes which rooms have and have not been visited, as well 
	 * as what Items are located in which rooms. The PrintWriter is then used to write
	 * the state of the game to a file. 
	 * @param w A PrintWriter used to write to a file. 
	 */
	void storeState(PrintWriter w) throws IOException {

		w.println(FILENAME_LEADER + getFilename());
		w.println(ROOM_STATES_MARKER);
		for (Room room : rooms.values()) {
			room.storeState(w);
		}
		w.println(TOP_LEVEL_DELIM);


	}

	/**
	 * Uses a scanner to restore the instantiated Dungeon to the state in which it was written to a .sav file. 
	 * The state of the Dungeon includes which rooms have and have not been visited, as well as 
	 * what Items are located in which rooms. Restoring the state will recreate the entire dungeon, 
	 * and return it to the state it was saved in.
	 * @param s A scanner used to read the appropriate .sav file. 
	 * @param initState A boolean representing whether the state of the Dungeon is hydrated from a .zork file (true), or a .sav file (false).
	 * @throws IllegalSaveFormatException if the .sav file is incorrectly formatted.
	 */
	void restoreState(Scanner s, boolean initState) throws GameState.IllegalSaveFormatException {

		// Note: the filename has already been read at this point.
		if (!s.nextLine().equals(ROOM_STATES_MARKER)) {
			throw new GameState.IllegalSaveFormatException("No '" +
					ROOM_STATES_MARKER + "' after dungeon filename in save file.");
		}

		String roomName = s.nextLine();
		while (!roomName.equals(TOP_LEVEL_DELIM)) {
			getRoom(roomName.substring(0,roomName.length()-1)).restoreState(s, this, initState);
			roomName = s.nextLine();
		}

	}
	/**
	  * This method returns a random room in the dungeon, and if that random room
	  * is the same as the current Player's current room, it recurses.
	  */
	public Room getRandomRoom(){ //for teleport, uses recursion to make it different to Player's current room
		Random rand = new Random();
		int r = rand.nextInt(rooms.size());
		Iterator<Room> iter = rooms.values().iterator();
		Room randomRoom = null;
		for(int i = 0; i<=r; i++){
			randomRoom = iter.next();
		}
		if(GameState.instance().getCurrentPlayer().getCurrentRoom().equals(randomRoom)){
			randomRoom = this.getRandomRoom();
		}
		return randomRoom;
	}

	/**
	 * Returns the dungeon's entry room. The entry room of a Dungeon is the first room that the 
	 * user interacts with, and is where they begin their traversal of the Dungeon. 
	 */
	public Room getEntry() { return entry; }
	
	/**
	 * Returns a String containing the Dungeon's name. 
	 */
	public String getName() { return name; }
	
	/**
	 * Returns a String containing the name of the .zork file from which the Dungeon was hydrated.
	 */
	public String getFilename() { return filename; }
	
	/**
	 * Adds a room to the Dungeon's collection of rooms, given that the room has been instantiated.  
	 */
	public void add(Room room) { rooms.put(room.getTitle(),room); }
	
	/**
	 * Returns the room with a name that matches the passed string, given that the Dungeon's collection 
	 * of rooms contains a room of that name. 
	 * @param roomTitle A string representing the name of a Room in the Dungeon's collection of rooms.
	 */
	public Room getRoom(String roomTitle) {
		return rooms.get(roomTitle);
	}
}
