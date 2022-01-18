
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;

/**
 * The <tt>GameState</tt> class represents the current status and major components of the Zork-style, text-based game. <p>
 * The <tt>GameState</tt> class contains and manipulates several objects that are used to represent {@link Player}s, {@link NonPlayableCharacter}s, {@link Item}s and the {@link Dungeon} being played. It keeps track which player's turn it is.<p>
 * It is also used to load preset game attributes set by the map maker, such as minimum and maximum number of players and possible {@link PlayerType}s that users can choose from.<p>
 * There can only be one <tt>GameState</tt> object instantiated for a game. This class provides a {@link GameState#instance} method for instantiating and calling the <tt>GameState</tt>.<p>
 * 	<blockquote>Example: <tt>GameState state = new GameState.instance();</tt></blockquote>
 * @author James Peacemaker
 */
class GameState {

	private ArrayList<Player> players;
	private ArrayList<NonPlayableCharacter> npcs;
	private ArrayList<PlayerType> playerTypes;
	private Dungeon dungeon;
	private Player currentPlayer;
	private int maxPlayers;
	private int minPlayers;



	/**
	 * This exception is thrown when a saved game file (.sav) or Zork file (.zork) is incompatible with this class. This exception is thrown by the {@link GameState#restore} method  if the Zork version in the .sav or .zork file is not compatible with the GameState class. This exception is also thrown if the file is structured so that it is not compatible.
	 */
	public static class IllegalSaveFormatException extends Exception {

		/**
		 * Signals that there was an error loading the GameState from a file.
		 * @param e The detail message.
		 */	
		public IllegalSaveFormatException(String e) {
			super(e);
		}
	}




	static String DEFAULT_SAVE_FILE = "zork_save";
	static String SAVE_FILE_EXTENSION = ".sav";
	static String SAVE_FILE_VERSION = "Zork III save data";
	static String SAVE_FILE_VERSION2 = "Zork ++ save data";

	//static String CURRENT_ROOM_LEADER = "Current room: ";
	//static String ADVENTURER_LEADER = "Adventurer:";
	//static String INVENTORY_LEADER = "Inventory: ";

	private static GameState theInstance;
	static java.util.Random random = new java.util.Random(13);

	/**
	 * Instantiates a new <tt>GameState</tt> if one has not yet been created. If the <tt>GameState</tt> has already been created then this method returns that <tt>GameState</tt>.
	 * @return GameState
	 */
	static synchronized GameState instance() {
		if (theInstance == null) {
			theInstance = new GameState();
		}
		return theInstance;
	}

	private GameState() {
		this.players = new ArrayList<Player>();
		this.npcs = new ArrayList<NonPlayableCharacter>();
		this.playerTypes = new ArrayList<PlayerType>();
		this.minPlayers = 1;
		this.maxPlayers = 1;

	}



	/**
	 * Adds a {@link Player} to the list of players in the GameState.<p>
	 * Players in GameState have turns in the same order that they are added with this method.<p>
	 * This method sets the current player in GameState to the player added.<p>
	 * @param p The player being added to the <tt>GameState</tt>.<p>
	 */	
	void addPlayer (Player p){
		this.players.add(p);
		this.currentPlayer = p;	
	}	



	/**
	 * Removes a {@link Player} from the list of players in the GameState.<p>
	 * If the current player is removed, the <tt>GameState</tt>'s current player needs to be updated or advanced to the next player using the {@link GameState#nextPlayer} method.<p>
	 * @param p The player being removed from the <tt>GameState</tt>.
	 */	
	void removePlayer(Player p) {
		this.players.remove(p);
	}




	/**
	 * Advances the current player to the next player in the list of players. <p>
	 * It moves the turn to the next player. If there is only one player in the GameState, the current player stays the same.<p>
	 * Players must be added to the <tt>GameState</tt> using the {@link GameState#addPlayer} method before using the this method.<p>
	 */
	String nextPlayer(){
		int turn = this.players.indexOf(this.currentPlayer);
        String msg = takeTurnNPCs();
		if ((turn+1)==this.players.size()){//if turn is last player, move to first player
			this.currentPlayer = players.get(0);

		} else{//move to next player
			this.currentPlayer = players.get(turn+1);
		}
		return msg;
	}



