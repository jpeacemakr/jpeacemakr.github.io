

/**
  * An object of TalkCommand represents an instance where the user
  * enters "talk to" or "talk to NPCName" in the command prompt.
  * @author JD
  */
class TalkCommand extends Command {
	
	private String cmd;
	private String NPCName;

	/**
	  * The constructor is passed a String that starts with "talk to" as
	  * an identifier in CommandFactory. If it is followed by the name of
	  * a NonPlayableCharacter, it is saved. If no name is given, it is
	  * handled appropriately in execute.
	  */
	TalkCommand(String cmd){
		super(cmd);
		try{
			String[] cmdSplit = cmd.split(" "); 
			this.cmd = cmdSplit[0];
			this.NPCName = cmdSplit[2];
		} catch (ArrayIndexOutOfBoundsException e){
			this.NPCName = null;
		}
	}
	
	/**
	  * This method returns the dialogue of the NonPlayableCharacter
	  * object with the given name, appropriately changes their hostility,
	  * and increments the turn.
	  */
	String execute(){
		if(this.NPCName == null){
			return "Talk to whom?"; //If whom isn't right I do not care
		}
		
		Room currentRoom = GameState.instance().getCurrentPlayer().getCurrentRoom();
		try{
			NonPlayableCharacter npc = GameState.instance().getNPCNamed(NPCName);
			if(!npc.getCurrentRoom().equals(currentRoom)){
				return NPCName + " isn't here.\n";
			}else{
				return npc.getDialogue() + "\n";
			}
		} catch(Character.NoCharacterException e){
			return "I don't know who " + NPCName + " is.\n";
		}
	}
}
