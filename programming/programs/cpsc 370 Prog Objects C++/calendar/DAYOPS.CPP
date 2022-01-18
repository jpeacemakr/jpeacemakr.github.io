////////////////////////////////////////////////////////////////////////////
//title:dayops.cpp
//author:james peacemaker
//class:CPSC 370
//e-mail adress:jpeac1ij@mwc.edu
//language:C++
//purpose:the purpose of this program is to simulate the card game of war.
/*description:This program is desined to be able to add or subtract a certain
 number of days from a certain date. It can compare two dates. It can
 Subtract two dates. It can also tell what day of the week a certain date
 falls on.*/
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip.h>
#include "calops.h"


int main (void)
	{//begin main
	char selection; //menu choice
	date day; //date number 1 used as the main date
	date day2; //date number 2 used for comparing and subtracting 2 dates

	//handshake
	cout<<"Welcome to the date manipulation program. This program\n";
	cout<<"is desined to be able to add or subtract a certain number\n";
	cout<<"of days from a certain date. It can compare two dates.\n";
	cout<<"It can Subtract two dates. It can also tell what day of\n";
	cout<<"the week a certain date falls on.\n";
	cout<<"Remember to Enter dates in the following format: Month Day Year";

	int contin=1; //1(true) to continue looping, 0(false) to exit
	int month; //holds value of the month
	int daym; //holds the value of the day
	int year; //holds the value of the year
	int num; //holds the number of days to advance or go back
	while (contin==1)
		{
		//display menu
		cout<<"\n\n (1) Enter a date\n";
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
		if (selection=='1') //enter a date
			{
			cout<<"Enter the date: ";
			cin>>month>>daym>>year;
			day.setdate(month, daym, year);
			}
		else if (selection=='2') //add days to a date
			{
			cout<<"Enter the number of days to advance: ";
			cin>>num;
			day=day+num; //day.adddays(day,num);
			day.display();
			}
		else if (selection=='3') //subtract days from a date
			{
			cout<<"Enter the number of days to go back: ";
			cin>>num;
			day=day-num; //day.subtractdays(day,num);
			day.display();
			}
		else if (selection=='4') //Subtract two dates
			{
			cout<<"Enter the first date: ";
			cin>>month>>daym>>year;
			day.setdate(month, daym, year);
			cout<<"Enter the first date: ";
			cin>>month>>daym>>year;
			day2.setdate(month, daym, year);
			num = day - day2; //num=day.subtract2dates(day, day2);
			cout<<"\nThe difference between the two dates is ";
			cout<<num<<" days.";
			}
		else if (selection=='5') //find the next day
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
				case 0: cout<<"sunday";break;
				case 1: cout<<"monday";break;
				case 2: cout<<"tuesday";break;
				case 3: cout<<"wednesday";break;
				case 4: cout<<"thursday";break;
				case 5: cout<<"friday";break;
				case 6: cout<<"saturday";break;

				}
			}

		else if (selection=='8') //exit
			{
			cout<<"\nThank you for using the date manipulation program.";
			contin=0; //continue = false
			}
		else
			{
			cout<<"You did not enter a valid selection.\n\n";
			}
		}
	return 0;
	}//end main
