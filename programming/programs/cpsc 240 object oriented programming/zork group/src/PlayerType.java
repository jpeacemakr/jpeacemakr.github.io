import java.util.Scanner;
import java.lang.Integer;


/**
 * A <tt>PlayerType</tt> represents  preset stats (dexterity, endurance, strength) used for a {@link Player}.<p>
 * Player types are meant to be hydrated from a .zork file and will give a user several preset options to set their player's stats. Each <tt>PlayerType</tt> has a name associated with the given set of stats.<p>
 *<p>
 * Examples used for different classes:<p>
 * <blockquote>Paladin can have dexterity 5, endurance 7, strength 6. <br>
 * Barbarian can have dexterity 3, endurance 6, strength 8.<br>
 * Thief can have dexterity 7, endurance 5, strength 4.</blockquote><p>
 *<p>
 * Examples used for different difficulties:<p>
 * <blockquote>Normal can have dexterity 9, endurance 9, strength 9.<br>
 * Difficult can have dexterity 7, endurance 7, strength 7.<br>
 * Nightmare can have dexterity 5, endurance 5, strength 5.<blockquote><p>
 * @author James Peacemaker
 */
public class PlayerType {

	private String typeName;
	private int strength;
	private int dexterity;
	private int endurance;



	/**
	 * This exception is thrown when a <tt>PlayerType</tt> can't be found or when a <tt>PlayerType</tt> can't be hydrated from a file.
	 */
	public static class NoPlayerTypeException extends Exception {
		/**
		 * Signals that there was an error hydrating <tt>PlayerType</tt> information or that the <tt>PlayerType</tt> could not be found.
		 * @param e The detail message.
		 */	
		public NoPlayerTypeException(String e) {
			super(e);
		}
	}




	/**
	 * Reads a line of text from a file to create a <tt>PlayerType</tt>.<p>
	 * The line of text read from the Scanner must be the name of the player type followed by ":" and three ints separated by commas and no spaces. The stats are read in the following order: dexterity,endurance,strength.<p>
	 * <blockquote>Example: Warrior:5,7,5</blockquote>
	 * @param s The Scanner being read.
	 * @throws NoPlayerTypeException if the <tt>PlayerType</tt> can't be hydrated from the Scanner or if the delimiter "===" is found.
	 */
	PlayerType (Scanner s) throws NoPlayerTypeException {
		String textLine = s.nextLine();
		if (textLine.equals("===")){
			throw new NoPlayerTypeException("End of PlayerTypes");
		}	
		
		if (textLine.equals("Classes:")){
			textLine = s.nextLine();//skip "Classes:" line and ignore it if present
		}
		
		//get name
		String[] nameSplit = textLine.split(":");
		this.typeName = nameSplit[0];

		//gets stats
		String statsText = nameSplit[1];
		String[] statsSplit = statsText.split(",");

		this.dexterity = java.lang.Integer.parseInt(statsSplit[0]);
		this.endurance = java.lang.Integer.parseInt(statsSplit[1]);
		this.strength = java.lang.Integer.parseInt(statsSplit[2]);
	}	

	


	/**
	 * Constructs a <tt>PlayerType</tt> with a default values.<p>
	 * The default <tt>PlayerType</tt> has no name (a String equal to "") and dexterity, endurance and strength stats all set to 100.
	 */
	PlayerType() {
		this.typeName = "";
		this.strength = 10;
		this.endurance = 10;
		this.dexterity = 10;
	}



	/**
	 * Returns the dexterity value of the <tt>PlayerType</tt>.
	 * @return The dexterity value of the <tt>PlayerType</tt>.
	 */
	public int getDexterity() {return this.dexterity;}




	/**
	 * Returns the endurance value of the <tt>PlayerType</tt>.
	 * @return The endurance value of the <tt>PlayerType</tt>.
	 */
	public int getEndurance() {return this.endurance;}



	/**
	 * Returns the strength value of the <tt>PlayerType</tt>.
	 * @return The strength value of the <tt>PlayerType</tt>.
	 */
	public int getStrength() {return this.strength;}



	/**
	 * Returns the name of the <tt>PlayerType<tt>.
	 * @return The name of the <tt>PlayerType<tt>.
	 */
	public String getTypeName() {return this.typeName;}

}




