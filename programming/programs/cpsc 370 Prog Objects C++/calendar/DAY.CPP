////////////////////////////////////////////////////////////////////////////
//title:war.cpp
//author:james peacemaker
//class:CPSC 370
//e-mail adress:jpeac1ij@mwc.edu
//language:C++
//purpose:the purpose of this program is to do calendar calculations.
/*description:*/
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip.h>
#include "calender.h"


int main (void)
	{//begin main
	char selection;
	date day;
	date day2;
	//handshake

	int contin=1;
	int month;
	int daym;
	int year;
	int num;
	while (contin==1)
		{
		//display menu
		cout<<"\n (1) Enter a date\n";
		cout<<" (2) Add a given number of days to a date\n";
		cout<<" (3) Subtract a given number of days from a date\n";
		cout<<" (4) Subtract two dates, the original and a new date\n";
		cout<<" (5) Find the next day\n";
		cout<<" (6) Compare two dates\n";
		cout<<" (7) Find the day of the week\n";
		cout<<" (8) Quit\n\n";
		cout<<"Enter a selection from the menu: ";
		cin>>selection;
      cout<<"\n";
		if (selection=='1')
			{
			cout<<"Enter the date: ";
			cin>>month>>daym>>year;
			day.setdate(month, daym, year);
			}
		else if (selection=='2')
			{
			cout<<"Enter the number of days to advance: ";
			cin>>num;
			day.adddays(day,num);
			day.display();
			}
		else if (selection=='3')
			{
			cout<<"Enter the number of days to go back: ";
			cin>>num;
			day.subtractdays(day,num);
			day.display();
			}
		else if (selection=='4')
			{
			cout<<"Enter the first date: ";
			cin>>month>>daym>>year;
			day.setdate(month, daym, year);
			cout<<"Enter the first date: ";
			cin>>month>>daym>>year;
			day2.setdate(month, daym, year);
			num=day.subtract2dates(day, day2);
			cout<<"/nThe difference between the two dates is ";
			cout<<num<<" days.";
			}
		else if (selection=='5')
			{
			day.nextday(day);
			day.display();
			}

		else if (selection=='6')//compare two dates
			{
			cout<<"Enter the first date: ";
			cin>>month>>daym>>year;
			day.setdate(month, daym, year);
			cout<<"Enter the first date: ";
			cin>>month>>daym>>year;
			day2.setdate(month, daym, year);
			if (day.compare2dates (day,day2)==1)
				{
				day2.display();
				cout<<" is before ";
				day.display();
				}
			else if (day.compare2dates (day,day2)==-1)
				{
				day.display();
				cout<<" is before ";
				day2.display();
				}
			 else if (day.compare2dates (day,day2)==0)
				{
				day.display();
				cout<<" is the same as ";
				day2.display();
				}
			}

		else if (selection=='7')//find the day of the week
			{
			num=day.dayofweek(day);
			switch (num)
				{
				case 0: cout<<"monday";break;
				case 1: cout<<"tuesday";break;
				case 2: cout<<"wednesday";break;
				case 3: cout<<"thursday";break;
				case 4: cout<<"friday";break;
				case 5: cout<<"saturday";break;
				case 6: cout<<"sunday";break;
				}
			}

		else if (selection=='8')
			{
			contin=0;
			}
		else
			{
			cout<<"You did not enter a valid selection.\n\n";
			}
		}
	return 0;
	}//end main
