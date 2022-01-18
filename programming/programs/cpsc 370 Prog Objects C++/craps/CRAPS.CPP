

//title:craps
//author:james peacemaker
//class:CPSC 370
//e-mail adress:jpeac1ij@mwc.edu
//language:C++
//purpose:The purpose of this program is to simulate the game of craps.
//description:Two dice are rolled. If the the sum of the dice on the first
	//roll is equal to 7 or 11, then the player wins. If the sum
	//of dice on the first roll is equal to 2, 3, or 12, then the
	//player loses. In the case that the player rolls a 4, 5, 6, 8,
	//9, or 10, then that sum  becomes the "point". In order for
	//the player to win, then the player must roll the "point"
	//before they roll a 7. At the end of the game a table of wins/losses,
	//wagers, and balance.

#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>


struct gamerec //a record of a game
	{
	char outcome;//W for win, or L for loss.
	double wager;//the amount of money wagered.
	double balance;//balance after game
	};

gamerec record[500];//an array of game records




void handshake (void);
//purpose:The purpose of this function is to greet the user, and to supply
			//them with instructions if necessary
//preconditions:None
//postconditions:The User will be geeted, told that they are playing craps,
			//and displayed instructions if the user wants.
//exeptions:none



double getbalance (void);
//purpose:The purpose of this function is to promt the player for
//			how much money they want to start off with.
//preconditions:none
//postconditions:the variable corresponding to the balance will be established.
//exeptions:the computer must have enough memory to store the variable balance




double getwager (double balance);
//purpose:The purpose of this function is to promt the player for
//			the amount that they want to wager.
//preconditions:The variable balance must exist. Wager must be less than
//			balance and atleast 1 dollar.
//postconditions:The variable wager will have been established.
//exeptions:The variable balance must be of type integer, and there must be
//			enough memory to store the variable wager.




int rolldice (int numberofdice, int numberofsides);
//purpose:The purpose of this function is to roll a certain number of dice
//			(numberofdice). The dice have a certain number of sides
//			(numberofsides). The rolls are displayed to the screen and
//			the sum of the rolls is returned.
//preconditions:numberofdice and numberofsides must exist as integers.
//postconditions:the rolls are displayed to the screen, and the sum of the
//			rolls are returned.
//exeptions:the numberofsides and numberofdice need to be integers and there
//			must be enough memory to store rollsum.




double win (double balance, double wager, gamerec record[], int turn);
//purpose:the purpose of this the function is to store balance, wager,
//			and if the player won or not. The wager will be added to the
//			balance.
//preconditions:the array of gamerec (record) must exist whith atleast
//			the length of turn. Balance, wager, and turn must exist.
//postconditions:the gamerec in the array record at position turn will
//			have the information(wager, balance, W) input into it.
//exeptions:the array of gamerec(record) must exist. Balance, turn, and
//			wager must exist as the correct type.




double lose (double balance, double wager, gamerec record[], int turn);
//purpose:the purpose of this the function is to store balance, wager,
//			and if the player won or not. The wager will be subtracted from
//			the balance.
//preconditions:the array of gamerec (record) must exist whith atleast
//			the length of turn. Balance, wager, and turn must exist.
//postconditions:the gamerec in the array record at position turn will
//			have the information(wager, balance, L) input into it.
//exeptions:the array of gamerec(record) must exist. Balance, turn, and
//			wager must exist as the correct type.




void printrecord(int turn, gamerec record[]);
//purpose:The pupose of this function is to print a table containing one
//			peice of the array of gamerec(record). The peice of the array in
//			position turn will be displayed.
//preconditions:the array of gamerec must exist and turn must exist.
//			the array of gamerec must atleast be of length turn. This
//			function requires the function displayheader.
//postconditions:the peice of record(the array of gamerec) at position turn
//			will be displayed in chart form.
//exeptions:The array of gamerec must be of atleast length turn.
//			displayheader must be in the same file.




void displayrecord(int turn, gamerec record[]);
//purpose:The pupose of this function is to print a table containing the
//			contents of the array of gamerec(record). The function will
//			print 1 through turn peices of the array.
//preconditions:the array of gamerec must exist and turn must exist.
//			the array of gamerec must atleast be of length turn. This
//			function requires the function displayheader.
//postconditions:record(the array of gamerec) will be displayed in chart
//			form.
//exeptions:The array of gamerec must be of atleast length turn.
//			displayheader must be in the same file.




int contin();
//purpose:The purpose of this funstion is to ask the play if they want
//			to continue playing. The function will return a 1 for yes
//			or a 2 for no.
//preconditions:none
//postconditions:the player will be asked if they want to continue and
//			then a 1 will be returned if they answer yes, or a 0 will be
//			if they answer no.
//exeptions:none.




void displayheader(void);
//purpose:The purpose of this function is to display to the screen the
//			header for the craps results table
//preconditions:none
//postconditions:the table header will be displayed.
//exeptions:none



void main (void)

