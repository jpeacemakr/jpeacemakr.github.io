
import java.util.ArrayList;
import java.util.Random;

class HealthCommand extends Command {

	private String cmd;
	private int healthPoints;

	HealthCommand(String cmd){
		super(cmd);
		this.cmd = cmd;
		this.healthPoints = GameState.instance().getCurrentPlayer().getHealth();
	}
	String execute(){
		
		String message = " ";
		Random rand = new Random();
		Player currentPlayer = GameState.instance().getCurrentPlayer();
		
		double currentHP = this.healthPoints;	
		double maxHP = currentPlayer.getMaxHealth(); 
		double healthPercentage = currentHP / maxHP;
		healthPercentage = healthPercentage * 100;

		ArrayList<String> goodHealthMessages = new ArrayList<String>();
		ArrayList<String> okHealthMessages = new ArrayList<String>();
		ArrayList<String> badHealthMessages = new ArrayList<String>();
		ArrayList<String> nearDeadMessages = new ArrayList<String>();
		
		//76-100% health
		goodHealthMessages.add("You feel top-notch:");
		goodHealthMessages.add("You are running like a well-oiled machine:");
		goodHealthMessages.add("You have an incredible headache... wait... it's gone. You're fine:");
		goodHealthMessages.add("You're mildly frustrated with the current state of affairs, but physically fine:");
		goodHealthMessages.add("You're fine, calm down:");
		goodHealthMessages.add("No cause for concern... Yet:");

		//51-75% health
		okHealthMessages.add("You've got some bumps and bruises, but at least you're alive:");
		okHealthMessages.add("A few Band-Aids could'nt hurt:");
		okHealthMessages.add("You've probably been better, but you've definetely been worse:");
		okHealthMessages.add("You have a dreadful stomach cramp, but you could be worse off:");
		okHealthMessages.add("You have some papercuts, and various other minor injuries, mainly just an annoyance:");
		okHealthMessages.add("There's something on your arm... tis but a scratch, you're alright:");

		//26-50% health
		badHealthMessages.add("There's certainly cause for concern:");
		badHealthMessages.add("You're pretty banged up:");
		badHealthMessages.add("You could probably get a job as an extra in a two star zombie movie:");
		badHealthMessages.add("You look rough around the edges... even more so than usual:");
		badHealthMessages.add("You look a bit worse for the wear:");
		badHealthMessages.add("There's a lot of blood... ah it's just a flesh wound:");

		//1-25% health
		nearDeadMessages.add("Your mother has the right to be worried at this point:");
		nearDeadMessages.add("You are on the brink of death:");
		nearDeadMessages.add("It's impressive that you're still standing:");
		nearDeadMessages.add("Let's just say you should enjoy breathing while you can:");
		nearDeadMessages.add("You might not want to buy any green bananas:");
	

		if(healthPercentage >= 1 && healthPercentage <= 25){
			message = nearDeadMessages.get(rand.nextInt(nearDeadMessages.size()));
		}else if(healthPercentage >= 26 && healthPercentage <= 50){
			message = badHealthMessages.get(rand.nextInt(badHealthMessages.size()));	
		}else if(healthPercentage >= 51 && healthPercentage <= 75){
			message = okHealthMessages.get(rand.nextInt(okHealthMessages.size()));
		}else if(healthPercentage >= 76 && healthPercentage <= 100){
			message = goodHealthMessages.get(rand.nextInt(goodHealthMessages.size()));
		}

		return message + " " + currentHP + "/" + maxHP + "\n";
	}
}