	/**
	 * Returns the current player whose turn it is.
	 * @return The current player whose turn it is. 
	 */
	Player getCurrentPlayer(){
		return this.currentPlayer;
	}



	/**
	 * Sets the current player whose turn it will be.
	 * @param p The current player whose turn it will be. 
	 */
	void setCurrentPlayer(Player p){
		this.currentPlayer = p; 
	}



	/**
	 * Returns the total number of players. <p>
	 * This method can be used to tell if the game is over if the number returned is 0.
	 * @return The total number of players. 
	 */
	int getNumPlayers(){
		return this.players.size();
	}


	/**
	 * Returns the maximum number of players.<p>
	 * The maximum number of players should be set by the {@link GameState#restore} method when it loads the map maker's .zork file. 
	 * @return The maximum number of players. 
	 */
	int getMaxPlayers(){
		return this.maxPlayers;
	}




	/**
	 * Sets the maximum number of players that should be added to the game.<p>
	 * Maximum number of players is used as a guide, not a hard limit. <p>
	 * {@link GameState#addPlayer} does not actually enforce this limit.<p>
	 * @param i The maximum number of players. 
	 */
	void setMaxPlayers(int i){
		this.maxPlayers = i;
	}





	/**
	 * Returns the minimum number of players.<p>
	 * The minimum number of players should be set by the {@link GameState#restore} method when it loads the map maker's .zork file. <p>
	 * @return The minimum number of players. 
	 */
	int getMinPlayers(){
		return this.minPlayers;
	}



	/**
	 * Sets the minimum number of players that should be added to the game.<p>
	 * Minimum number of players is used as a guide, not a hard limit. <p>
	 * {@link GameState#addPlayer} does not actually enforce this limit.<p>
	 * @param i The minimum number of players. 
	 */
	void setMinPlayers (int i){
		this.minPlayers = i;
	}




	/**
	 * Cycles through all NPCs ({@link NonPlayableCharacter} class) in the <tt>GameState</tt> and has them each take a turn.<p>
	 * NPCs take a turn using the {@link NonPlayableCharacter#takeTurn()} method.<p>
	 * If no NPCs have been added to the <tt>GameState</tt>, no actions are taken.
	 */
	String takeTurnNPCs(){
		
		String npcString = "";
		//NPCs only take turn if player is last in players
		if ((this.players.indexOf(this.currentPlayer)+1)==this.players.size()){


			for (NonPlayableCharacter n : this.npcs) {

				if (n.canFollow() == true && n.isFollowing() != null){
					if(n.isFollowing().getJustTeleported() == true){

						n.setCurrentRoom(n.isFollowing().getCurrentRoom());
						npcString += n.getName() + " Teleported!";
						n.isFollowing().setJustTeleported(false);
						return npcString + "\n";
					}
				}else{
					//check to see if npc can move & there are no players in the room. if true, move to random connected room
					boolean noPlayers = true;
					for (int i = 0; i < 1; i++){
						if ( this.players.get(i).getCurrentRoom() == n.getCurrentRoom()){//there is a player in the room
							noPlayers = false;
						}
					}
					if (n.canMove() == true && noPlayers == true){
					
						Room nextRoom = n.getCurrentRoom().getRandomConnectedRoom();
						n.setCurrentRoom(nextRoom);
						//npcString += "\n" + n.getName() + " moved to " + n.getCurrentRoom().getTitle() + "\n";
					       	return npcString;	
					}
				}	

				//check to see if enemy is in the same room
				try {
					//forces npc to wait to attack until player gets description of room the first time
					if (n.getCurrentRoom().getBeenHere()==true){

						//get random target in room
						Player target = getRandomTargetInRoom(n);
						//System.out.println(n.getName() + " attacked " + target.getName());

						int damage = 0;
						String attackMessage = "";;

						if (n.getWeapon() == null){
							//damage = strength if no weapon
							damage = n.getStrength();
						} else
							//damage = weapon damage * 1+strength/10
							damage = ((n.getWeapon().getDamage())*(10+n.getStrength()))/10;


						//check to see if attack is blocked
						if (target.getShield()!=null) {
							//if random*100 is less than block chance, the return attack was blocked
							if (100*GameState.instance().random.nextDouble() <= (double) target.getShield().getChanceToBlock()){
								npcString += "\n" + n.getName() + "'s attack was blocked by " + target.getName() + ".\n";
								damage=0;
							} 

						}


						//check to see if attack missed due to dexterity
						int totalDexterity = n.getDexterity() + target.getDexterity();

						//if Random number * total dexterity < Player Dexterity, then hit	
						if (damage != 0 && (double)totalDexterity * GameState.instance().random.nextDouble() <= (double)target.getDexterity()){
							npcString += n.getName() + "'s attack was dodged by " + target.getName() + ".\n";
							damage = 0;
						}	
						
						if (damage!=0) {
							//reduce damage based on armor (damage = damage -(damage * damagereduction/100)
							if (target.getArmor() != null){
								damage = damage-(damage*target.getArmor().getDamageReduction()/100);
							}	

							//damage target
							target.setHealth(target.getHealth()-damage);
							attackMessage += n.getName() + " attacked " + target.getName() + " for " + damage + " damage.";

							//check if dead
							if (target.getHealth() <= 0){
								attackMessage += " " + target.getName() + " died.\n";
								target.die();
							}
							
							if (target.getHealth() > target.getMaxHealth()){
								target.setHealth(target.getMaxHealth());
							}

							npcString +=  attackMessage + "\n";
						}

					}

				}
				catch (Character.NoCharacterException e){
					//target not found

					//if canMove= true, move to random connected room






				}

			}

		}
		return npcString;
	}



