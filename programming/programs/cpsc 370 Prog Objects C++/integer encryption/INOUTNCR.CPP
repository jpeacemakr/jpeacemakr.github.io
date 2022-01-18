
//title:integer encryption
//author:james peacemaker
//class: 370
//e-mail adress:jpeac1ij@mwc.edu
//language:C++
//purpose:the purpose of this program is to encrypt a series of 4 digit
//		integers that are supposed to be transferred over phone lines. The
//		integers to be encrypted are in a file called 'datain_1'. The output
//		of the encrypted integers is going into a file called 'datout_1'.
//description: The integers are to be read from the file. They are then
//		converted into 4 seperate digits. The digits will be equal to:
//		((the digit +7)modulus 10). Then the first and third digit will be
//		swapped. Then the second and fourth digits will be swapped. The digits
//		will then be output to the output file.

#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>



void main (void)
{//begin main
	int number=1;//the original integer that is read in from the input file
	int temp;//used to temporarily hold a value in order to swap two numbers
	int thousandsdigit;//holds the digit in the thousands place
	int hundredsdigit;//holds the digit in the hundreds place
	int tensdigit;//holds the digit in the tens place
	int onesdigit;//holds the digit in the ones place

	ifstream infile("datain_1");//input file
	ofstream outfile ("datout_1");//output file

	//handshake
	cout<<"\n\nThis program is designed to encrypt information before it\n";
	cout<<"is sent over phone lines. The information should be organized\n";
	cout<<"beforehand as a series of four digit integers. The integers\n";
	cout<<"should be placed in the file 'datain_1' so that the program can\n";
	cout<<"read from. The output file is named 'datout_1'.\n\n";
	cout<<"  Press RETURN to continue.";
	cin.get();
	cout<<"\n\n";

while(!infile.eof())
	{
	infile>>number;

	//get the digits from the integer
	thousandsdigit=(number/1000);
	hundredsdigit=((number%1000)/100);
	tensdigit=((number%100)/10);
	onesdigit=(number%10);

	//add 7 to each digit and chop off the 1 if it is carried
	thousandsdigit=((thousandsdigit+7)%10);
	hundredsdigit=((hundredsdigit+7)%10);
	tensdigit=((tensdigit+7)%10);
	onesdigit=((onesdigit+7)%10);

	//swap first and third digits
	temp=thousandsdigit;
	thousandsdigit=tensdigit;
	tensdigit=temp;

	//swap second and fourth digits
	temp=hundredsdigit;
	hundredsdigit=onesdigit;
	onesdigit=temp;

	//number=(thousandsdigit*1000)+(hundredsdigit*100)+(tensdigit*10)+onesdigit;

	cout<<"\nThe number after encryption is: ";
	cout<<thousandsdigit<<hundredsdigit<<tensdigit<<onesdigit;
	outfile<<thousandsdigit<<hundredsdigit<<tensdigit<<onesdigit<<"\n";
	}
	cout<<"\n\nThank you for using this encryption program";

}//end main




