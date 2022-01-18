class Person {

	
static int mostVowels = 0; //stores the highest number of vowels

String firstName;//person's first name
String lastName;//person's last name
String momMaidenName;//mother's maiden name
String birthCity;//the city in which they were born

String jediFirstName;//the jedi first name
String jediLastName;//the jedi last name
String jediName;//the combined jedi name

String sithLastName;//the Sith last name
String sithName;//the full sith name

int vowels;//the total number of vowels combined in their first and last name



//constructor method
Person() {
	this.vowels = 0;
}


//name setters
void setFirstName(String firstNameValue) {
	this.firstName = firstNameValue;
}

void setLastName(String lastNameValue) {
	this.lastName = lastNameValue;
}

void setMomMaidenName(String momMaidenNameValue) {
	this.momMaidenName = momMaidenNameValue;
}

void setBirthCity(String birthCityValue) {
	this.birthCity = birthCityValue;
}


//name getters (not used in final version of this example but used for debugging and potential for future use)
String getFirstName() {
	return this.firstName;
}

String getLastName() {
	return this.lastName;
}

String getMomMaidenName() {
	return this.momMaidenName;
}

String getBirthCity() {
	return this.birthCity;
}


//vowel counter. it returns the combined number of vowels found in the first and last name.
void setVowels() {
	this.vowels = 0;
	
	//count vowels in first name
	for (int i=0; i<this.firstName.length(); i++){
		if (this.firstName.charAt(i)=='a'||this.firstName.charAt(i)=='A'||this.firstName.charAt(i)=='e'||this.firstName.charAt(i)=='E'||this.firstName.charAt(i)=='i'||this.firstName.charAt(i)=='I'||this.firstName.charAt(i)=='o'||this.firstName.charAt(i)=='O'||this.firstName.charAt(i)=='u'||this.firstName.charAt(i)=='U'){ 
			this.vowels++;	
		}
	}

	//count vowels in last name
	for (int i=0; i<this.lastName.length(); i++){
		if (this.lastName.charAt(i)=='a'||this.lastName.charAt(i)=='A'||this.lastName.charAt(i)=='e'||this.lastName.charAt(i)=='E'||this.lastName.charAt(i)=='i'||this.lastName.charAt(i)=='I'||this.lastName.charAt(i)=='o'||this.lastName.charAt(i)=='O'||this.lastName.charAt(i)=='u'||this.lastName.charAt(i)=='U'){ 
			this.vowels++;	
		}
	}

	//set most vowels to the new higher number if this person has more
	if (this.vowels>Person.mostVowels){
		Person.mostVowels=this.vowels;
	}
}




//return the number of vowels in the name
int getVowels(){
	return this.vowels;
}


//returns the highest number of vowels in the combined first and last name
static int getMostVowels(){
	return Person.mostVowels;
}


//create and return Jedi Name
String getJediName(){
	//create Jedi first name by combining first three letters of first name and two first letters of last name
	this.jediFirstName = this.firstName.substring(0,1).toUpperCase() + this.firstName.substring(1,3).toLowerCase() + this.lastName.substring(0,2).toLowerCase();
	//create Jedi last name by combing first three letters of mom's maiden name and first two letters of birth city
	this.jediLastName = this.momMaidenName.substring(0,1).toUpperCase() + this.momMaidenName.substring(1,3).toLowerCase() + this.birthCity.substring(0,2).toLowerCase();
	//combine Jedi first name and Jedi last name
	this.jediName = this.jediFirstName + " " + this.jediLastName;
	return this.jediName;
}



//create and return Sith name
String getSithName(){
	//Create Sith name by combining Darth and the first three lettters of the first name and first two letters of the last name
	this.sithLastName = this.firstName.substring(0,1).toUpperCase() + this.firstName.substring(1,3).toLowerCase() + this.lastName.substring(0,2).toLowerCase();
	this.sithName = "Darth " + sithLastName; 
	return this.sithName;
}












}
