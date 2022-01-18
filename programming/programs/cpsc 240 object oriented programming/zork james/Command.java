/********************************************************************************************
 * Command class executes a command that is given to it in the form of a string. 
 * It is instantiated by CommandFactory.java.
 * Command method accepts a command string from CommandFactory and sets dir (direction).
 * execute method actually executes the command by modifying GameState. It return text describing
 * the ation taken and new room to be used by clent.
 *
 * @author: James Peacemaker 
 * ******************************************************************************************/

class Command {


	private String dir;//direction

	
	//constructor. takes in commandString and sets dir to be be used in execute method
	Command (String commandString){

		if (commandString.equals("north")){
			this.dir = "n";		
		}

		else if (commandString.equals("south")){
			this.dir = "s";		
		}

		else if (commandString.equals("east")){
			this.dir = "e";		
		}
		
		else if (commandString.equals("west")){
			this.dir = "w";		
		}
		
		else if (commandString.equals("up")){
			this.dir = "u";		
		}
		
		else if (commandString.equals("down")){
			this.dir = "d";		
		}
		
		else if (commandString.equals("quit")){
			this.dir = "quit";		
		}
		else if (commandString.equals("load")){
			this.dir = "load";		
		}
		else if (commandString.equals("save")){
			this.dir = "save";		
		}
		else{
			this.dir = "unknown";
		}		
	}




	//Executes a command. Returns message to user that action was taken. Returns a string
	String execute (){
		String executeMessage;
		//if command is to move
		if (dir.equals("n")||dir.equals("s")||dir.equals("w")||dir.equals("e")||dir.equals("u")||dir.equals("d")){
			//if exit does not exist
			if (GameState.instance().getAdventurersCurrentRoom().leaveBy(dir)==null){
				executeMessage="\nYou can't go that way!\n\n" + GameState.instance().getAdventurersCurrentRoom().describe();
			}
			//if exit does exist
			else {
				//create a string to that the user will see when action is taken. For now, return Room.describe.
				executeMessage = "\nMoving " + dir + " from " + GameState.instance().getAdventurersCurrentRoom().getTitle()+ 
				" to " + GameState.instance().getAdventurersCurrentRoom().leaveBy(dir).getTitle() + ".\n";
				//take the exit
				GameState.instance().setAdventurersCurrentRoom(GameState.instance().getAdventurersCurrentRoom().leaveBy(dir));
				//add description of the new room that you moved to.
				executeMessage = executeMessage + GameState.instance().getAdventurersCurrentRoom().describe();
			}
		}
		//if command is to load
		else if (dir.equals("load")){
			try {
				GameState.instance().restore("test.sav");
				executeMessage = "\nLoading saved game.\n" + GameState.instance().getAdventurersCurrentRoom().describe();
			}
			catch (Exception e){
				executeMessage = "\nCan't load file test.sav.\n";
			}
		}
		//if command is to save
		else if (dir.equals("save")){
			try {
				GameState.instance().store("save.sav");
				executeMessage = "\nSaving game.\n";
			} 
			catch (Exception e) {
				executeMessage = "\nError saving game.\n";
			}	
		}
		//if command is to quit
		else if (dir.equals("quit")){
			executeMessage = "\nThank you for playing.\n";
		}
		
		
		
		//if command is not known
		else{
			executeMessage = "\nThat command is not known. Please enter a direction (N,S,W,E,U,D) or Q for quit.\n";
		}

		return executeMessage;
	}
}
