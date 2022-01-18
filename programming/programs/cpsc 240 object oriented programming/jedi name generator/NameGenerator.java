import java.util.Scanner;

class NameGenerator {


	public static void main (String args[]){


		Scanner text = new Scanner(System.in);
		Person jediNames[] = new Person[1001]; //array of type Person. I hate having an array with a set size here, but I was not sure how to create a dynamic array or linked list structure in Java.
		int i = 0; //number of names that were entered
		String done = "done";
		while (i<=1001){
		
			jediNames[i] = new Person();

			//Get first name
			System.out.print("Enter your first name:");
			jediNames[i].setFirstName(text.nextLine());
			if (jediNames[i].getFirstName().toLowerCase().equals("done")){
				break;
			}
			else {	

			//Get last name
			System.out.print("Enter your last name:");
			jediNames[i].setLastName(text.nextLine());


			//Get mother's maiden name
			System.out.print("Enter your mother's maiden name:");
			jediNames[i].setMomMaidenName(text.nextLine());
			
			//Get birth city
			System.out.print("Enter the city where you were born:");
			jediNames[i].setBirthCity (text.nextLine());

			//Calculate number of values and update highest number if more
			jediNames[i].setVowels();

			//increment loop counter
			i++;
			}
			
		}


		
		//print list of names. for debugging purposes only
		/*for (int printCount = 0; printCount<=i; printCount++){

			if (jediNames[printCount].getFirstName().toLowerCase().equals("done")){
				//System.out.print("All done.");
			}
			else {
				System.out.println(jediNames[printCount].getFirstName());
				System.out.println(jediNames[printCount].getLastName());
				System.out.println(jediNames[printCount].getMomMaidenName());
				System.out.println(jediNames[printCount].getBirthCity());
				System.out.println(jediNames[printCount].getVowels());
			}

		}*/




		//print list of jedi or sith names. they are sith if their voewls equal the max vowels
		for (int printCount = 0; printCount<=i; printCount++){

			if (jediNames[printCount].getFirstName().toLowerCase().equals("done")){
				//System.out.print("All done.");
			}
			else if (jediNames[printCount].getVowels() == Person.getMostVowels()){
				System.out.println(jediNames[printCount].getSithName());
			}
			else {
				System.out.println(jediNames[printCount].getJediName());
			}

		}



	}

}
