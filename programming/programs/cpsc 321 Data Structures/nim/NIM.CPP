
//title:nim.cpp
//author:james peacemaker
//class:cpsc 321
//e-mail adress:jpeac1ij@mwc.edu
//language:C++
//purpose:The pupose of this program is to simulate the game of nim.
//description:	The game of Nim is played with three piles of stones. One
//	pile has three stones, a second pile has five stones, and a
//	third pile has eight stones. Player 1 and Player 2 take turns
//	removing any number of stones from one pile. The one to take
//	the last stone loses. The winner of the game gets to go first
//	on the next round.

#include <iostream.h>


void handshake(void);
//purpose:The purpose of the handshake is to greet
//         the user and to briefly explain the game of nim.
//preconditions:none
//postconditions:none
//exeptions:none


void getplayernames (char player1[], char player2[]);
//purpose:the purpose of this function is to get the names
//        of player1 and player2
//preconditions:there must be enough memory to store the names
//postconditions:the strings player1 and player2 will hold the names
//exeptions:the user must not enter more than 30 characters. If the user
//        puts blank spaces it will stop. The characters after the space
//        will be read by the next "cin>>"  statement, causing problems.


void removestones (char name[],int pilesarray[3]);
//purpose:The purpose of this function is to promt the player for
//			which pile that they want to remove stones from, then how many
//			they want to remove. The function then removes the number from
//			that pile.
//preconditions:the player's name must be present. The array pilesarray
//			must exist.
//postconditions:pilesarray will be modified. the number of stones will
//			be removed from one pile in the array.
//exeptions:if a character not an integer is entered for the pile number or
//			number of stones then the program will crash. The function makes
//       sure that the integers are with in range.


int gameovercheck (int pilesarray[3]);
//purpose:the purpose of this function is to tell if the game is over. If
//			pileasarray=[0,0,0], then the array is empty and the game is over.
//			A value of 1 is returned for game not over and 0 for game over.
//preconditions:the pilesarray must exist
//postconditions:the returned value will be a 0 for game over or a 1 for
//			not over
//exeptions:there will be an exception if pilesarray is not atleast 3 long.


void addscore (int *playerarray,int turn);
//purpose:the purpose of addscore is to add one win to the player's record
//			if it is not their turn.
//preconditions:playerarray must exist, turn must exist
//postconditions:the player's wins in player array will be incremented by 1
//exeptions:playerarray must be array of integer, turn must be integer


void printscore(int playerarray[2], char player1[], char player2[]);
//purpose: the purpose of this function is to print the score of player 1
//			and the score of player 2.
//preconditions:player1, player2, and playerarray must exist
//postconditions:the scores will be printed to the screen.
//exeptions:none




void main (void)
	{//begin main
	char continueplaying ='Y';//used to see if the user wants to continue playing
	int pilearray[3];//holds number of stones in the 3 piles
	int playerarray[2];//holds the number of wins for player1 and player 2
	int turn;//if even then player1's turn, if odd player2's turn
	char player1[31];//string of player1's name
	char player2[31];//string of player2's name
	int contin;//if user wants to continue then contin=1, otherwise 0

	handshake();
	getplayernames(player1, player2);
	playerarray[0]=0;//player1 starts off with 0 wins
	playerarray[1]=0;//player2 starts off with 0 wins
	turn=0;
	while ((continueplaying !='N')&&(continueplaying!='n'))
		{
		contin=1;
		pilearray[0]=3;
		pilearray[1]=5;
		pilearray[2]=8;
		while (contin == 1)
			{
			if ((turn%2)==0)//player1's turn
				{
				removestones(player1,pilearray);
				}
			if ((turn%2)==1)//player2's turn
				{
				removestones(player2,pilearray);
				}
			contin=gameovercheck(pilearray);
			if (contin == 0)
				addscore(playerarray,turn);
			turn++;
			}
		printscore(playerarray,player1,player2);
		cout<<"\nDo you wish to continue playing?(Y/N)";
		cin>>continueplaying;
		cout<<"\n\n";
		}
	printscore(playerarray,player1,player2);
	if (playerarray[0]==playerarray[1])
		cout<<"There is a tie! Neither player wins or loses.";
	if (playerarray[0]>playerarray[1])
		{
		cout<<"\nPlayer 1, "<<player1<<", is the winner!\n";
		cout<<"Player 2, "<<player2<<", is the loser.";
		}
	if (playerarray[0]<playerarray[1])
		{
		cout<<"\nPlayer 2, "<<player2<<", is the winner!\n";
		cout<<"Player 1, "<<player1<<", is the loser.";
		}
	cout<<"\n\nThank you for playing Nim.";
	}//end main


