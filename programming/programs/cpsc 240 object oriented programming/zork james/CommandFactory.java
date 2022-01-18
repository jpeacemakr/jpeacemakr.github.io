/******************************************************************
 * CommandFactory.class is a singleton factory class.
 * The parse method accepts a string and returns a command from the Command.java class.
 *
 * @author: James Peacemaker
******************************************************************/

class CommandFactory {

	private static CommandFactory theInstance;
	
	//creates first and only instance of CommandFactory
	public static synchronized CommandFactory instance() {

		if (theInstance == null) {
			theInstance = new CommandFactory();
		}
		return theInstance;		
	}	

	//constructor
	private CommandFactory(){
	}


	//takes in a String, parses it, and returns a Command that Interpreter can understand 
	//so far, it only takes directional commands and q for quit. It also parses unknown commands as unknown.
	Command parse (String commandString){

		Command parsedCommand;	
		
		//Convert commandString to new Command
		if (commandString.equalsIgnoreCase("n")){
			parsedCommand = new Command("north");
		}
		else if (commandString.equalsIgnoreCase("s")){
			parsedCommand = new Command("south");
		}
		else if (commandString.equalsIgnoreCase("w")){
			parsedCommand = new Command("west");
		}
		else if (commandString.equalsIgnoreCase("e")){
			parsedCommand = new Command("east");
		}
		else if (commandString.equalsIgnoreCase("u")){
			parsedCommand = new Command("up");
		}	
		else if (commandString.equalsIgnoreCase("d")){
			parsedCommand = new Command("down");
		}
		else if (commandString.equalsIgnoreCase("q")){
			parsedCommand = new Command("quit");
		}
		else if (commandString.equalsIgnoreCase("load")){
			parsedCommand = new Command("load");
		}
		else if (commandString.equalsIgnoreCase("save")){
			parsedCommand = new Command("save");
		}		
		else {
			parsedCommand = new Command("unknown");
		}

		return parsedCommand;

	}


}
