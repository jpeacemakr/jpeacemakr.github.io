
import java.util.Scanner;

/**
 * Armor is an {@link Item} subtype that when eqiupped, reduces damage 
 * inflicted upon the wearer.   
 *@author Michael Goyer
 */
public class Armor extends Item {
	
	private int damageReduction;

	//constructor
	public Armor(Scanner s) throws NoItemException
	{
		super(s);
		//steals the damage value and uses it for damageReduction	
		this.damageReduction = this.damage;
	}



	/**
	 * Returns the int used to calculate the amount by which
	 * damage will be decreased when inflicted upon the 
	 * Armor's wearer.
	 */
	public int getDamageReduction(){
		return this.damageReduction;
	}

	/**
	 * Sets the int used to calculate the amount by which damage
	 * will be decreased when inflicted upon the Armor's wearer.
	 * @param i The int to represent the percent chance to block. 
	 */
	public void setDamageReduction(int i){
		this.damageReduction = i;
	}

	/**
	 * Moves an instantiated Armor item from a Character's inventory 
	 * to their equippedArmor slot, reducing any damage inflicted upon
	 * them. This method overrides the Item class's equip() method, 
	 * ensuring that Armor items are only used as a character's Armor 
	 * instead of as a weapon. 
	 */
	public void equip(){

		//move current armor to player's inventory
		if (GameState.instance().getCurrentPlayer().getArmor() != null) {
			GameState.instance().getCurrentPlayer().addToInventory(GameState.instance().getCurrentPlayer().getArmor());
		}	





		//equip new armor
		GameState.instance().getCurrentPlayer().setArmor(this);
	}
}