	/**
	 * Returns the NPC ({@link NonPlayableCharacter} class) that has the matching name.<p>
	 * It only returns the first NPC (in order they were added) with the name if more than one has the same name. Map makers should avoid having NPCs with the same name.<p>
	 * @param s The name of the NPC.
	 * @return NPC corresponding to the name given.
	 * @throws NoCharacterException if NPC can't be found or if no NPCs have been added to the GameState.
	 */
	NonPlayableCharacter getNPCNamed(String s) throws Character.NoCharacterException {

		//loops through NPC array list and returns NPC if name matches
		for (NonPlayableCharacter p : this.npcs){
			if (p.getName().equalsIgnoreCase(s)){
				return p;
			}
		}
		throw new Character.NoCharacterException("NPC not found");
	}


	/**
	 * Returns the player ({@link Player} class) that has the matching name.<p>
	 * It only returns the first player (in order they were added) with the name if more than one has the same name.
	 * @param s The name of the player.
	 * @return Player corresponding to the name given.
	 * @throws Character.NoCharacterException if player can't be found or if no players have been added to the GameState.
	 */
	Player getPlayerNamed(String s) throws Character.NoCharacterException {

		//loops through Player array list and returns Player if name matches
		for (Player p : this.players){
			if (p.getName().equalsIgnoreCase(s)){
				return p;
			}
		}
		throw new Character.NoCharacterException("Player not found");
	}



	/**
	 * Returns the {@link PlayerType} that has the matching name.<p>
	 * It only returns the first PlayerType (in order they were added) with the name if more than one has the same name. Map makers should avoid having the same name for more than one PlayerType.<p>
	 * @param s The name of the PlayerType.
	 * @return PlayerType corresponding to the name given.
	 * @throws PlayerType.NoPlayerTypeException if {@link PlayerType} can't be found or if no PlayerType has been added to the GameState.
	 */
	PlayerType getPlayerTypeNamed(String s) throws PlayerType.NoPlayerTypeException {
		//loops through PlayerType array list and returns PlayerType if name matches
		for (PlayerType p : this.playerTypes){
			if (p.getTypeName().equalsIgnoreCase(s)){
				return p;
			}
		}
		throw new PlayerType.NoPlayerTypeException("No player type found");
	}





