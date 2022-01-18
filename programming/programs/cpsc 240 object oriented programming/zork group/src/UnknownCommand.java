/**
  * An object of UnknownCommand represents an instance where the user
  * enters an unrecognizable or non-supported command in the command
  * prompt.
  * @author JD
  */
class UnknownCommand extends Command {
	
	private String cmd;
	
	/**
	  * The constructor is passed any String that was not an identifier
	  * for any of the supported commands.
	  */
	UnknownCommand(String cmd){
		super(cmd);
		this.cmd = cmd;
	}
	
	/**
	  * This method returns feedback to the user that whatever he/she
	  * entered is not understood by the program.
	  */
	String execute(){
		return "I don't know what \"" + this.cmd + "\" means.\n";
	}
}
