/**
  * An object of class SaveCommand represents an instance when the user types
  * "save" in the command prompt, and its purpose is to initiate GameState's
  * persistance of data to an exterior file.
  * @author JD
  */
class SaveCommand extends Command {
	
	private String filename;
	
	/**
	  * The constructor takes a String "save" OR "save filename" where save is
	  * an identifier in CommandFactory, no following information is a default
	  * case, and a given filename allows the user to name the .sav file.
	  */
	SaveCommand(String cmd){
		super(cmd);
		try{
			String[] cmdSplit = cmd.split(" ");
			this.filename = cmdSplit[1];
		}catch (ArrayIndexOutOfBoundsException e){
			this.filename = null;
		}
	}
	
	/**
	  * The execute method first checks if there is a given filename or if it
	  * is a default case. If it is a default case, it calls GameState's default
	  * store method, if there is a given filename, it passes the name as a parameter
	  * to GameState's store() method.
	  * @return a confirmation of a successful save or an error message and stack trace.
	  */
	String execute(){ 
		if(this.filename == null){ //default case, no filename given
			try {
           		GameState.instance().store();
            	return "Data saved to " + GameState.DEFAULT_SAVE_FILE +
                	GameState.SAVE_FILE_EXTENSION + ".\n";
        	} catch (Exception e) {
            	System.err.println("Couldn't save!");
            	e.printStackTrace();
            	return "";
        	}
		} else { //case user provides filename
			try {
           		GameState.instance().store(this.filename);
            	return "Data saved to " + this.filename +
                	GameState.SAVE_FILE_EXTENSION + ".\n";
        	} catch (Exception e) {
            	System.err.println("Couldn't save!");
            	e.printStackTrace();
            	return "";
        	}
		}
	}
}