void handshake(void)
	{//begin
	cout<<"Welcome. This is the game of Nim.\n\n";
	cout<<"The game of Nim is played with three piles of stones. One\n";
	cout<<"pile has three stones, a second pile has five stones, and a\n";
	cout<<"third pile has eight stones. Player 1 and Player 2 take turns\n";
	cout<<"removing any number of stones from one pile. The one to take\n";
	cout<<"the last stone loses. The winner of the game gets to go first\n";
	cout<<"on the next round.\n\n";
	cout<<"Press RETURN to begin the game.";
	cin.get();
	}//end handshake


void getplayernames (char player1[31],char player2[31])
	{//begin
	cout<<"\nPlease enter the name of player 1 (30 letters max, no spaces):";
	cin>>player1;
	cout<<"Please enter the name for player 2 (30 letters max, no spaces):";
	cin>>player2;
	}//end getplayernames


void removestones (char name[],int pilesarray[3])
	{//begin
	int I;
	int pile;
	int rocks;
	int pile1=pilesarray[0];
	int pile2=pilesarray[1];
	int pile3=pilesarray[2];
	int one =1;
	while (one==1)
		{
		cout<<"\nPile 1: ";
		for(I=0;I<pile1;I++)
			{
			cout<<"@";
			}
		cout<<"\nPile 2: ";
		for(I=0;I<pile2;I++)
			{
			cout<<"@";
			}
		cout<<"\nPile 3: ";
		for(I=0;I<pile3;I++)
			{
			cout<<"@";
			}
		cout<<"\nThere are "<<pilesarray[0]<<" stones in the first pile.\n";
		cout<<"There are "<<pilesarray[1]<<" stones in the second pile.\n";
		cout<<"There are "<<pilesarray[2]<<" stones in the third pile.\n\n";
		cout<<name<<", which pile do you want to remove stones from?(1-3):";
		cin>>pile;
		if ((pile<4) && (pile>0))
			{
			cout<<name<<", how many stones do you want to remove from pile "<<pile<<" ?:";
			cin>>rocks;
			if (rocks<=(pilesarray[pile-1])&&(rocks>0))
				{
				pilesarray[pile-1]=(pilesarray[pile-1]-rocks);
				one=2;//exit the loop
				}
			else
				{
				cout<<"You did not enter a number between 1 and "<<pilesarray[pile-1]<<".\n\n";
				}
			}
		else
			{
			cout<<"You did not enter a number between 1 and 3 for the pile number.\n\n";
			}
		}
	}//end removestones

int gameovercheck (int *pilesarray)
	{//begin
	if ((pilesarray[0]==0) && (pilesarray[1]==0) &&(pilesarray[2]==0))
		return 0;
	else
		return 1;
	}//end gameovercheck

void addscore (int *playerarray,int turn)
	{//begin
	if ((turn%2)==1)//player1's turn
		{
		playerarray[0]=playerarray[0]+1;
		cout<<"\nPlayer 1 wins that round!\n\n";
		}
	if ((turn%2)==0)//player2's turn
		{
		playerarray[1]=playerarray[1]+1;
		cout<<"\nPlayer 2 wins that round!\n\n";
		}
	}//end addscore

void printscore(int playerarray[2], char player1[], char player2[])
	{//begin
	cout<<"Player 1, "<<player1<<", won "<<playerarray[0]<<" time(s).\n";
	cout<<"Player 2, "<<player2<<", won "<<playerarray[1]<<" time(s).\n";
	}//end printscore





