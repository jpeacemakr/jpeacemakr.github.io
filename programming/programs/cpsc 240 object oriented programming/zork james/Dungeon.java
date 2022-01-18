/*****************************************************************************
 * Dungeon class is used to create the Dungeon which is a collection of rooms. 
 * Each dungeon has an entry room. Rooms are stored in a Hashtable.
 * Dungeon is used by GameState. 
 * @author: James Peacemaker
 ****************************************************************************/

import java.util.Hashtable;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.File;
import java.util.Enumeration;

public class Dungeon {

	private String name; //name of the Dungeon
	private Room entry; //Entry room, the first room the adventurer goes into 
	private String filename; // 
	private Hashtable<String, Room> rooms; //Hashtable of rooms	
	
	//constructor
	Dungeon (Room entry, String name){
		this.name = name;
		this.entry = entry;
		this.rooms = new Hashtable<String, Room>();
		this.rooms.put(entry.getTitle(), entry);
	}


	//constructor using text file as input
	public Dungeon (String filename) {
		this.init();
		this.filename = filename;
		try {
			//create scanner from file
			Scanner r = new Scanner(new File(filename));
	
			//get dungeon name from file
			this.name = r.nextLine();

			//read "Zork II" from file. If it does not match, throw error not correct version
			if (r.nextLine().equals("Zork II")) {
				System.out.println("Version is Zork II");
			} else {
				//throw exception
				System.out.println("Version of Zork is not compatible.");
			}

			//get next two lines and trash them  as they are a delimter and "Rooms:"
			r.nextLine();
			r.nextLine();

			//get entry room
			System.out.println("Getting entry room");	
			Room entryTemp = new Room(r);//read first room from file
			this.entry = entryTemp;//make this room the dungeon entry
			this.add(entryTemp);//add this room to the dungeon rooms

			//get more rooms and add them to the dungeon
			try { 
				while (true){
					this.add(new Room(r));
				}
			}
			catch (Exception e) {
			}


			r.nextLine();//grab and trash "Exits:" from file

			System.out.println("Getting exits");	
			//get exits and add them to the dungeon

			try { 
				while (true){
					new Exit (r, this);
				}
			}
			catch (Exception e) {
			}

			System.out.println("Closing file");
			r.close();
		} 
		
		catch (Exception e) {
	
		}
	}


	//getter for filename
	public String getFilename() {
		return this.filename;
	}



	//returns the entryRoom for a starting point in Dungeon
	public Room getEntry(){
		return this.entry;
	}


	//returns the name of the Dungeon
	public String getName(){
		return this.name;
	}


	//adds a room to the Dungeon. takes room you want to add as input.
	public void add (Room room){
		this.rooms.put(room.getTitle(), room);
	}


	//returns room with name of room as input and key in hashtable
	public Room getRoom (String roomTitle){
		return this.rooms.get(roomTitle);
	}


	private void init() {
		System.out.println("Running Dungeon.init");	
		
		this.entry = new Room(" ");
		this.rooms = new Hashtable<String, Room>();
		this.name = " ";
		this.filename = " ";
	}


	void restoreState (Scanner r) throws Exception {

		
		System.out.println("Running Dungeon.restoreState");	

			

		String tempTitle = r.nextLine();//get name of first room
		tempTitle = tempTitle.substring(0, tempTitle.length()-1);//truncate ":" from end
	
		while (!tempTitle.equals("===")) {
		
				this.getRoom(tempTitle).restoreState(r);//gets beenhere info and sets it 
				r.nextLine();//grab and discard "---"
				tempTitle = r.nextLine();//get next name of room.
				if (!tempTitle.equals("===")){
					//truncate ":" from end
					tempTitle = tempTitle.substring(0, tempTitle.length()-1);
					System.out.println(tempTitle);
				}
		}

		System.out.println("Getting current room");	
		//Get an next line and discard "Current Room:"
		tempTitle = r.nextLine();
		tempTitle = tempTitle.substring(14, tempTitle.length()); 
		System.out.println(tempTitle);
		//Assign Adventurer to room from file
		GameState.instance().setAdventurersCurrentRoom(this.getRoom(tempTitle));	

	}


	void storeState (PrintWriter w) {
		System.out.println("Running Dungeon.storeState");	
		
		Enumeration<String> roomNames = this.rooms.keys();

		while (roomNames.hasMoreElements()){
			String roomName = roomNames.nextElement();
			this.getRoom(roomName).storeState(w);
		}	

	}



}
