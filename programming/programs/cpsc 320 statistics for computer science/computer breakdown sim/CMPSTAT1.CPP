////////////////////////////////////////////////////////////////////////////
//	title:cmpstats1.cpp
// author:james peacemaker
// class:CPSC 320
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose:this program is designed to simulate the results of a computer
// 	system. The program accepts the random number seed and the number of
//		days to be simulated. Various statics will be displayed at the end
//		of the run.
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <iomanip.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main (void)
	{//begin main
	int numdays;//number of days to simulate
	double breakdownprob;//prob. that the computer will breakdown
	long int users;//number of users for a day
	int breakdowns=0;//number of breakdowns
	int seed;//seed for the random number generator
	double hoursbroken;//number of hours broken in numdays
	double randomvar;//holds a random variable
	double randomnum;//holds a random variable
	double product;//used in the poisson random number generator
	double randbreakdowns;//holds thevariable that tells if it will breakdown
	long int totalusers=0;//total number of users
	int minor=0;//number of minor breakdowns
	int serious=0;//number of serious breakdowns
	int major=0;//number of major breakdowns

	cout<<"Enter the seed for the random number generator: ";
	cin>>seed;
	cout<<"\n";

	cout<<"Enter the number of days that you want to simulate: ";
	cin>>numdays;
	cout<<"\n\n";

	srand(seed); //set the seed

	for (int i=0; i<numdays; i++)
		{
		users=0;
		product=1;

		//generate a poissan random variable (avg.=20)
		while(product>powl((2.718281828),(-20)))
		//while (product > 0.0000000020611) e^(-20)
			{
			randomnum=(double(rand())/double(RAND_MAX));
			users=users+1;
			product=product*randomnum;
			}


		//cout<<"Day "<<(i+1)<<", users= "<<users<<endl;
		totalusers=totalusers+users;

		//decide what the prob. for breakdown is
		if (users<=10)
			{breakdownprob=0.1;}
		else if (users<=18)
			{breakdownprob=0.15;}
		else if (users <= 25)
			{breakdownprob=0.2;}
		else if (users <=30)
			{breakdownprob=0.25;}
		else
			{breakdownprob=0.3;}

		//given the breakdown probability, decide if it will breakdown
		randbreakdowns=(double(rand())/double(RAND_MAX));
		if (randbreakdowns<breakdownprob)
			{breakdowns=breakdowns+1;}
		}

	//display results of the simulation
	cout<<"\n\nThe total number of users was: "<<totalusers<<endl;
	cout<<"The average number of users per day was: "<<(float(totalusers)/float(numdays));

	cout<<"\n\nThe computer broke down with "<<(float(breakdowns)/float(totalusers)*100)<<"% of the users.\n";

	cout<<"The computer broke down ";
	cout<<breakdowns;
	cout<<" times, in ";
	cout<<numdays;
	cout<<" days.\n";
	cout<<"The computer went down an average of ";
	cout<<(float(breakdowns)/float(numdays));
	cout<<" times per day.\n\n";
	hoursbroken=0.0;

	//decide the seriousness of the breakdowns
	for (int j=0; j<breakdowns; j++)
		{
		//generate random variable 1..4
		randomvar= rand()%4+1;
		if ((randomvar == 1)||(randomvar ==2))//minor breakdown
			{
			hoursbroken=hoursbroken+0.5;
			minor++;
			}
		else if (randomvar == 3)//serious breakdown
			{
			hoursbroken=hoursbroken+5.0;
			serious++;
			}
		else if (randomvar == 4)//major breakdown
			{
			hoursbroken=hoursbroken+48.0;
			major++;
			}
		}

	//display more results
	cout<<"The computer was down ";
	cout<<hoursbroken;
	cout<<" hours, in ";
	cout<<numdays;
	cout<<" days.\n";

	cout<<"The computer was down an average of ";
	cout<<(float(hoursbroken)/float(numdays));
	cout<<" hours per day.\n";

	cout<<"The computer was down an average of ";
	cout<<((float(hoursbroken)/float(numdays)/24.0)*100);
	cout<<"% of the time.\n";

	cout<<"\nThe computer had a minor problem "<<minor<<" times.\n";
	cout<<"Minor problems caused the computer to be down for "<<(minor*0.5)<<" hours\n";
	cout<<"( "<<(double(minor)/double(breakdowns)*100) <<"% of the times that it failed.)\n\n";

	cout<<"The computer had a serious problem "<<serious<<" times. \n";
	cout<<"Serious problems caused the computer to be down for "<<(serious*5.0)<<" hours\n";
	cout<<"( "<<(double(serious)/double(breakdowns)*100) <<"% of the times that it failed.)\n\n";

	cout<<"The computer had a major or problem "<<major<<" times. \n";
	cout<<"Major problems caused the computer to be down for "<<(major*48.0)<<" hours\n";
	cout<<"( "<<(double(major)/double(breakdowns)*100) <<"% of the times that it failed.)\n\n";

	cout<<"When the computer did go down, it was down for an average of ";
	cout<<(hoursbroken/breakdowns)<<" hours.\n\n";

	return 1;





	}
