
import java.util.List;
import java.util.Arrays;

/**
  * CommandFactory follows both the singleton and factory design patterns. It's
  * single object instantiates all Command objects.
  */
class CommandFactory {

    private static CommandFactory theInstance;
    public static List<String> MOVEMENT_COMMANDS = 
        Arrays.asList("n","w","e","s","u","d" );
	
	/**
	  * The purpose of the instance() method is to return an object of type CommandFactory,
	  * so other methods can be called on it from a non-static context.
	  * @return the method instantiates a new object if one does not yet exist, otherwise, it returns
	  * the same object.
	  */
    public static synchronized CommandFactory instance() {
        if (theInstance == null) {
            theInstance = new CommandFactory();
        }
        return theInstance;
    }

    private CommandFactory() {

    }

	/**
	  * The purpose of the parse() method is to instantiate the appropriate subtype of Command.
	  * @param command is any String that the user enters into the command prompt.
	  * @return the method returns an object of the appropriate subclass of Command.
	  */

    public Command parse(String command) {
        if (MOVEMENT_COMMANDS.contains(command)) {
            return new MovementCommand(command);
        } else if (command.startsWith("save")){
            return new SaveCommand(command);
		} else if (command.equalsIgnoreCase("look")){
			return new LookCommand(command);
		} else if (command.equalsIgnoreCase("i")){
			return new InventoryCommand(command);
		}else if (command.startsWith("take")){
			return new TakeCommand(command);
		}else if (command.startsWith("drop")){
			return new DropCommand(command);
		}else if (command.startsWith("attack")){
			return new AttackCommand(command);
		}else if (command.equalsIgnoreCase("score")){
			return new ScoreCommand(command);
		}else if (command.startsWith("equip")){
			return new EquipCommand(command);
		}else if (command.startsWith("unequip")){
			return new UnequipCommand(command);
		}else if (command.equalsIgnoreCase("health")){
			return new HealthCommand(command);
		}else if (command.startsWith("talk")){
			return new TalkCommand(command);
		}else if (command.startsWith("give")){
			return new GiveCommand(command);
		}else if (command.equalsIgnoreCase("help")){
				return new HelpCommand(command);
		}else{
			try{
				if(Item.VERBS.contains(command)){ //verb with no noun, split fails
					return new ItemSpecificCommand(command);
				}
				String[] cmdSplit = command.split(" ");
				if(Item.VERBS.contains(cmdSplit[0])){
					return new ItemSpecificCommand(command);
				}
				return new UnknownCommand(command);
			}catch(ArrayIndexOutOfBoundsException e){
			}
			return new UnknownCommand(command);
		}
    }
}
