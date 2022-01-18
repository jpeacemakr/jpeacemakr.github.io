
import java.util.Scanner;


/**
 * The Interpreter class is the main executable class for a Zork-like, text-based adventure game.<p>
 * The game is customizable so that a map maker can create their own dungeon with interconnected rooms, multiple players of different types, non-playable characters that can be friendly or hostile, and items that can be interacted with or used as weapons, armor or a shield.<p>
 * Each player can move from room to room and attack NPCs or interact with items. NPCs are given the option to move or even follow the players. Hostile NPCs will attack the player while friendly NPCs will attack hostile NPCs.<p>
 * The game ends when a game-winning event is triggered or when all of the players die.<p>
 * @author James Peacemaker
 */
public class Interpreter {

	private static GameState state; // not strictly necessary; GameState is singleton 

	public static String USAGE_MSG = 
		"Usage: Interpreter dungeonFile.zork|saveFile.sav.";




	/**
	 * This is the main method for the Interprter class, which is a Zork-like, text-based adventure game.<p>
	 * The game either opens a map file (.zork), which has been created by a map maker and includes all dungeon rooms, characters and items, or opens a saved game file (.sav), which stores the current state of all players, NPCs, rooms and items of a map file being played.<p>
	 * The user has the option to load a .zork or a .sav file using command line arguments when running the program to bypass the in-game prompts for loading a file.<p>
	 * <blockquote>Example: The command "java Interpreter dungeon.zork" will start the game with the dungeon.zork map file.</blockquote><p>
	 * When loading a .zork map file, the user will be prompted to choose the number of players and player types. Players in the new .zork map start off in the dungeon's entry room and have no items in their inventory.<p>
	 * If the user loads a .sav file, the number of players and player types have already been chosen. Players are restored to the room they were in at the time of saving and they will have of the same items equipped and in their inventory. NPCs will be in the same locations as when they saved.<p>
	 * @param args[] The command line argument that can either be a .zork file name or .sav file name.
	 */
	public static void main(String args[]) {

		if (args.length < 1) {
			System.err.println(USAGE_MSG);
			System.exit(1);
		}

		String command;
		Scanner commandLine = new Scanner(System.in);

		try {
			state = GameState.instance();

			//if a .zork file
			if (args[0].endsWith(".zork")) {
				state.initialize(new Dungeon(args[0], true));
				System.out.println("\nWelcome to " + state.getDungeon().getName() + "!");

				if (state.getMaxPlayers()==1){//single Player

					Player newPlayer = new Player("Adventurer",state.getDungeon().getEntry());
					state.addPlayer(newPlayer);

					//prompt for, find and assign player type	
					String playerTypeDescription = state.describePlayerTypes();
					if (!playerTypeDescription.equals("none")){
						while (true){
							System.out.print("Player options:\n" + playerTypeDescription + "Choose one of the above: ");
							String playerTypeChoice = commandLine.nextLine();
							try {
								state.getCurrentPlayer().setPlayerType(state.getPlayerTypeNamed(playerTypeChoice));
								break;
							}
							catch (Exception e) {
								System.out.println("\nPlayer type must match one of the following.");
							}
						}

					}

				}

				else {//multiplayer

					int numPlayers;
					
					//get number of players
					while (true) {
						try {

							System.out.print("How many players do you want to have? (" + state.getMinPlayers() + "-" + state.getMaxPlayers() + "): ");
							
							numPlayers = java.lang.Integer.parseInt(commandLine.nextLine());

							if (!(numPlayers <= state.getMaxPlayers() && numPlayers >=state.getMinPlayers())){
								throw new Exception();
							}
							break;
							

						} catch (Exception e) {
							System.out.print("Number of players must be within range. ");
						}
					}





					//create players and set them to dungeon entry room
					for (int i=0; i<numPlayers; i++) {
						

						//Check to see if name has already been used by an NPC or player
						boolean nameCopiedNPC = true;
						boolean nameCopiedPlayer = true;
						boolean firstTry = true;
						String playerName = "";

						while (nameCopiedNPC || nameCopiedPlayer){
							
							nameCopiedNPC = true;
							nameCopiedPlayer = true;
						
							if (firstTry == false) {
								System.out.print("\nName can't be the same as another player or NPC.");
							}

							System.out.print("\nEnter the name for Player " + (i+1) + ": ");
							playerName = commandLine.nextLine();
							playerName = playerName.replaceAll(" ","_"); 
								
							try
								{GameState.instance().getNPCNamed(playerName);}
							catch (Character.NoCharacterException g)
								{
								nameCopiedNPC = false;
								//System.out.println("NPC name not copied.");
								}
							
							try
								{GameState.instance().getPlayerNamed(playerName);}
							catch (Character.NoCharacterException h)
								{
								nameCopiedPlayer = false;
								//System.out.println("Player name not copied.");
								}	
								
							firstTry = false;

						}
						
						Player newPlayer = new Player(playerName,state.getDungeon().getEntry());
						state.addPlayer(newPlayer);
							

						//prompt for, find and assign player type	
						String playerTypeDescription = state.describePlayerTypes();
						if (!playerTypeDescription.equals("none")){
							while (true){
								System.out.print("Player options:\n" + playerTypeDescription + "Choose one of the above: ");
								String playerTypeChoice = commandLine.nextLine();
								try {
									state.getCurrentPlayer().setPlayerType(state.getPlayerTypeNamed(playerTypeChoice));
									break;
								}
								catch (Exception e) {
									System.out.println("\nPlayer type must match one of the following.");
								}

							}

						}


					}
				}
			}
			//if a .sav file
			else if(args[0].endsWith(".sav")){
				state.restore(args[0]);
				System.out.println("\nWelcome back to " + 
						state.getDungeon().getName() + "!");
			}

			//if unknown file type
			else {
				System.err.println(USAGE_MSG);
				System.exit(2);
			}

			state.nextPlayer(); // sets current player to first player added

			System.out.print("\n" + state.getCurrentPlayer().getCurrentRoom().describe());

			command = promptUser(commandLine);

			while (!command.equals("q")) {

				System.out.print(CommandFactory.instance().parse(command).execute());
				
				if(GameState.instance().getNumPlayers()==0){ //All players are dead -OR- all players have won
					System.out.println("\nGame over!\n");
					System.exit(1);
				}
				command = promptUser(commandLine);
			
			}

			System.out.println("\nBye!\n");

		} catch(Exception e) { 
			e.printStackTrace(); 
		}
	}

	private static String promptUser(Scanner commandLine) {
		System.out.print("\n" + GameState.instance().getCurrentPlayer().getName() +" > ");
		return commandLine.nextLine();
	}

}
