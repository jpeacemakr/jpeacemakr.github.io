
import java.util.ArrayList;

class ScoreCommand extends Command{

	private String cmd;
	private int points;

	ScoreCommand(String cmd){
		super(cmd);
		this.cmd = cmd;

		this.points = GameState.instance().getCurrentPlayer().getScore();
	}

	String execute(){
		
		String pointMSG = "You have a total score of " + this.points + " points,";
		String rank = " ";
		if(this.points == 0){
			rank = "Noob";
		}else if(this.points >= 1 && this.points < 11){
			rank = "Novice";
		}else if(this.points >= 11 && this.points < 21){
			rank = "Adventurer";
		}else if(this.points >= 21 && this.points < 31){
			rank = "Brave warrior";
		}else if(this.points >= 31 && this.points < 41){
			rank = "Hero";
		}else if(this.points >= 41 && this.points < 51){
			rank = "Godlike";
		}	

		String returnMSG = pointMSG + " granting you rank " + rank + ".\n";
			

		return returnMSG;
	}
}
