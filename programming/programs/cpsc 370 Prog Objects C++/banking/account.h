////////////////////////////////////////////////////////////////////////////
//	title:account.h
// author:james peacemaker
// class:CPSC 370
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose:this class is used to maintain a type of bank account
////////////////////////////////////////////////////////////////////////////

#include "calops.h"
class account
	{
	public:
		//default constructor
		account()
			{
			strcpy(name, "");
			currentbalance = 0.0;
			lasttransaction.setdate(0,0,0);
			};


		//initializes account
		void initialize(char *name1, int month1, int day1 , int year1)
			{
			strncpy(name, name1, 49);
			currentbalance = 0.0;
			lasttransaction.setdate(month1,day1,year1);
			};

		//destructor
		~account()
			{

			};

		//used to setbalance to an amount (bal)
		void setbalance (double bal)
			{
			currentbalance = bal;
			};

		//used to set the name
		void setname (char *name1)
			{
			strncpy(name, name1, 49);
			};

		//used to set the date of the las transaction
		void setlasttransaction(int month1, int day1, int year1)
			{
			lasttransaction.setdate(month1,day1,year1);
			};

		//used to make a deposit ont he account
		void deposit(double tobeadded, int month1, int day1, int year1)
			{
			setlasttransaction(month1,day1,year1);
			currentbalance = currentbalance+ tobeadded;
			};

		//used to make a withdrawal on the account
		void withdraw(double tobesubtracted, int month1, int day1, int year1)
			{
			setlasttransaction(month1,day1,year1);
			currentbalance = currentbalance - tobesubtracted;
			};

		//return's the name
		char* getname()
			{
			return name;
			};

		//return's the balance
		double getbalance()
			{
			return currentbalance;
			};

		//return's the date
		date getdate()
			{
			return lasttransaction;
			};

		//displays the account statistics
		void printaccount(int month1, int day1, int year1)
			{
			cout<<"\n\nName: ";
			cout<<name;
			cout<<"\nDate of last transaction: ";
			lasttransaction.display();
			setlasttransaction(month1,day1,year1);
			cout<<"Balance: $";
			cout<<currentbalance;
			};

		//determines if the account has been set yet
		int isnull()
			{
			date temp(0,0,0);
			if (lasttransaction.compare2dates(lasttransaction,temp)==0)
				return 1;
			else return 0;
			};

	//private:
		char name[50];//holds the name of the account holder
		long double currentbalance;//amount of money in the bank
		date lasttransaction; //date of the last transaction
	}; //end struct account

