/**
  * An object of AttackCommand represents an instance where the user
  * enters "attack" in the command prompt.
  * @author JD
  */
public class AttackCommand extends Command {
	
	private String targetName;
	private String cmd;

	/**
	  * The constructor is passed a String that starts with "attack" as an
	  * identifier in CommandFactory, and if it is followed by another word,
	  * saves that word as the target Character's name.
	  */
	AttackCommand(String cmd){
		super(cmd);
		this.cmd = cmd;
		try{
			String[] cmdSplit = cmd.split(" ");
			this.cmd = cmdSplit[0]; //"take" can be ignored
			this.targetName = cmdSplit[1];
		} catch (ArrayIndexOutOfBoundsException e){
			this.targetName = null;
		}
	}
	
	/**
	  * This method compares the dexterity of the current Player and the target
	  * Character to determine which party deals damage first. Damage is calculated
	  * by the damage value of the equipped weapon (int D), the damage resistance of the
	  * armor (double DR less than 1), the endurance of the Character (double E less than 1)
	  * and the chance to block of the shield (double CB less than 1). If CB does
	  * not block the blow, the amount of health taken from the target is D * DR * E.
	  */
	String execute(){
		
		Character target = new Character("blank", GameState.instance().getDungeon().getEntry());

		//find NPC or Player named this.targetName
		try {
			target = GameState.instance().getNPCNamed(this.targetName);
		}
		catch (Character.NoCharacterException e) {
			try {
				target = GameState.instance().getPlayerNamed(this.targetName);
			}
			catch (Character.NoCharacterException f) {
				return "Target does not exist.\n";
			}
		}

		//check to see if target is in the same room
		if (target.getCurrentRoom() == GameState.instance().getCurrentPlayer().getCurrentRoom()){
			
			int damage = 0;
			String attackMessage = "";;

			if (GameState.instance().getCurrentPlayer().getWeapon() == null){
				//damage = 1 if no weapon
				damage = GameState.instance().getCurrentPlayer().getStrength();

			} else
				//damage = weapon damage * 1+strength/10
				damage = ((GameState.instance().getCurrentPlayer().getWeapon().getDamage())*
					(10+GameState.instance().getCurrentPlayer().getStrength()))/10;


			//check to see if attack is blocked
			
			if (target.getShield()!=null) {
				//if random*100 is less than block chance, the return attack was blocked
				if (100*GameState.instance().random.nextDouble() <= (double) target.getShield().getChanceToBlock()){
					//advance turn to next player if possible
					try {
						try{
							//set self as followed
							NonPlayableCharacter npc = (NonPlayableCharacter)target;
							npc.setFollowing(GameState.instance().getCurrentPlayer());
						}catch (ClassCastException e0){ //target is a player
						}
		 
						return "Attack was blocked.\n" + GameState.instance().nextPlayer(); 
					}
					catch (IndexOutOfBoundsException e) { 
						try{
							//set self as followed
							NonPlayableCharacter npc = (NonPlayableCharacter)target;
							npc.setFollowing(GameState.instance().getCurrentPlayer());
						}catch (ClassCastException e1){ //target is a player
						}

						return "Attack was blocked.\n";
					}
				}	
			}

			//check to see if attack missed
			int totalDexterity = GameState.instance().getCurrentPlayer().getDexterity() + target.getDexterity();
			
			//if Random number * total dexterity < Player Dexterity, then hit	
			if ((double)totalDexterity * GameState.instance().random.nextDouble() <= (double)target.getDexterity()){
				//advance turn to next player if possible
				try { 
					try{
				 		//set self as followed
						NonPlayableCharacter npc = (NonPlayableCharacter)target;
						npc.setFollowing(GameState.instance().getCurrentPlayer());
					}catch (ClassCastException e2){ //target is a player
					}
					return "Attack was dodged.\n" + GameState.instance().nextPlayer(); 
				}
				catch (IndexOutOfBoundsException e) { 
					try{
				 		//set self as followed
						NonPlayableCharacter npc = (NonPlayableCharacter)target;
						npc.setFollowing(GameState.instance().getCurrentPlayer());
					}catch (ClassCastException e3){ //target is a player
					}

					return "Attack was dodged.\n";
				}
			}	
			
			//reduce damage based on armor (damage = damage -(damage * damagereduction/100)
			if (target.getArmor() != null){
				damage = damage-(damage*target.getArmor().getDamageReduction()/100);
			}	

			//damage target
			target.setHealth(target.getHealth()-damage);
			
			//set damage message
			if (damage>=0){
				attackMessage += GameState.instance().getCurrentPlayer().getName() +
			       	" attacked " + this.targetName + " for " + damage + " damage.";
			}else {
				attackMessage += GameState.instance().getCurrentPlayer().getName() +
			       	" healed " + this.targetName + " for " + (0-damage) + " damage.";
			}

			//adjust hostility
			target.setHostility(target.getHostility() - (double)damage);
			
			try{
				//set self as followed
				NonPlayableCharacter npc = (NonPlayableCharacter)target;
				npc.setFollowing(GameState.instance().getCurrentPlayer());
			}catch (ClassCastException e4){ //target is a player
			}


			//check if dead
			if (target.getHealth() <= 0){
				target.die();
				attackMessage += " " + targetName + " died.";
			}
		
			//make sure health does not go over max if healing weapon was used
			if (target.getHealth() > target.getMaxHealth()){
				target.setHealth(target.getMaxHealth());
			}


			//advance turn to next player if possible
			try { return attackMessage + "\n" + GameState.instance().nextPlayer();}
			catch (IndexOutOfBoundsException e) { return attackMessage + "\n"; }
	

		} else {
			return "Target is not in the same room.\n";
		}


	}
}
