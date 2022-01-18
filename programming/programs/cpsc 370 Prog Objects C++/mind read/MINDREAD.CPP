
//title:mindread.cpp
//author:james peacemaker
//class:cpsc 370
//e-mail adress:jpeac1ij@mwc.edu
//language:C++
//purpose:The purpose of this program is to use math in order to fool
//   someone into thinking that the program can read their mind.
//description:The program prompts the user for a four digit number.
//   The program multiplies that number by 9 to get a magic number.
//   The user selects a digit from this magic number and removes it.
//   With this new four digit number, the missing digit can be gotten by:
//   digit = (9 - (new four digit number moulus 9)).


#include <iostream.h>

unsigned int number = 1;//holds the original integer entered
unsigned int true = 0;//whether or not the value entered is good
unsigned int newnumber;//holds the value of ninenumber after a digit is removed
unsigned int tenthousandsdigit;//holds the tenthousands place digit of ninenumber
unsigned int thousandsdigit;//holds the thousands place digit of ninenumber
unsigned int hundredsdigit;//holds the hundreds place digit of ninenumber
unsigned int tensdigit;//holds the tens place digit of ninenumber
unsigned int onesdigit;//holds the ones place digit of ninenumber
unsigned int missingdigit;//holds the digit that the user removes from ninenumber
unsigned int ninenumber;//original number X nine
unsigned int rearrangednumber;//newnumber that has been rearranged by the user
unsigned int digit;//holds the digit that the user wants to remove from ninenumber

void main (void)
{//begin main
//handshake
cout<<"Welcome. This computer program can magically read your mind.\n\n";

//get the number between 9999 and 1001
while (number>9999||number<1001)
	{
	cout<<"Enter a number from 1001 to 9999: ";
	cin>>number;
	if (number>9999||number<1001)
		cout<<"\nThe number "<<number<<" is not between 1001 and 9999.\n";
	}

//get the magic number
ninenumber=number*9;
cout<<"\nThe number "<<number<<" will now be multiplied by 9 to make "<<ninenumber;


//convert ninenumber into individual digits
tenthousandsdigit=(ninenumber/10000);
thousandsdigit=((ninenumber%10000)/1000);
hundredsdigit=((ninenumber%1000)/100);
tensdigit=((ninenumber%100)/10);
onesdigit=(ninenumber%10);

//get the digit of ninenumber that the user wants to remove and calculate the new number
while (true==0)
	{
	cout<<"\nEnter a nonzero digit from the number "<<ninenumber<<": ";
	cin>>digit;
	if (digit == 0)
		cout<<"\nThe digit cannot equal zero.\n\n";
	else if (digit==tenthousandsdigit)
		{
		true=1;
		newnumber=(thousandsdigit*1000)+(hundredsdigit*100)+(tensdigit*10)+onesdigit;
		}
	else if (digit==thousandsdigit)
		{
		true=1;
		newnumber=(tenthousandsdigit*1000)+(hundredsdigit*100)+(tensdigit*10)+onesdigit;
		}
	else if (digit==hundredsdigit)
		{
		true=1;
		newnumber=(tenthousandsdigit*1000)+(thousandsdigit*100)+(tensdigit*10)+onesdigit;
		}
	else if (digit==tensdigit)
		{
		true=1;
		newnumber=(tenthousandsdigit*1000)+(thousandsdigit*100)+(hundredsdigit*10)+onesdigit;
		}
	else if (digit==onesdigit)
		{
		true=1;
		newnumber=(tenthousandsdigit*1000)+(thousandsdigit*100)+(hundredsdigit*10)+tensdigit;
		}
	else
		cout<<"You did not enter a digit from the number "<<ninenumber<<".\n\n";
	}

//get the rearranged number after the user rearranges newnumber
rearrangednumber= newnumber+1;
while((rearrangednumber%9)!=(newnumber%9))
	{
	cout<<"\nNow, rearrange the digits of the number "<<newnumber<<".\n";
	cout<<"Enter the rearranged number (don't put a zero first):";
	cin>>rearrangednumber;
	if ((rearrangednumber%9)!=(newnumber%9))
		cout<<"\nYou did not rearrange the letters correctly. Try again.\n";
	else
		{
		missingdigit =(9-(rearrangednumber %9));
		cout<<"\nThe missing number is: "<<missingdigit;
		}
	}
}//end main




