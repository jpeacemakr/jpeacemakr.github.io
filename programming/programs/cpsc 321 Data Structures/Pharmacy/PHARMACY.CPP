
////////////////////////////////////////////////////////////////////////////
//	title:pharmacy.cpp
// author:james peacemaker
// class:CPSC 321
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose:this program is designed to simulate a pharmacy.
//a queue is emplemented to hold the customer information nodes.
//a stack is implemented to hold integer values for ingredients of the prescription.
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <iomanip.h>
#include <string.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

//this structure is the node type for the customer list
struct customernode
	{
	char name[50];         //holds the name of the customer
	char prescription[50]; //holds the name of the prescription
	int numofingredients;  //holds the number of ingredients in the prescription
	};

//friend functions


//printdata:
//purpose: this friend function is used by the print function in order to
//print a node in the customer queue
void printdata (customernode customer)
	{
	cout<<"\nCustomer's name: ";
	cout<<customer.name<<endl;
	cout<<"Prescription: ";
	cout<<customer.prescription<<endl;
	cout<<"Number of Ingredients: ";
	cout<<customer.numofingredients<<endl;
	cout<<"Course Name: ";
	cout<<"\n";
	}


//printdata:
//purpose: this friend function is used by the print function in order to
//print a node in the ingredient stack
void printdata (int ingred) //print student in a roster
	{
	cout<<ingred<<" ";;
	}


//printdata:
//purpose this friend function is used by the print function in order to
//print a node in the customer queue to a specific file
void printdata (customernode customer, ofstream &outfile) //print course in a courselist
	{
	outfile<<"\nCustomer's name: ";
	outfile<<customer.name<<endl;
	outfile<<"Prescription: ";
	outfile<<customer.prescription<<endl;
	outfile<<"Number of Ingredients: ";
	outfile<<customer.numofingredients<<endl;
	outfile<<"Course Name: ";
	outfile<<"\n";
	}


//printdata:
//purpose this friend function is used by the print function in order to
//print a node in the ingredient stack to a specific file
void printdata (int ingred, ofstream &outfile) //print student in a roster
	{
	outfile<<ingred<<" ";
	}


//compare: NOT USED AND SERVES NO PURPOSE
//purpose: friend function insert compare for customers
//used by the search function to find where to insert a student
//returns 1(true) or 0(false)
int compare(const customernode temp, const customernode insertednode)
	{
	if(strcmp(temp.name,insertednode.name)>0)
		{
		return 0;
		}
	else
		{
		return 1;
		}
	}





//compare: NOT USED AND SERVES NO PURPOSE
//purpose: friend function to compare ingredients
//used by the search function to find a student
//returns 1(true) or 0(false)
int compare(const int temp, const int key)
	{
	if (temp<key)
		return 0;
	else
		return 1;
	}


//validatefriend: NOT USED AND SERVES NO PURPOSE
//purpose: this friend checks to see if a customer node is valid
//returns a 1(true) or 0(false)
int validatefriend(customernode &temp)
	{
	if (temp.prescription!="t")
		return 1;
	else return 0;
	}


//validatefriend: NOT USED AND SERVES NO PURPOSE
//purpose: this friend checks to see if a ingredientnode node is valid
//returns a 1(true) or 0(false)
//this function is not used in this program, but needed for compilation
int validatefriend(int &temp)
	{
	if (temp/=0)
		return 1;
	else return 0;
	}




