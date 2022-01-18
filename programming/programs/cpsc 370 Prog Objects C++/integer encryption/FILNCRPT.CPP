//title:
//author:james peacemaker
//class: 370
//e-mail adress:jpeac1ij@mwc.edu
//language:C++
//purpose:
//description:

#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>



void main (void)
{//begin main
	int number=1;
	int temp;
	int thousandsdigit;
	int hundredsdigit;
	int tensdigit;
	int onesdigit;
	ifstream infile("datain_1");

   cout<<"\n\nThis program is designed to encrypt information before it\n";
	cout<<"is sent over phone lines. The information should be organized\n";
	cout<<"beforehand as a series of four digit integers. The integers\n";
	cout<<"should be placed in a file that the program can read from.\n\n";
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

	number=(thousandsdigit*1000)+(hundredsdigit*100)+(tensdigit*10)+onesdigit;
	cout<<"\nThe number after encryption is: ";
	cout<<thousandsdigit<<hundredsdigit<<tensdigit<<onesdigit;
	}
	cout<<"\n\nThank you for using this encryption program";

}//end main




