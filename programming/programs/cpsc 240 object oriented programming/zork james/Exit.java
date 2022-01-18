/**************************************************************************
 * Exit class serves as a connection between two Rooms. Each Room can have up to six exits NSEWUD
 * 
 * @author: James Peacemaker
******************************************************************************/
import java.util.Hashtable;
import java.util.Enumeration;
import java.io.PrintWriter;
import java.util.Scanner;


public class Exit{

	private String dir; // direction of the exit
	private Room src; // room you are leaving
	private Room dest; // room you are entering


	// constructor. creates exit and sets direction, source and destination rooms
	public Exit(String dir, Room src, Room dest){
		this.dir = dir;
		this.src = src;
		this.dest = dest;
	}


	public Exit(Scanner s, Dungeon d) throws Exception {
		System.out.println("Running Exit constructor");
		String temp = new String();
		temp = s.nextLine();
		//System.out.println ("1");
		System.out.println(temp);

		if (!temp.equals("===")){
			
			//System.out.println ("running dungeon.getroom from exit");
			this.src = d.getRoom(temp);
			
			//System.out.println ("running Room.gettitle from exit");
			System.out.println (this.src.getTitle());
			
			//System.out.println ("setting this.dir to nextline");
			
			this.dir = s.nextLine();
			//System.out.println ("2");
			System.out.println (this.dir);
			
			
			temp = s.nextLine();
			//System.out.println ("3");
			System.out.println(temp);
		
			this.dest = d.getRoom(temp);
			System.out.println (this.dest.getTitle());
			
			s.nextLine();	
			//System.out.println ("4");
				
			
			d.getRoom(this.src.getTitle()).addExit(this);
		
		}
		else {
			throw new Exception();
		}

	}



	private void init() {
	
	
	}





	// gives the description of the exit.
	String describe(){
		return "Moving " + this.dir + " from " + this.src.getTitle() + " to " + this.dest.getTitle() +".";
	}


	// returns the direction of the exit
	public String getDir(){
		return this.dir;
	}


	// returns the source room of the exit
	public Room getSrc(){
		return this.src;
	}

	// returns the destination of the exit
	public Room getDest(){
		return this.dest;
	}

}