	/**
	 * Adds a {@link NonPlayableCharacter} to the list of NPCs maintained by the <tt>GameState</tt>.
	 * @param npc The {@link NonPlayableCharacter} that is being added to the <tt>GameState</tt>'s list of NPCs.
	 */
	void addNPC(NonPlayableCharacter npc){
		this.npcs.add(npc);
	}





	/**
	 * Removes a {@link NonPlayableCharacter} from the list of NPCs in the <tt>GameState</tt>.<p>
	 * If NPC can't be found, no action is taken.	
	 * @param npc The NPC being removed from the <tt>GameState</tt>.
	 */	
	void removeNPC(NonPlayableCharacter npc){
		this.npcs.remove(npc);
	}





	/**
	 * Adds a {@link PlayerType} to the list of player types used by the GameState.
	 * @param newPlayerType The PlayerType being added.
	 */
	void addPlayerType(PlayerType newPlayerType){
		this.playerTypes.add(newPlayerType);
	}




	/**
	 * Returns a random {@link Player} who is in the room.<p> 
	 * This method can be used to acquire a target for a hostile {@link NonPlayableCharacter} to attack.<p>
	 * This method throws a {@link Character.NoCharacterException} if no player is found in the room.<p>
	 * @param r The room that is being searched for a player.
	 * @return A random player found in the room.
	 * @throws Character.NoCharacterException if no player is found in the room.  
	 */
	Player getRandomTargetInRoom(NonPlayableCharacter attacker) throws Character.NoCharacterException {


		//build an array of possible targets
		ArrayList<Player> targetList = new ArrayList<Player>();

		//for hostile npcs		
		if (attacker.getHostility() < 0) {

			//loops through Player array list and adds player to target list if in same room
			for (Player p : this.players){
				if (p.getCurrentRoom() == attacker.getCurrentRoom()){
					targetList.add(p);
					//System.out.println("Adding" + p.getName());
				}
			}

			//loops through Player array list and adds player to target list if in same room
			//for (NonPlayableCharacter n : this.npcs){
			//	if (n.getCurrentRoom() == attacker.getCurrentRoom() && n.getHostility() > 0){
			//		targetList.add(n);
			//		//System.out.println("Adding" + n.getName());
				//}
			//}
		}


		//for friendly npcs		
		if (attacker.getHostility() > 0) {

			//loops through Player array list and adds player to target list if in same room
			for (NonPlayableCharacter n : this.npcs){
				if (n.getCurrentRoom() == attacker.getCurrentRoom() && n.getHostility() < 0){
					//targetList.add(n);
					//System.out.println("Adding" + n.getName());
				}
			}
		}

		//get random target from the list
		if (targetList.size() !=0){
			int randomIndex = (int) (GameState.instance().random.nextDouble()*targetList.size());	
			//System.out.println(randomIndex);
			return targetList.get(randomIndex);
		}

		//throw exception if no targets found
		throw new Character.NoCharacterException("No targets to attack");


	}






