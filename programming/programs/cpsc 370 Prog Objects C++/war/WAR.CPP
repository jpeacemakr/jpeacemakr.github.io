
////////////////////////////////////////////////////////////////////////////
//title:war.cpp
//author:james peacemaker
//class:CPSC 370
//e-mail adress:jpeac1ij@mwc.edu
//language:C++
//purpose:the purpose of this program is to simulate the card game of war.
/*description:The game of war starts out by dealing out all of the cards
		to the two players. Each player should have 26 cards to begin
		with. The player's cards are stacked face down on the table.
		The two players both draw one card from the top of their
		respective decks and place them face up on the table. The
		player with the highest card wins ang gets both of the cards
		to put at the bottom of his/her pile. In the event of a tie,
		war is declared. When war is declared, each player takes three
		cards off the top of their pile and places them face down on
		the table. The players then each draw a fourth card and place
		it face up on the table. the player with the highest card gets
		all of the cards on the table to put at the bottom of their
		stack. If there is a tie again, then war is declared again and
		the process repeats. The game ends when one player has all of
		the cards.*/
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip.h>
#include "card.h"
#include "carddeck.h"


int main (void)
	{//begin main
	char answer;//if y or Y then the user wants to see the rules of the game
	int playagain;//1=true , 0=false, if user wants to play again
	int turns;//number of turns that have passed
	const int turnslimit=500;//limits the number of turns to 500
	card cardtoget;//holds the card recieved by a player from from the pile
	card cardtodeal;//holds the card to be dealt
	card player1card;//holds player1's card for comparing
	card player2card;//holds player2's card for comparing

	//handshake
	cout<<"Welcome. This is the card game of War.\n\n";
	cout<<"Do you wish to see the rules of the game?(Y/N):";
	cin>>answer;
	if (answer=='y' || answer=='Y')
		{
		cout<<"\nThe game of war starts out by dealing out all of the cards\n";
		cout<<"to the two players. Each player should have 26 cards to begin\n";
		cout<<"with. The player's cards are stacked face down on the table.\n";
		cout<<"The two players both draw one card from the top of their\n";
		cout<<"respective decks and place them face up on the table. The\n";
		cout<<"player with the highest card wins ang gets both of the cards\n";
		cout<<"to put at the bottom of his/her pile. In the event of a tie,\n";
		cout<<"war is declared. When war is declared, each player takes three\n";
		cout<<"cards off the top of their pile and places them face down on\n";
		cout<<"the table. The players then each draw a fourth card and place\n";
		cout<<"it face up on the table. the player with the highest card gets\n";
		cout<<"all of the cards on the table to put at the bottom of their\n";
		cout<<"stack. If there is a tie again, then war is declared again and\n";
		cout<<"the process repeats. The game ends when one player has all of\n";
		cout<<" the cards.\n\n";
		cout<<"Press RETURN to continue.";
		cin.get();
		cin.get();
		cout<<"\n\n";
	}

	playagain=1;
	while (playagain==1)
		{
		cout<<"The shuffled deck is:\n";
		cout<<"---------------------\n";
		carddeck deck(52);//sets the deck to 52 cards, shuffles, prints
		cout<<"\nPress RETURN to continue.\n";
		cin.get();
		carddeck player1;//player1's hand
		carddeck player2;//player2's hand
		carddeck pile;//hold's the cards that are on the table
		srand(time(0));//set the random number generator seed
		int keepplaying=1;//1=true(keep playing), 0=false(game over)
		cout<<"\n";

		//deal cards from deck to player1 and player2
		for(int i=1;i<=52;i++)
			{
			cardtodeal = deck.deal();
			if(i%2==1)
				player1.insert (cardtodeal);
			if(i%2==0)
				player2.insert (cardtodeal);
			}

		//display player1 and player2's hands that they start with
		cout<<"\nPlayer 1's hand:\n";
		cout<<"----------------\n";
		player1.showdeck();
		cout<<"\nPlayer 2's hand:\n";
		cout<<"----------------\n";
		player2.showdeck();
		cout<<"\n\nPress RETURN to continue.";
		cin.get();

		turns=0;
		//gameplay (continues until someone has no cards)
		while (keepplaying !=0)
			{
			//display number of cards each person has
			cout<<"Player 1 has "<<player1.getsize()<<" cards.\n";
			cout<<"Player 2 has "<<player2.getsize()<<" cards.\n\n";

			//get player1's card
			player1card=player1.deal();
			cout<<"\nPlayer 1 draws a: ";
			player1card.showcard();
			pile.insert (player1card);

			//get player2's card
			player2card=player2.deal();
			cout<<"\nPlayer 2 draws a: ";
			player2card.showcard();
			pile.insert (player2card);

			//if player1's card > player2's card
			if (player1card.getface() > player2card.getface())
				{
				//player1 gets all cards in pile (on table)
				cout<<"\n\nPlayer 1 wins that set.\n\n";
				cout<<"Player 1 wins the following cards:\n";
				cout<<"----------------------------------\n";
				pile.showdeck();
				while (!pile.isempty())
					{
					cardtoget=pile.deal();
					player1.insert (cardtoget);
					}
				turns++;
				cin.get();
				}

			//if player2's card > player1's card
			if (player2card.getface() > player1card.getface())
				{
				//player2 gets all cards in pile (on table)
				cout<<"\n\nPlayer 2 wins that set.\n\n";
				cout<<"Player 2 wins the following cards:\n";
				cout<<"----------------------------------\n";
				pile.showdeck();
				while (!pile.isempty())
					{
					cardtoget=pile.deal();
					player2.insert (cardtoget);
					}
				turns++;
				cin.get();
				}

			//if player1's card = player2's card
			if (player1card.getface()==player2card.getface())
				{
				cout<<"\n\nIT IS TIME TO DECLARE WAR!!!\n";

				//put 3 cards from player1 into pile
				cout<<"\nPlayer 1 lies 3 cards face down.\n";
				for(i=1;i<=3&&!player1.isempty();i++)
					{
					cardtoget = player1.deal();
					cardtoget.showcard();
					pile.insert (cardtoget);
					}

				//put 3 cards from player2 into pile
				cout<<"\nPlayer 2 lies 3 cards face down.\n";
				for(i=1;i<=3&&!player2.isempty();i++)
					{
					cardtoget = player2.deal();
					cardtoget.showcard();
					pile.insert (cardtoget);
					}
				cout<<"\n\n";
				}

			//if player1 is out of cards player 2 wins and the game is over
			if (player1.isempty())
				{
				cout<<"Player 1 has no more cards.\n";
				cout<<"Player 2 has all of the cards.\n\n";
				cout<<"\nPlayer 2 wins!\n";
				keepplaying=0;
				}

			//if player2 is out of cards player 1 wins and the game is over
			if (player2.isempty())
				{
				cout<<"Player 1 has all of the cards.\n";
				cout<<"Player 2 has no more cards.\n\n";
				cout<<"\nPlayer 1 wins\n";
				keepplaying=0;
				}

			//if a turnslimit number of hands are played then the game ends
			if(turns>turnslimit)
				{
				keepplaying=0;
				cout<<"You have drawn cards "<<turnslimit<<" times.\n";
				cout<<"It's time to determine a winner.\n\n";
				cout<<"Player 1 has "<<player1.getsize()<<" cards.\n";
				cout<<"Player 2 has "<<player2.getsize()<<" cards.\n\n";
				if (player1.getsize()>player2.getsize())
					{
					cout<<"Player 1 wins!\n\n";
					}
				else if (player2.getsize()>player1.getsize())
					{
					cout<<"Player 2 wins!\n\n";
					}
				else
					{
					cout<<"It's a tie!";
					}
				}
			}

		//see if the user wants to play again
		cout<<"\nDo you want to play again?(Y/N): ";
		cin>>answer;
		cout<<"\n\n";
		if (answer=='n' ||answer=='N')
			{
			playagain=0;
			}
		}
	return 0;
	}//end main

