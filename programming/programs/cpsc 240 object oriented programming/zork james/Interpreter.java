/*****************************************************************
 * This is the main class for a game similar to Zork. So far, the program
 * just moves from room to room. The uder enters a direction to move.
 * It requires six other classes to run: CommandFactor.java, Command.java, 
 * Dungeon.java, Room.java, Exit.java and GameState.java. 
 * @author: James Peacemaker
 *****************************************************************/

import java.util.Scanner;
import java.io.File;
import java.io.PrintWriter;

class Interpreter{


	public static void main(String args[]) {
		
		//load file from command line argument. throw error if file not found
		/*		
		if (args.[0].equals(something.zork)){
			//load zork file

		} else if (args.[0].equals(something.sav)) {
			//load saved file

		}
		*/

		//build the dungeon and initialize game state
		Dungeon dungeonOne = new Dungeon("test.zork");
		GameState state = GameState.instance();	
		state.initialize(dungeonOne);

		//initialize the CommandFactory
		CommandFactory parser = CommandFactory.instance();
		System.out.println(" ");
		System.out.println(" ");
		System.out.println("Welcome to the Dungeon: " + dungeonOne.getName());	
		System.out.println(" ");
		
		Scanner text = new Scanner(System.in);
		String command = " ";
	
		//give description of room you are starting in and its exits
		System.out.println(GameState.instance().getAdventurersCurrentRoom().describe());
		
		//while command is not q (for quit). Valid commands are directions N,S,E,W,U,D.
		while (!command.equalsIgnoreCase("q")){
			
			System.out.print(">");
			command = text.nextLine();

			//Executes pasrse command and prints its output
			System.out.println(parser.parse(command).execute());

		}	
	}	


	/*
	private static Dungeon buildSampleDungeon() {

		//create rooms
		Room frontPorch = new Room("The Front Porch");
		frontPorch.setDesc("You stand on the porch of a brick, two-story home that was built around 1900. The porch railing and columns need to be painted, and a bird has made a nest in the transom. ");

		Room frontHallway = new Room("The Front Hallway");
		frontHallway.setDesc("You enter a long hallway with tan plaster walls and heart-of-pine wood floors. Numerous photos hand from a picture rail that runs the length of the hallway.");
	
		Room backHallway = new Room("The Back Hallway");
		backHallway.setDesc("The back hallway has a large staircase leading upstairs. A large coat rack and sitting area is along the back wall.");

		Room diningRoom = new Room("The Dining Room");
		diningRoom.setDesc("What should be an area for eating is now being used as a makeshift workshop as the home is being renovated. Sawdust covers the floor and numerous power tools are in cabinets.");
		
		Room livingRoom = new Room("The Living Room");
		livingRoom.setDesc("A large fireplace is flanked by large figures of Batman and Darth Vader. A worn leather couch sits in front of a large television. Kids toys are scattered throughout the room.");

		Room kitchen = new Room("The Kitchen");
		kitchen.setDesc("A gas stove sits against one side of the room. A small table is in the center. Two dogs keep going in and out of the dog door into the back yard.");
		
		Room backPorch = new Room("The Back Porch");
		backPorch.setDesc("The recently painted porch looks out on to the fenced back yard.");
		
		Room upstairsHallway = new Room("The Upstairs Hallway");
		upstairsHallway.setDesc("The hall is lined with storage boxes containing items from another room that is being renovated.");
				
		Room kidsBedroom = new Room("The Kids' Bedroom");
		kidsBedroom.setDesc("This room is bright blue and has numerous shelves filled to the ceiling with toys and books. A bunk bed sits in one corner.");
		
		Room parentsBedroom = new Room("The Parents' Bedroom");
		parentsBedroom.setDesc("This room was recently renovated. It has a large fireplace with a wooden sunburst pattern and a brass dragon fire screen. A bed is against one wall.");
		
		Room office = new Room("The Office");
		office.setDesc("This room is covered in wallpaper scrapings and plaster dust from an ongoing renovation.");
		
		Room bathroom = new Room("The Bathroom");
		bathroom.setDesc("This room has bright green walls and white wainscoting.");


		//add exits to rooms
		//(direction, source, destination)
		
		frontPorch.addExit(new Exit("west",frontPorch,frontHallway));

		frontHallway.addExit(new Exit("east",frontHallway,frontPorch));
		frontHallway.addExit(new Exit("south",frontHallway,diningRoom));
		frontHallway.addExit(new Exit("west",frontHallway,backHallway));
	
		backHallway.addExit(new Exit("east",backHallway,frontHallway));
		backHallway.addExit(new Exit("west",backHallway,kitchen));
		backHallway.addExit(new Exit("south",backHallway,livingRoom));
		backHallway.addExit(new Exit("up",backHallway,upstairsHallway));
		
		diningRoom.addExit(new Exit("north",diningRoom,frontHallway));
		diningRoom.addExit(new Exit("west",diningRoom,livingRoom));
		
		livingRoom.addExit(new Exit("north",livingRoom,backHallway));
		livingRoom.addExit(new Exit("east",livingRoom,diningRoom));
		
		kitchen.addExit(new Exit("west",kitchen,backPorch));
		kitchen.addExit(new Exit("east",kitchen,backHallway));

		backPorch.addExit(new Exit("east",backPorch,kitchen));
		
		upstairsHallway.addExit(new Exit("down",upstairsHallway,backHallway));
		upstairsHallway.addExit(new Exit("west",upstairsHallway,kidsBedroom));
		upstairsHallway.addExit(new Exit("south",upstairsHallway,parentsBedroom));
		upstairsHallway.addExit(new Exit("north",upstairsHallway,bathroom));
		upstairsHallway.addExit(new Exit("east",upstairsHallway,office));
		
		kidsBedroom.addExit(new Exit("east",kidsBedroom,upstairsHallway));

		parentsBedroom.addExit(new Exit("north",parentsBedroom,upstairsHallway));

		office.addExit(new Exit("west",office,upstairsHallway));

		bathroom.addExit(new Exit("south",bathroom,upstairsHallway));


		//create the dungeon with the entry room starting point added
		Dungeon nightmareOn32nd = new Dungeon(frontPorch, "Nightmare on 32nd Street"); 	
		
		//add remaining rooms to the dungeon
		nightmareOn32nd.add(frontHallway);
		nightmareOn32nd.add(backHallway);
		nightmareOn32nd.add(diningRoom);
		nightmareOn32nd.add(livingRoom);
		nightmareOn32nd.add(kitchen);
		nightmareOn32nd.add(backPorch);
		nightmareOn32nd.add(upstairsHallway);
		nightmareOn32nd.add(kidsBedroom);
		nightmareOn32nd.add(parentsBedroom);
		nightmareOn32nd.add(bathroom);
		nightmareOn32nd.add(office);
	
		return nightmareOn32nd;

	}
	*/

}
