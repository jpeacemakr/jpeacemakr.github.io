#include <time.h>
#include <stdlib.h>
#include <iostream.h>
#include <iomanip.h>
#include "card.h"
#include "carddeck.h"

void carddeck::filldeck(){
card item;
Front = 51; Rear = 51; Count=0;
//for (colors i=club; i <= spade; i++)
for (int i=int(club); i <= int(spade); i++)
	for (int j=0; j<13; j++){
		item.face = j+2;
		item.suite = colors(i);
		insert(item);
	}//end for i and for j
}; //end filldeck
void carddeck::shuffle (){
int I;
card Temp ;
for (int J = 51; J > 0; J--) {
	I = rand() % 52;
	Temp = Deck[I];
	Deck[I] = Deck[J];
	Deck[J] = Temp;
	}//end for
	showdeck();
	} //END Shuffle
void carddeck::insert (const card Item) {
if (!full()) {
	Rear = (Rear+1) % Limit;
	Deck[Rear] = Item;
	Count++; }
	}
card carddeck::deal()
	{Front = (Front+1 ) % Limit;
	Count--;
	return Deck[Front];
	 }
void carddeck::showdeck () {
int front, count=0;
front = (Front + 1) % Limit;
do {
	Deck[front].showcard();
	count ++;
	if ((count % 4) == 0) cout <<endl;
	front = (front + 1) % Limit;
} while (count != Count);
cout <<endl <<endl;
}