	/**
	 * Loads saved game information from a .sav file.<p>
	 * The .sav file contains the status of rooms, players and NPCs.<p>
	 * The file being hydrated should contain the following information in order:<p>
	 * <blockquote>1. A line stating the version. (Example: "Zork III save data") If the Zork version is not compatible, this method will throw an IllegalSaveFormatException.<br>
	 * 2. A line stating the dungeon file, starting with "Dungeon file: " followed by the file location. If this file can't be found, it will throw a FileNotFound exception.<br>
	 * 3. A line stating "Room states:"<br>
	 * 4. A series of text entries that will be hydrated by the {@link Dungeon} class and ends with a section delimiter "===". Actual format for these text entries will be handled by the {@link Dungeon#restoreState} method. Entries will continue to be hydrated until the "===" is read. Errors in this sections will reult in a {@link Dungeon.IllegalDungeonFormatException}.<br>
	 * 5. A series of text entries that will be hydrated by the Player class, with each separated by a "---" delimiter line and ending with a section delimiter "===" line. Actual format for these text entries will be handled by the {link Player#restore} method. For multiple players, the {@link Player#restore} method should be called repeatedly until the "===" delimiter is reached or until a {@link Character.NoCharacterException} is returned.  <br>
	 * 6. A line stating "NPCs:"<br>
	 * 7. A series of text entries that will be hydrated by the {@link NonPlayableCharacter} class, with each separated by a "---" delimiter line and ending with a section delimiter "===" line. Actual format for these text entries will be handled by the {@link NonPlayableCharacter#restore} method. For multiple NPCs, the {@link NonPlayableCharacter#restore} method should be called repeatedly until the "===" delimiter is reached or until a {@link Character.NoCharacterException} is returned. </blockquote><p> 
	 * To stay compatible with older verions of Zork, missing sections will be ignored.
	 * @param filename the name of the .sav file to be hydrated.
	 * @throws FileNotFoundException if the .sav file does not exist.
	 * @throws IllegalSaveFormatException if the format of the .sav file does not conform to the standard.
	 * @throws Dungeon.IllegalDungeonFormatException if the format of the dungeon does not conform to the standard.
	 */
	void restore(String filename) throws FileNotFoundException,
	     IllegalSaveFormatException, Dungeon.IllegalDungeonFormatException {
		     //restores game from a .sav file
		     Scanner s = new Scanner(new FileReader(filename));

		     //get save file version
		     String zorkVersion = s.nextLine();
		     if (!zorkVersion.equals(SAVE_FILE_VERSION) && !zorkVersion.equals(SAVE_FILE_VERSION2)) {
			     throw new IllegalSaveFormatException("Save file not compatible.");
		     }

		     String dungeonFileLine = s.nextLine();

		     if (!dungeonFileLine.startsWith(Dungeon.FILENAME_LEADER)) {
			     throw new IllegalSaveFormatException("No '" +
					     Dungeon.FILENAME_LEADER + 
					     "' after version indicator.");
		     }

		     //Gets Dungeon file: and Room states: and hydrates rooms
		     dungeon = new Dungeon(dungeonFileLine.substring(Dungeon.FILENAME_LEADER.length()), false);
		     dungeon.restoreState(s,false);

		     //Get Players
		     try {
			     // Instantiate and add players.
			     while (true) {
				     GameState.instance().addPlayer(new Player(s));
			     }
		     } catch (Character.NoCharacterException e) {  /* end of players*/ }


		     //Remove all npcs
		     this.npcs.clear();


		     //Get NPCs
		     try {
			     // Instantiate and add NPCs.
			     while (true) {
				     GameState.instance().addNPC(new NonPlayableCharacter(s, dungeon));
			     }
		     } catch (Character.NoCharacterException e) {  /* end of players*/ }




	}



	/**
	 * Stores saved game information to the default .sav file location.
	 * The default location for the file to be saved is held by the static String variable DEFAULT_SAVE_FILE.
	 * The .sav file contains the status of rooms, players and NPCs<p>.
	 * The file being saved should contain the following information in order:<p>
	 * <blockquote>1. A line stating the version. (Example: "Zork III save data").<br>
	 * 2. A line stating the dungeon file, starting with "Dungeon file: " followed by the file location.<br>
	 * 3. A line stating "Room states:"<br>
	 * 4. A series of text entries that will be persisted by the {@link Dungeon} class and ends with a section delimiter "===". Actual format for these text entries will be handled by the {@link Dungeon#storeState} method. This section will end with a delimiter line "===".<br>
	 * 5. A series of text entries that will be persisted by the {@link Player} class, with each separated by a "---" delimiter line and the section ending with a section delimiter "===" line. Actual format for these text entries will be handled by the {@link Player#store} method. For multiple players, the {@link Player#store} method should be called repeatedly until all players have been persisted. The "===" delimiter will end the section.  <br>
	 * 6. A line stating "NPCs:"<br>
	 * 7. A series of text entries that will be persisted by the {@link NonPlayableCharacter} class, with each separated by a "---" delimiter line and ending the section with a section delimiter "===" line. Actual format for these text entries will be handled by the {@link NonPlayableCharacter#store} method. For multiple NPCs, the {@link NonPlayableCharacter#store} method should be called repeatedly until all NPCs have been persisted. </blockquote> 
	 * @throws IOException if the file can't be created or written to.
	 */
	void store() throws IOException {
		store(DEFAULT_SAVE_FILE);
	}



