////////////////////////////////////////////////////////////////////////////
//	title:bank.cpp
// author:james peacemaker
// class:CPSC 370
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose:This program simulates a bank. It has two parts.
//	One part simulates and maintains a checking account.
// The second simulates and maintains a savings account.
//a C++ driver program that displays a menu of options;
//	allows the user to select the desired option; performs the
//	selected operation and displays the results.
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <iomanip.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "account.h"
#include "savings.h"
#include "checking.h"

void main()
	{
	checking check[11];//an array of checking accounts
	savings save[11]; //an array of savingsaccounts
	char ch='a'; //the menu choice, set to something other than Q to begin
	char tempname[50];//holds the temp account holder's name
	int arraynum=0;//position in the array
	int month1;   //holds a temp month
	int day1;    //holds a temp day
	int year1;   //holds a temp year
	long double cash;//holds the amount of money to be withdrawn or deposited

	while (ch!='q'&&ch!='Q')
		{

		//main menu
		cout<<"\n\nSelect an option from the menu below.\n\n";
		cout<<"(S) Update a savings account\n";
		cout<<"(C) Update a checking account\n";
		cout<<"(Q) Quit\n\n";
		cout<<"Enter your selection: ";
		cin>>ch;

		if (ch=='s'||ch=='S')//update a savings account
			{
			//savings account menu
			cout<<"\n\nThe Savings Account Menu Options:\n\n";
			cout<<"(O)pen new account\n";
			cout<<"(D)eposit\n";
			cout<<"(W)ithdrawal\n";
		//interest update is done with
		//every action and displayed with (C)
			cout<<" Display (C)urrent balance\n\n";
			cout<<"Enter your selection: ";
			cin>>ch;

			if (ch=='o'||ch=='O')//open a new account
				{
				arraynum=0;

				//find the next empty space in the array
				while((save[arraynum].isnull()==0)&&(arraynum<=10))
					{
					arraynum++;
					}

				if (arraynum<=9)//if not full
					{
					cout<<"\nEnter the name: ";
					cin.ignore(1);
					cin.getline(tempname,50);
					//cout<<tempname;
					cout<<"\nEnter today's date: ";
					cin>>month1>>day1>>year1;
					save[arraynum].initialize(tempname, month1, day1, year1);
					save[arraynum].printaccount(month1, day1, year1);
					}
				else  //array is full
					cout<<"\nPerson cannot be added.\n\n";
				}

			else if (ch=='d'||ch=='D')//make a deposit
				{
				arraynum=0;
				cout<<"\nEnter the name: ";
				cin.ignore(1);
				cin.getline(tempname,50);

				//search for name match in the array
				while((strcmp(tempname,save[arraynum].name))!=0&&(arraynum<=10))
					{
					arraynum++;
					}

				if (arraynum<=9)//if found
					{
					cout<<"\nEnter today's date: ";
					cin>>month1>>day1>>year1;
					cout<<"\nHow much do you wish to deposit?: $";
					cin>>cash;
					save[arraynum].deposit(cash, month1, day1, year1);
					save[arraynum].printaccount(month1, day1, year1);
					}
				else //not found
					cout<<"\nPerson not found in list.\n\n";
				}
			else if (ch=='w'||ch=='W') //withdraw
				{
				arraynum=0;
				cout<<"\nEnter the name: ";
				cin.ignore(1);
				cin.getline(tempname,50);

				//search for name match in the save array
				while((strcmp(tempname,save[arraynum].name))!=0&&(arraynum<=10))
					{
					arraynum++;
					}

				if (arraynum<=9)//if found
					{
					cout<<"\nEnter today's date: ";
					cin>>month1>>day1>>year1;
					cout<<"\nHow much do you wish to withdrawl?: ";
					cin>>cash;
					save[arraynum].withdraw(cash, month1, day1, year1);
					save[arraynum].printaccount(month1, day1, year1);
					}
				else //not found
					cout<<"\nPerson not found in list.\n\n";
				}
			else if (ch=='c'||ch=='C') //display checking account
				{
				arraynum=0;
				cout<<"\nEnter the name: ";
				cin.ignore(1);
				cin.getline(tempname,50);

				//search for a name match in save the array
				while((strcmp(tempname,save[arraynum].name))!=0&&(arraynum<=10))
					{
					arraynum++;
					}

				if (arraynum<=9)//if found
					{
					cout<<"\nEnter today's date: ";
					cin>>month1>>day1>>year1;
					save[arraynum].printaccount(month1, day1, year1);
					}
				else  //not found
					cout<<"\nPerson not found in list.\n\n";
				}
			}

		else if ((ch=='c')||(ch=='C')) //checking account
			{
			//display checking account menu
			cout<<"\n\nThe Checking Account Menu Options:\n\n";
			cout<<"(O)pen new account\n";
			cout<<"(D)eposit\n";
			cout<<"(C)heck debit\n";
	 //monthly fee assesment is done with
	 //every action and displayed with (A)
			cout<<"Display (A)ccount\n";
			cout<<"Enter your selection: ";
			cin>>ch;

			if (ch=='o'||ch=='O')//open a checking account
				{
				arraynum=0;
				//search for next open space in the array
				while((!(check[arraynum].isnull()))&&(arraynum<=10))
					{
					arraynum++;
					}

				if (arraynum<=9)//if there is a space
					{
					cout<<"\nEnter the name: ";
					cin.ignore(1);
					cin.getline(tempname,50);
					//cout<<tempname;
					cout<<"\nEnter today's date: ";
					cin>>month1>>day1>>year1;
					check[arraynum].initialize(tempname, month1, day1, year1);
					check[arraynum].printaccount(month1, day1, year1);
					}
				else  //no spaces left
					cout<<"\nPerson cannot be added.\n\n";
				}

			else if (ch=='d'||ch=='D')//make a deposit
				{
				arraynum=0;
				cout<<"\nEnter the name: ";
				cin.ignore(1);
				cin.getline(tempname,50);

				//search the array for a name that matches
				while((strcmp(tempname,check[arraynum].name))!=0&&(arraynum<=10))
					{
					arraynum++;
					}

				if (arraynum<=9) //if name found
					{
					cout<<"\nEnter today's date: ";
					cin>>month1>>day1>>year1;
					cout<<"\nHow much do you wish to deposit?: ";
					cin>>cash;
					check[arraynum].deposit(cash, month1, day1, year1);
					check[arraynum].printaccount(month1, day1, year1);
					}
				else //name not found
					cout<<"\nPerson not found in list.\n\n";
				}

			else if (ch=='c'||ch=='C') //withdraw, check debit
				{
				arraynum=0;
				cout<<"\nEnter the name: ";
				cin.ignore(1);
				cin.getline(tempname,50);

				//search for the name in the list
				while((strcmp(tempname,check[arraynum].name))!=0&&(arraynum<=10))
					{
					arraynum++;
					}

				if (arraynum<=9)//if name found
					{
					cout<<"\nEnter today's date: ";
					cin>>month1>>day1>>year1;
					cout<<"\nHow much do you wish to withdrawl?: ";
					cin>>cash;
					check[arraynum].withdraw(cash, month1, day1, year1);
					check[arraynum].printaccount(month1, day1, year1);
					}
				else //name is not found
					cout<<"\nPerson not found in list.\n\n";
				}

			else if((ch=='a')||(ch=='A')) //display checking account
				{
				arraynum=0;
				cout<<"\nEnter the name: ";
				cin.ignore(1);
				cin.getline(tempname,50);

				//search for the name in the array
				while((strcmp(tempname,check[arraynum].name))!=0&&(arraynum<=10))
					{
					arraynum++;
					}

				if (arraynum<=9)//if name is found
					{
					cout<<"\nEnter today's date: ";
					cin>>month1>>day1>>year1;
					check[arraynum].printaccount(month1, day1, year1);
					}
				else  //name is not found
					cout<<"\nPerson not found in list.\n\n";
				}
			}
		else if (ch=='q'||ch=='Q') //quit
			{
			cout<<"\nThank you.\n";
			}
		else
			{
			cout<<"\nYour menu selection is invalid.\n";
			}
		}
	}