{//begin main

int play=1;//if play =1 then continue playing, if play=0 stop play.
double balance;//holds the amount of money the player has
double wager;//the wager
int turn;//number of times that player has played
int roll;//the value of the roll
int point;//holds the value of the point to be matched by roll

handshake();
balance=getbalance();
turn=0;
while (play==1)//continue playing
	{
	if (balance>=1.0)//if player has money
		{
		wager=getwager(balance);
		roll=rolldice(2,6);
		if ((roll==7)||(roll==11))//the player wins
			balance=win(balance,wager,record,turn);
		else if ((roll==2)||(roll==3)||(roll==12))//the player loses
			balance=lose(balance,wager,record,turn);
		else//the player must settle his point
			{
			point=roll;
			cout<<"Your point is "<<point<<".\n";
			cout<<"If you roll a 7, then you lose.\n";
			cout<<"If you roll a "<<point<<" then you win.\n\n";
			roll=1;
			while ((point!=roll)&&(roll!=7))//neither won nor lost
				{
				roll=rolldice(2,6);
				if (roll==point)//player wins
					balance=win(balance,wager,record,turn);
				if (roll==7)//player loses
					balance=lose(balance,wager,record,turn);
				}
			}
		printrecord(turn,record);//prints the record of this game
		}
	else //player's balance is less than 1, can't play anymore
		{
		cout<<"Sorry, you do not have enough money to continue playing.\n\n";
		play=0;
		}
	play=contin();
	turn++;
	if (turn==500)//player cannot play more than 500 games
		{
		play=0;
		cout<<"You have played craps 500 times. I'm sorry, but at this\n";
		cout<<"time you have to leave The Virtual Casino. We hope you have\n";
		cout<<"enjoyed yourself. Feel free to play again.\n\n";
		}
	}
displayrecord(turn,record);
}//end main


void handshake (void)
{//begin handshake
char answer;
cout<<"Welcome to The Virtual Casino. This is the game of craps.\n\n";
cout<<"Do you need to view the rules of the game? (Y/N):";
cin>>answer;
cout<<"\n";
if (answer=='y'||answer=='Y')
	{
	cout<<"Two dice are rolled. If the the sum of the dice on the first\n";
	cout<<"roll is equal to 7 or 11, then the player wins. If the sum\n";
	cout<<"of dice on the first roll is equal to 2, 3, or 12, then the\n";
	cout<<"player loses. In the case that the player rolls a 4, 5, 6, 8,\n";
	cout<<"9, or 10, then that sum  becomes the \"point\". In order for\n";
	cout<<"the player to win, then the player must roll the \"point\"\n";
	cout<<"before they roll a 7.\n\n";
	}
}//end handshake


double getbalance (void)
{//begin getbalance
double balance=0.0;
while (balance<=1.0)
	{
	cout<<"How much money are you beginning the game with?: $";
	cin>>balance;
	cout<<"\n";
	if (balance<=1.0)
		cout<<"You must start the game with atleast one dollar.\n\n";
	}
return balance;
}//end getbalance


double getwager (double balance)
{//begin getwager
int wager=0.0;
while ((wager>balance) ||(wager<1))
	{
	cout<<"You have $"<<balance<<" to wager.\n";
	cout<<"How much money do you wish to wager?: $";
	cin>>wager;
	if (wager>balance)
		cout<<"\nYou cannot have a wager that is higher than your balance.";
	if (wager<1)
		cout<<"\nYou have to bet atleast one dollar.";
	cout<<"\n";
	}
return wager;
}//end getwager


int  rolldice (int numberofdice, int numberofsides)
{//begin rolldice
int rollsum=0;
int roll;

cout<<"You rolled a ";
for (int i=1; i<=numberofdice; i++)
	{
	if (i!=1)
		cout<<" and a ";
	roll =1 + (rand()%numberofsides);
	cout<<roll;
	rollsum=rollsum+roll;
	}
cout<<" for a total of "<<rollsum<<"\n";
return rollsum;
}//end rolldice


double win (double balance,double wager, gamerec record[],int turn)
{//begin win
cout<<"You Win!\n\n";
record[turn].balance=balance+wager;
record[turn].wager=wager;
balance=balance +wager;
record[turn].outcome='W';
return balance;
}//end win


double lose (double balance,double wager,gamerec record[],int turn)
{//begin lose
cout<<"You Lose!\n\n";
record[turn].balance=balance-wager;
record[turn].wager=wager;
balance=balance -wager;
record[turn].outcome='L';
return balance;
}//end lose


void displayheader(void)
{//begin
cout<<"\nGame Number       Outcome         Wager          Bank Balance\n";
cout<<"-------------------------------------------------------------\n";
}//end



void printrecord(int turn, gamerec record[])
{//begin printrecord

displayheader();
cout<<"     ";
cout<<(turn+1);
cout<<"              ";
cout<<record[turn].outcome;
cout<<"             $";
cout<<record[turn].wager;
cout<<"             $";
cout<<record[turn].balance;
cout<<"\n\n";
}//end printrecord


void displayrecord(int turn, gamerec record[])
{//begin displayrecord

cout<<"The results of the game are:\n";
for (int i=0; i<turn; i++)
	{
	if ((i%20)==0)
		{
		displayheader();
		}
	cout<<"     ";
	cout<<(i+1);
	cout<<"             ";
	cout<<record[i].outcome;
	cout<<"             $";
	cout<<record[i].wager;
	cout<<"             $";
	cout<<record[i].balance;
	cout<<"\n";
	}
cout<<"\n";
}//end displayrecord


int contin()
{//begin contin
int play;
char answer;
cout<<"Do you wish to continue playing? (Y/N):";
cin>>answer;
cout<<"\n\n";
if ((answer=='N')||(answer=='n'))
	{
	play=0;
	cout<<"Thank you for playing craps.\n\n";
	}
else
	play=1;

return play;
}//end contin

