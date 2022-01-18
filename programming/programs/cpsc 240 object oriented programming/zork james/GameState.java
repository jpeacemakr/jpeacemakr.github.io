/***********************************************************************************
 * GameState is a singleton class. It represents the current state of the game. It stores the 
 * dungeon you are in and current room. When starting a dungeon, it puts you in the entry room.
 * @author: James Peacemaker
***********************************************************************************/

import java.util.Scanner;
import java.io.PrintWriter;
import java.io.File;


class GameState {

	private static GameState theInstance;
	private Dungeon adventurersCurrentDungeon; // stores current Dungeon being played
	private Room adventurersCurrentRoom; //stores adventurer's current room


	// used to create the one and only instance of GameState
	public static synchronized GameState instance(){
		if (theInstance == null) {
			theInstance = new GameState();
		}
		return theInstance;
	}


	//constructor
	private GameState(){
		adventurersCurrentRoom = new Room(" ");
		adventurersCurrentDungeon = new Dungeon(adventurersCurrentRoom, " ");
	}





	//retrieve game state from a .sav file
	void restore (String filename) throws Exception {
	
	System.out.println("Running Gamestate.restore");
		try {
			//open the file and create scanner to read from it
			Scanner gameStateFile = new Scanner(new File(filename));

			gameStateFile.nextLine(); //retrieve and disgard first line "Zork II save data"
			gameStateFile.nextLine(); //retrieve and disgard second line save file location
			gameStateFile.nextLine(); //retrieve and disgard third line "Room States:"
			
			//get and restore dungeon info from file	
			adventurersCurrentDungeon.restoreState(gameStateFile);
			
			//close the file
			System.out.println("Closing file");
			gameStateFile.close();
		} 
		
		catch (Exception e) {
			System.out.println("Gamestate.restore. Can't find .sav file.");
			throw new Exception();	
		}
	}



	//store game state to a file
	void store (String saveName) throws Exception {
		
		try {
			PrintWriter gameStateFile = new PrintWriter(new File(saveName));

			gameStateFile.println("Zork II save data"); 
			
			gameStateFile.println("Dungeon file: " + saveName);
			
			gameStateFile.println("Room states:"); 
			this.getDungeon().storeState(gameStateFile);

			gameStateFile.println("==="); 
			gameStateFile.println("Current room: " + this.getAdventurersCurrentRoom().getTitle()); 
			
			gameStateFile.close();
		}
		catch (Exception e){
			System.out.println("Gamestate.store. Can't create .sav file.");
			throw new Exception();	
		
		}




	}





	//set adventurer's dungeon and current room to dungeon's entry point
	public void initialize(Dungeon dungeon){
		this.adventurersCurrentRoom = dungeon.getEntry();
		this.adventurersCurrentDungeon = dungeon;



	}


	// returns adventurer's current room
	public Room getAdventurersCurrentRoom (){
		return this.adventurersCurrentRoom;
	}


	// sets adventurer's current room.
	public void setAdventurersCurrentRoom (Room room) {
		this.adventurersCurrentRoom = room;
	}

	// returns Dungeon that adventurer is in
	public Dungeon getDungeon(){
		return this.adventurersCurrentDungeon;
	}


}