int main (void)
	{//begin main
	int ingredient;//the ingredient to be added to the stack
	int num;//the number of ingredients to be added to the stack
	stack <int> ingredientstack;//the ingredient stack, each ingredient is an integer
	queue <customernode> customerqueue;//the customer queue
	customernode newcustomer;//newcustomer to be added to the queue
	customernode tempcustomer;//holds the value of the customer being serviced
	char choice;//the menu choice
	cout<< "Welcome to the Pharmacy.\n\n";
	int done=0; //whether or not it is time to exit
	while (done==0)
		{
		//display menu
		cout<<"\n\nPlease make a selection from the menu below.\n\n";
		cout<<"1). Add a customer.\n";
		cout<<"2). Service a Customer.\n";
		cout<<"3). Enter Ingredients.\n";
		cout<<"4). Mix Ingredients.\n";
		cout<<"5). Exit.\n\n";
		cout<<"Enter your selection: ";
		cin>>choice;

		if (choice =='1')//Add a customer
			{
			cout<<"\nEnter the customer's name: ";
			cin.ignore(1);
			cin.getline(newcustomer.name,50);
			cout<<"Enter the prescription: ";
			cin.getline(newcustomer.prescription,50);
			newcustomer.numofingredients=0;
			customerqueue.enqueue(newcustomer);
			}

		else if (choice =='2')//Service customer
			{
			if (customerqueue.queueisempty())//customers are not waiting
				{
				cout<<"There are no customers to be serviced.\n\n";
				}
			else                             //customers are waiting
				{
				if (tempcustomer.numofingredients==0)//the customer being serviced is not done
					{
					cout<<"\nOnly one customer can be serviced at a time.\n";
					}
				else                            //the next customer can be served
					{
					if (ingredientstack.stackisempty())
						{
						customerqueue.dequeue(tempcustomer);
						cout<<"\n"<<tempcustomer.name;
						cout<<" ordered ";
						cout<<tempcustomer.prescription;
						cout<<" and is ready to be serviced.\n";
						}
					else  //the customer being served has not had their ingredients mixed yet
						{
						cout<<"\nThe customer cannot be serviced while another\n";
						cout<<"customer is being serviced. The perscription\n";
						cout<<"stack must be emptied and mixed.\n\n";
						}
					}
				}
			}

		else if (choice =='3')//Enter Ingredients
			{
			if (tempcustomer.numofingredients==0)//tempcustomer has not been served yet
				{
				if (ingredientstack.stackisempty())//tempcustomer needs to be served
					{
					if (strcmp(tempcustomer.prescription, "Data Structures Headaches")==0)
						{num=4;}
					else if (strcmp(tempcustomer.prescription, "Programming Stomach Pains")==0)
						{num=3;}
					else if (strcmp(tempcustomer.prescription, "Super Power Programmer")==0)
						{num=1;}
					else if (strcmp(tempcustomer.prescription, "Soar Elbow")==0)
						{num=6;}
					else if (strcmp(tempcustomer.prescription, "Eye Strainer")==0)
						{num=5;}
					else
						{
						num=0;
						while (num <=0)
							{
							cout<<tempcustomer.prescription<<" is not recognized.\n";
							cout<<"\nHow many ingredients do you wish to mix: ";
							cin>>num;
							if (num<=0)
								cout<<"\nThe number of ingredients must greater than 0.\n";
							}
						}
					tempcustomer.numofingredients=num;
					cout<<"\nEnter the "<<num<<" ingredients: ";
					for (int i=0; i<num; i++)
						{
						cin>>ingredient;
						ingredientstack.push(ingredient);
						}
					}
				else //ingredients stack is already full
					{
					cout<<"\nThe perscription stack already contains ingredients\n";
					cout<<"that must be mixed. Please mix them before entering\n";
					cout<<"more ingredients to the stack.\n";
					}
				}
			else  //customer already has ingredients
				{
				cout<<"\nYou cannot enter ingredients until the customer is serviced.\n";
				}
			}

		else if (choice =='4')//Mix Ingredients
			{
			if (ingredientstack.stackisempty())//can't mix an empty stack
				{
				cout<<"There are no ingredients to mix.\n";
				}
			else //it's time to mix the ingredients
				{
				while (!ingredientstack.stackisempty())
					{
					ingredientstack.pop(ingredient);
					cout<<"\nIngredient Mix "<<ingredient;
					}
				}
			}

		else if (choice =='5')//exit
			{
			if (ingredientstack.stackisempty())//stack has ingredients, cannot exit
				{
				cout<<"The stack of ingredients is not empty.\n";
				cout<<"You cannot exit yet.\n";
				}
			else if (customerqueue.queueisempty())//queue is not empty, cannot exit
				{
				cout<<"The queue of customers is not empty.\n";
				cout<<"You cannot exit yet.\n";
				}
			else   //stack and queue are both empty
				{
				cout<<"Thank you for a hard days work.\n";
				cout<<"No customers are left. You can go home.\n";
				done=1;
				}
			}
		else  //repeat loop because invalid menu choice
			{
			cout<<"You did not enter a valid choice of the menu.\n\n";
			}
		}
	return 0;
	}//end main


