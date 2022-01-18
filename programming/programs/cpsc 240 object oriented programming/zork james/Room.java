/*****************************************************************************
 * Room contains the name, description and exits to other rooms. 
 * Also says if player has been in room before.
 * @author: James Peacemaker 
*****************************************************************************/

import java.util.Hashtable;
import java.util.Enumeration;
import java.io.PrintWriter;
import java.util.Scanner;

public class Room {


	private String title; //name of room
	private String desc; //description of room
	private boolean beenHere; //whether room has been visited
	private Hashtable<String, Exit> exits; //list of exits


	//constructor. accepts name of room
	Room (String title){
		
		System.out.println("Running Room constructor (String)");
		this.init();
		this.title = title;
	}


	//constructor when given a scanner
	public Room (Scanner s) throws Exception{
		System.out.println("Running Room (Scanner s)");
		this.init();
		try {
			//get first line. should be room title
			this.title = s.nextLine();

			//check if it is a delimiter
			if (this.title.equals("===")) {
				throw new Exception();
			}

			//get description of room until delimiter found
			String temp = s.nextLine();
			while (!temp.equals("---")){	
				this.desc = this.desc + temp;
				temp = s.nextLine();
			}
			//System.out.println(this.title);	
			//System.out.println(describe());	
		} 
		catch (Exception e) {
			throw new Exception();
		}

	}

	private void init() {
		System.out.println("Running Room.init");
		this.title = " ";
		this.beenHere = false;
		this.desc = " ";
		this.exits = new Hashtable<String, Exit>();
	}	


	//grabs beenHere line from scanner and sets room accordingly
	
	void restoreState (Scanner s){
		System.out.println("Running Room.restoreState");
		
		String isVisited = s.nextLine();
		if (isVisited.equals("beenHere=true")){
			this.beenHere = true;
		} else {
			this.beenHere = false;
		}

	}




	//print fields for room to PrintWrter file
	void storeState (PrintWriter w){
		if (this.beenHere==true) {
			w.println(this.title + ":");	
			w.println("beenHere=true");
			w.println("---");
		} 
	}




	// returns the name of the room
	public String getTitle(){
		return this.title;
	}


	// sets the description of the room
	public void setDesc(String desc){
		this.desc = desc;
	}



	// returns the name and description of the room and its exits. 
	// It does not include the description if visited before. 
	String describe(){

		//compile description of all exits
		String exitsDesc = new String();
		String tempKey = new String(); 

		Enumeration<String> exitKeys = this.exits.keys(); 
		while (exitKeys.hasMoreElements()){
			tempKey = exitKeys.nextElement();
			exitsDesc = exitsDesc + this.exits.get(tempKey).getDest().getTitle() + 
			" going " + this.exits.get(tempKey).getDir() + ". ";	
		}	


		//give the title. also give the full description if it is the first 
		//time in the room. Then list exits.
		if (this.beenHere == false) {
			this.beenHere = true;
			return "You are in " + this.title + ". " + this.desc + " Exits are: " + exitsDesc + "\n"; 
		
		}
		else {
			return "You are in " + this.title + ". Exits are: " + exitsDesc + "\n";
		}
	}



	//returns the new room when given an exit direction of the current room. 
	//it returns null if exit in that direction does not exist.
	Room leaveBy(String dir){
		if (this.exits.get(dir) == null) { 
			return null;	
		}
		else {
			return this.exits.get(dir).getDest();
		}
	}	


	//adds an exit to the room 
	public void addExit (Exit exit){
		this.exits.put(exit.getDir(), exit);
	}



	




}
