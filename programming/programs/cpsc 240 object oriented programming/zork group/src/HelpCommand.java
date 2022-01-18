/**
  * An object of type HelpCommand represents an instance where the
  * user enters "help" into the command prompt.
  * @author JD
  */
class HelpCommand extends Command{
	
	private String cmd; //help

	/**
	  * The constructor is passed a String "help" which solely is
	  * an identifier in CommandFactory.
	  */
	HelpCommand(String cmd){
		super(cmd);
		this.cmd = cmd;
	}

	/**
	  * This method returns information to the user about what commands
	  * the CommandFactory parse() method supports and the correct format 
	  * in which those commands must be entered.
	  */
	String execute(){
		return "\n--HELP--\nA list of accepted commands follow:\nMovement - type the first letter of a direction (u,d,n,s,e,w) to exit a room.\nSave - type 'save' to save to a default file, or 'save filename' for any chosen\nfilename.\nLook - type 'look' if you need the room's description again.\nInventory - type 'i' to see the contents of your inventory.\nDrop - type 'drop itemName' to drop an item.\nTake - type 'take itemName' to take an item.\nGive - type 'give itemName to characterName' to give an item to a character.\nHealth - type 'health' to see, you guessed it, your health.\nScore - type 'score' to see your total points and rank.\nTalk - type 'talk to NPCName' to see what those idiots have to say.\nAttack - type 'attack characterName' to attack the character with whatever item\nyou have equipped.\nEquip - type 'equip itemName' to equip an item as your weapon, armor, or shield\n(this choice is made automatically).\nUnequip - type 'unequip itemName' to reset the respective slot to empty.\nLastly, items have many commands unique to them. Type whatever verb you can\nthink of and an itemName.\n";
	}
}
