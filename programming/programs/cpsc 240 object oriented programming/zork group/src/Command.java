/**
  * A Command's purpose is to alter the state of the game
  * given a user's input. All Command objects are instantiated
  * in CommandFactory.
  * @author JD
  */
abstract class Command {

    private String cmd;
	
	/**
	  * This general case constructor simply saves the String it
	  * is passed in the parameter. The String is a user's input.
	  */
    Command(String cmd) {
        this.cmd = cmd;
    }
	
	/**
	  * All Command subtypes have an execute method. It's purpose is
	  * to alter the state of the game in some way and return a String
	  * containing feedback about what changed to the user.
	  */
    abstract String execute();
	
}
