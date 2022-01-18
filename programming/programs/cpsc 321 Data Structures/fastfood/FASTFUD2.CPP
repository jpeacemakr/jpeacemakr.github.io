
////////////////////////////////////////////////////////////////////////////
//title:fastfood.cpp
//author:james peacemaker
//class:CPSC 321
//e-mail adress:jpeac1ij@mwc.edu
//language:C++
//purpose:
//description:
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <iomanip.h>

int main (void)
{//begin main

double dailyhamburger=0.0;
double dailychicken=0.0;
double dailysoda=0.0;
double dailyfries=0.0;
double dailytotal=0.0;
double dailyorders=0.0;
double customersubtotal=0;
double total=0;
double hamburgercost=0.0;
double chickencost=0.0;
double sodacost=0.0;
double friescost=0.0;
double payment=0.0;
double change=0.0;
double priceperhamburger =0.99;
double priceperchicken =1.56;
double pricepersoda =0.99;
double priceperfries =1.07;
double salestax =0.045;
int num=0;
int hamburgernum=0;
int chickennum=0;
int sodanum=0;
int friesnum=0;
char choice='0';
char selection='0';


while (selection !='6')
	{
	choice='0';
	selection='0';
	//showmenu();
	cout<<"Welcome to Fastfood Express.\n\n";
	cout<<"Please Enter a selection from the menu below.\n\n";
	cout<<"  1). Place an order.\n";
	cout<<"  2). Remove an item from the order.\n";
	cout<<"  3). Print out total.\n";
	cout<<"  4). Cancel the order.\n";
	cout<<"  5). Show daily totals.\n";
	cout<<"  6). Exit.\n\n";
	cout<<"Enter a selection:";
	cin>>selection;
	cout<<"\n \n";
	switch (selection)
	{
	case('1')://place an order
		{
		while (choice != '5')
			{
			cout<<"Enter the number of the item you wish to order.\n\n";
			cout<<"  1). hamburger.............$"<<priceperhamburger <<"\n";
			cout<<"  2). chicken...............$"<<priceperchicken <<"\n";
			cout<<"  3). soda..................$"<<pricepersoda<<"\n";
			cout<<"  4). fries.................$"<<priceperfries <<"\n";
			cout<<"  5). return to main menu.\n\n";
			cout<<"Enter your choice: ";
			cin>>choice;
			cout<<"\n\n";
			if (choice=='1')
				{
				hamburgercost = 0.0;
				cout<<"How many hamburgers do you wish to order?: ";
				cin>>num;
				cout<<"\n\n";
				hamburgernum = hamburgernum + num;
				dailyhamburger = dailyhamburger + num;
				hamburgercost=(priceperhamburger*double(num));
				customersubtotal=(customersubtotal+hamburgercost);
				cout<<"You have ordered "<<num << " hamburger(s) for $";
				cout.setf(ios::showpoint|ios::fixed);
				cout<<setprecision(2)<< hamburgercost;
				cout<<"\n\n";               //setioflags(ios::fixed|ios::showpoint)<<
				}
			if (choice=='2')
				{
				chickencost = 0.0;
				cout<<"How many chicken sandwiches do you wish to order?: ";
				cin>>num;
				cout<<"\n\n";
				chickennum = chickennum + num;
				dailychicken = dailychicken + num;
				chickencost=(priceperchicken*double(num));
				customersubtotal=(customersubtotal+chickencost);
				cout<<"You have ordered "<<num << " chicken sandwich(es) for $"<< chickencost;
				cout<<"\n\n";
				}
			if (choice=='3')
				{
				sodacost = 0.0;
				cout<<"How many sodas do you wish to order?: ";
				cin>>num;
				cout<<"\n\n";
				sodanum = sodanum + num;
				dailysoda = dailysoda + num;
				sodacost=(pricepersoda*double(num));
				customersubtotal=(customersubtotal+sodacost);
				cout<<"You have ordered "<<num << " soda(s) for $"<< sodacost;
				cout<<"\n\n";
				}
			if (choice=='4')
				{
				friescost = 0.0;
				cout<<"How many orders of fries do you wish to order?: ";
				cin>>num;
				cout<<"\n\n";
				friesnum = friesnum + num;
				dailyfries = dailyfries + num;
				friescost=(priceperfries*double(num));
				customersubtotal=(customersubtotal+friescost);
				cout<<"You have ordered "<<num << " order(s) of fries for $"<< friescost;
				cout<<"\n\n";
				}
			if (choice=='5')
				{
				//exit the loop
				}
			}
		break;
		}
	case('2')://remove from the order
		{
		while (choice != '5')
			{
			cout<<"Enter the number of the item you wish to remove.\n\n";
			cout<<"  1). hamburger.............$"<<priceperhamburger <<"\n";
			cout<<"  2). chicken sandwich......$"<<priceperchicken <<"\n";
			cout<<"  3). soda..................$"<<pricepersoda <<"\n";
			cout<<"  4). fries.................$"<<priceperfries <<"\n";
			cout<<"  5). return to main menu.\n\n";
			cout<<"Enter your choice: ";
			cin>>choice;
			cout<<"\n\n";
			if (choice=='1')
				{
				cout<<"How many hamburgers do you wish to remove?: ";
				cin>>num;
				cout<<"\n\n";
				if (num > hamburgernum)
					{
					cout<<"You cannot remove "<<num<<" hamburgers.\n";
					cout<<"You have only ordered "<<hamburgernum<<" hamburgers.\n";
					}
				if (num <= hamburgernum)
					{
					hamburgernum=hamburgernum - num;
					dailyhamburger = dailyhamburger - num;
					hamburgercost=(priceperhamburger*double(num));
					customersubtotal=(customersubtotal-hamburgercost);
					cout<<"You have removed "<<num << " hamburger(s) for $"<< hamburgercost;
					cout<<"\n\n";
					}
				}
			if (choice=='2')
				{
				cout<<"How many chicken sandwhiches do you wish to remove?: ";
				cin>>num;
				cout<<"\n\n";
				if (num > chickennum)
					{
					cout<<"You cannot remove "<<num<<" chicken sandwiches.\n";
					cout<<"You have only ordered "<<chickennum<<" chicken sandwiches.\n";
					}
				if (num <= chickennum)
					{
					chickennum=chickennum - num;
					dailychicken = dailychicken - num;
					chickencost=(priceperchicken*double(num));
					customersubtotal=(customersubtotal-chickencost);
					cout<<"You have removed "<<num << " chicken sandwich(es) for $"<< hamburgercost;
					cout<<"\n\n";
					}
				}
			if (choice=='3')
				{
				cout<<"How many sodas do you wish to remove?: ";
				cin>>num;
				cout<<"\n\n";
				if (num > sodanum)
					{
					cout<<"You cannot remove "<<num<<" sodas.\n";
					cout<<"You have only ordered "<<sodanum<<" sodas.\n";
					}
				if (num <= sodanum)
					{
					sodanum=sodanum - num;
					dailysoda = dailysoda - num;
					sodacost=(pricepersoda*double(num));
					customersubtotal=(customersubtotal-sodacost);
					cout<<"You have removed "<<num << " soda(s) for $"<< sodacost;
					cout<<"\n\n";
					}
				}
			if (choice=='4')
				{
				cout<<"How many orders of fries do you wish to remove?: ";
				cin>>num;
				cout<<"\n\n";
				if (num > friesnum)
					{
					cout<<"You cannot remove "<<num<<" orders of fries.\n";
					cout<<"You have only ordered "<<friesnum<<" orders of fries.\n";
					}
				if (num <= friesnum)
					{
					friesnum = friesnum -num;
					dailyfries = dailyfries - num;
					friescost=(priceperfries*double(num));
					customersubtotal=(customersubtotal-friescost);
					cout<<"You have removed "<<num << " order(s) of fries for $"<< hamburgercost;
					cout<<"\n\n";
					}
				}
			if (choice=='5')
				{
				//exit the loop
				cout<< "Return to the main menu.";
				cout<<"\n\n";
				}
			}
		break;
		}
	case('3'): //total the order
		{
		cout<< "You have ordered:\n\n";
		if (hamburgernum > 0)
			{
			cout<<hamburgernum<< " hamburger(s) ($"<<priceperhamburger<<" each).............$"<<(priceperhamburger*double(hamburgernum));
			cout<<"\n";
			}
		if (chickennum > 0)
			{
			cout<<chickennum<< " chicken sandwich(es) ($"<<priceperchicken<<" each).....$"<<(priceperchicken*double(chickennum));
			cout<<"\n";
			}
		if (sodanum > 0)
			{
			cout<<sodanum<< " sodas(s) ($"<<pricepersoda<<" each).................$"<<(pricepersoda*double(sodanum));
			cout<<"\n";
			}
		if (friesnum > 0)
			{
			cout<<friesnum<< " order(s) of fries ($"<<priceperfries<<" each)........$"<<(priceperfries*double(friesnum));
			cout<<"\n\n";
			}
		cout<<"subtotal..........................$"<<((priceperhamburger*double(hamburgernum))+(priceperchicken*double(chickennum))+(pricepersoda*double(sodanum))+(priceperfries*double(friesnum)));
		cout<<"\n";
		cout<<"tax...............................$"<<(customersubtotal*salestax);
		cout<<"\n";
		cout<<"total.............................$"<<(customersubtotal*(1.0+salestax));
		cout<<"\n\n";
		cout<<"Please enter the payment amount: $";
		cin>>payment;
		cout<<"\n";
		total=(customersubtotal*(1.0+salestax));
		if (payment < total)
			{
			cout<<"Your total is more than $"<<payment;
			cout<<"\nYour total is $"<<total;
			cout<<"\n\nPress RETURN to acknowledge.\n";
			cin.get();
			}
		if (payment >= total)
			{
			dailytotal=dailytotal + total;
			dailyorders++;
			change = (payment - total);
			cout<<"Your change is: $"<<change<<"\n";
			cout<<"Have a nice day. Please come again.\n\n";
			customersubtotal=0;
			total=0;
			hamburgercost=0.0;
			chickencost=0.0;
			sodacost=0.0;
			friescost=0.0;
			payment=0.0;
			change=0.0;
			num=0;
			hamburgernum=0;
			chickennum=0;
			sodanum=0;
			friesnum=0;
			choice='0';
			selection='0';
			}
		break;
		}
	case('4'): //cancel the order
		{
		cout<<"Your order has been canceled.\n";
		customersubtotal=0;
		total=0;
		hamburgercost=0.0;
		chickencost=0.0;
		sodacost=0.0;
		friescost=0.0;
		payment=0.0;
		change=0.0;
		num=0;
		hamburgernum=0;
		chickennum=0;
		sodanum=0;
		friesnum=0;
		choice='0';
		selection='0';
		break;
		}
	case('5'): //show daily totals
		{
		cout<<"The daily totals are:\n\n";
		cout<<"The number of hamburgers sold..............."<<dailyhamburger;
		cout<<"\nThe number of chicken sandwiches sold......."<<dailychicken;
		cout<<"\nThe number of sodas sold...................."<<dailysoda;
		cout<<"\nThe number of orders of fries sold.........."<<dailyfries;
		cout<<"\n\nThe total number of customers..............."<<dailyorders;
		cout<<"\n\nThe total sales for today are...............$"<<dailytotal;
		cout<<"\n\n";
		break;
		}
	case ('6'): //exit
		{
		cout<<"The daily totals are:\n\n";
		cout<<"The number of hamburgers sold..............."<<dailyhamburger;
		cout<<"\nThe number of chicken sandwiches sold......."<<dailychicken;
		cout<<"\nThe number of sodas sold...................."<<dailysoda;
		cout<<"\nThe number of orders of fries sold.........."<<dailyfries;
		cout<<"\n\nThe total number of customers..............."<<dailyorders;
		cout<<"\n\nThe total sales for today are...............$"<<dailytotal;
      cout<<"\n\nThank you for patronizing Fastfood Express.";

		break;
		}
	}
	}
return 0;
}//end main