	/**
	 * Stores saved game information to a specified .sav file.<p>
	 * The .sav file contains the status of rooms, players and NPCs.<p>
	 * The file being saved should contain the following information in order:<p>
	 * <blockquote>1. A line stating the version. (Example: "Zork III save data").<br>
	 * 2. A line stating the dungeon file, starting with "Dungeon file: " followed by the file location.<br>
	 * 3. A line stating "Room states:"<br>
	 * 4. A series of text entries that will be persisted by the {@link Dungeon} class and ends with a section delimiter "===". Actual format for these text entries will be handled by the {@link Dungeon#storeState} method. This section will end with a delimiter line "===".<br>
	 * 5. A series of text entries that will be persisted by the {@link Player} class, with each separated by a "---" delimiter line and the section ending with a section delimiter "===" line. Actual format for these text entries will be handled by the {@link Player#store} method. For multiple players, the {@link Player#store} method should be called repeatedly until all players have been persisted. The "===" delimiter will end the section.  <br>
	 * 6. A line stating "NPCs:"<br>
	 * 7. A series of text entries that will be persisted by the {@link NonPlayableCharacter} class, with each separated by a "---" delimiter line and ending the section with a section delimiter "===" line. Actual format for these text entries will be handled by the {@link NonPlayableCharacter#store} method. For multiple NPCs, the {@link NonPlayableCharacter#store} method should be called repeatedly until all NPCs have been persisted. </blockquote> 
	 * @param saveName the name of the save file.
	 * @throws IOException if the file can't be created or written to.
	 */
	void store(String saveName) throws IOException {
		//store in specified .sav file	
		String filename = saveName + SAVE_FILE_EXTENSION;
		PrintWriter w = new PrintWriter(new FileWriter(filename));

		//print save file version
		w.println(SAVE_FILE_VERSION2);

		//print dungeon 
		this.dungeon.storeState(w);

		//print list of players
		for (Player p : this.players) {
			p.store(w);
		}

		//print delimiter
		w.println("===");

		//print list of npcs
		for (NonPlayableCharacter n : this.npcs) {
			n.store(w);
		}

		w.close();
	}




	/**
	 * Assigns a {@link Dungeon} to the <tt>GameState</tt> so that it can be played.
	 * @param dungeon is the {@link Dungeon} that is being played.
	 */
	void initialize(Dungeon dungeon) {
		this.dungeon = dungeon;
	}




	/**
	 * Returns the {@link Dungeon} being played.<p>
	 * The dungeon needs to have been set by the {@link GameState#initialize} method.
	 * @return the dungeon that is currently being played.
	 */
	Dungeon getDungeon() {
		return dungeon;
	}



	//returns a list of player types for the user to choose from	
	public String describePlayerTypes(){

		if (this.playerTypes.isEmpty()){
			return "none";
		} else {

			String playerTypesDescription = ""; 
			for (PlayerType p : this.playerTypes){ 
				playerTypesDescription = playerTypesDescription + p.getTypeName() + 
					" (dexterity:" + p.getDexterity() + ", endurance:" + p.getEndurance() 
					+ ", strength:" + p.getStrength() + ").\n"; 
			}
			return playerTypesDescription;

		}
	}




	//describes the NPCs in the room	
	public String getDescriptionOfNPCs (Room r){

		String npcDescription = "";
		if (!this.npcs.isEmpty()){
			for (NonPlayableCharacter n : this.npcs){

				//System.out.println(n.getName());
				//System.out.println(n.getCurrentRoom().getTitle());
				//System.out.println(r.getTitle());
				if (n.getCurrentRoom().getTitle().equals(r.getTitle())){
					npcDescription = npcDescription + n.getDescription() + "\n";
				}
			}
		}
		return npcDescription;

	}




}
