////////////////////////////////////////////////////////////////////////////
//	title:savings.h
// author:james peacemaker
// class:CPSC 370
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose: This class inherits the properties of the account class
//	and is specifically used for savings accounts. interest is
//	added to the account the longer it exists.
////////////////////////////////////////////////////////////////////////////

class savings: public account

	{
	public:
		//default constructor
		savings()
			{
			strcpy(name, "");
			currentbalance = 0.0;
			lasttransaction.setdate(0,0,0);
			interest=0.0;
			};

		//initializes the savings account
		void initialize(char *name1, int month1, int day1 , int year1)
			{
			strncpy(name, name1, 49);
			currentbalance = 0.0;
			lasttransaction.setdate(month1,day1,year1);
			interest=0.0;
			};

		//savingsdestructor
		~savings(){};

		//withdraws money from the savings account
		void withdraw(double tobesubtracted, int month1, int day1, int year1)
			 {
			 setlasttransaction(month1,day1,year1);
			 cout<<"\n"<<name<<"'s saving's account:";
			 cout<<"\n\nBalance before withdrawl  $"<<currentbalance;
			 cout<<"\nWithdrawl                 $-"<<tobesubtracted;
			 cout<<"\n-------------------------------";
			 currentbalance = currentbalance - tobesubtracted;
			 cout<<"\nFinal balance             $"<<currentbalance;
			 cout<<"\n\nTotal interest accrued: $"<<interest;
			 };

		//sets the last transaction date and modifies the account accordingly
		void setlasttransaction(int month1, int day1, int year1)
			 {
			 int dayspassed;
			 date temp(month1, day1, year1);
			 dayspassed = temp-lasttransaction;
			 double tempbalance= currentbalance;
			 if (currentbalance-0.0 > 0.0001)
				 currentbalance=(currentbalance*pow((1.0+(0.0375/365.0)),(365.0*(float(dayspassed)/365.0))));
			 lasttransaction.setdate(month1,day1,year1);
			 interest=interest+(currentbalance-tempbalance);
			 };

		//sets the amount of interest that the account has aquired
		void setinterest(double inter){interest=inter;};

		//returns the amount of interest
		double getinterest(){return interest;};

		//prints the savings account statistics
		void printaccount(int month1, int day1, int year1)
			{
			cout<<"\n\nName: ";
			cout<<name;
			cout<<"\nDate of last transaction: ";
			lasttransaction.display();
			setlasttransaction(month1,day1,year1);
			cout<<"Balance: $";
			cout<<currentbalance;
			cout<<"\nInterest accrued: $";
			cout<<interest;
			};

	private:
		long double interest;
	};
