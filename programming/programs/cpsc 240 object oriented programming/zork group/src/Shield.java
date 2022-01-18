
import java.util.Scanner;

/**
 * A shield is an {@link Item} subclass that when equipped, has 
 * a chance of blocking any damage inflicted on the character 
 * who equipped it.
 * @author Michael Goyer 
 */
public class Shield extends Item {
	
	private int chanceToBlock;

	//constructor	
	public Shield(Scanner s) throws NoItemException
	{
		super(s);
		//steals the damage value and uses it for chanceToBlock	
		this.chanceToBlock = this.damage;
	
	}


	/**
	 * Returns an integer used to represent the Shield's percent chance
	 * of blocking any given attack on it's user. 
	 */
	public int getChanceToBlock(){
		return this.chanceToBlock;
	}
	
	/**
	 * Sets the int representing the percent chance of an attack being blocked.
	 * @param i the int to represent the percent chance of an attack being blocked.  
	 */
	public void setChanceToBlock(int i){
		this.chanceToBlock = i;
	}
	
	/**
	 * Moves an instantiated Shield Item from a character's inventory to 
	 * their equippedShield slot, adding the chance of any attack on 
	 * the character to be blocked completely. This overrides the Item
	 * class's equip() method, ensuring that Shield items are only used
	 * as Shields, rather than as a weapon.    
	 */
	public void equip(){
	
		//move current shield to player's inventory
		if (GameState.instance().getCurrentPlayer().getShield()!= null) {
			GameState.instance().getCurrentPlayer().addToInventory(GameState.instance().getCurrentPlayer().getShield());
		}	


		//equip new shield
		GameState.instance().getCurrentPlayer().setShield(this);

	}
}
