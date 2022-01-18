////////////////////////////////////////////////////////////////////////////
//	title:checking.h
// author:james peacemaker
// class:CPSC 370
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose:This class inherits from the account class and is more
//	specifically designed for checking accounts
////////////////////////////////////////////////////////////////////////////

class checking: public account
	{
	public:

		//default constructor
		checking()
			{
			strcpy(name, "");
			currentbalance = 0.0;
			lasttransaction.setdate(0,0,0);
			feeamount=0.0;
			};

		//initializes the checking account
		void initialize(char *name1, int month1, int day1 , int year1)
			{
			strncpy(name, name1, 49);
			currentbalance = 0.0;
			lasttransaction.setdate(month1,day1,year1);
			feeamount=0.0;
			};

		//checking destructor
		~checking(){};

		//withdraws money from the checking account
		//$0.50 is taken out with every withdraw
		void withdraw(double tobesubtracted, int month1, int day1, int year1)
			 {
			 cout<<"\n"<<name<<"'s checking account:";
			 setlasttransaction(month1,day1,year1);
			 cout<<"\n\nBalance before withdrawl  $"<<currentbalance;
			 cout<<"\nWithdrawl                 $-"<<tobesubtracted;
			 cout<<"\nWithdrawl Fee             $-0.50";
			 cout<<"\n-------------------------------";
			 currentbalance = currentbalance - tobesubtracted;
			 currentbalance = currentbalance - 0.5;
			 feeamount = feeamount + 0.5;
			 cout<<"\nFinal balance             $"<<currentbalance;
			 if(currentbalance<0.0)
				{
				cout<<"\n\nOver-withdrawl fee        $-25.00";
				feeamount=feeamount+25.0;
				currentbalance=currentbalance-25.0;
				cout<<"\nFinal balance             $"<<currentbalance;
				}
			 cout<<"\n\nTotal fees accrued: $"<<feeamount;
			 };

		//sets the last transaction date
		//$2.00 is taken as service charge every month
		void setlasttransaction(int month1, int day1, int year1)
			 {
			 double tempbalance=currentbalance;
			 int dayspassed;
			 date temp(month1, day1, year1);
			 dayspassed= temp-lasttransaction;
			 currentbalance= currentbalance-(2.0*(dayspassed/30));
			 lasttransaction.setdate(month1,day1,year1);
			 feeamount=feeamount+(tempbalance-currentbalance);
			 };

		//sets the fee amount
		void setfeeamount(double fee){feeamount=fee;};

		//returns the fee amount
		double getfeeamount(){return feeamount;};

		//prints out the account stats
		void printaccount(int month1, int day1, int year1)
			{
			cout<<"\n\nName: ";
			cout<<name;
			cout<<"\nDate of last transaction: ";
			lasttransaction.display();
			setlasttransaction(month1,day1,year1);
			cout<<"Balance: $";
			cout<<currentbalance;
			cout<<"\nFees accrued: $";
			cout<<feeamount;
			};

	private:
		long double feeamount;//the amount of total fees
	};
