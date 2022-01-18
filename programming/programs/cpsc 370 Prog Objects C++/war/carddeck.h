#ifndef Card_Deck
#define Card_Deck
#include "card.h"
const int Max= 52;
typedef card Decktype[Max];
class carddeck {

public:
carddeck(){Front=51; Rear =51; Limit=Max; Count = 0; }
carddeck (int max)
	{Limit = max; Front =51;  Rear = 51; Count = 0;
    filldeck();  shuffle();}

~carddeck(){}
int getsize (){return Count;}
void filldeck();

void shuffle ();

card  getinfo () {
	 card temp;
    temp.face = Deck[(Front +1)% Limit].getface();
    temp.suite = Deck[(Front+1)% Limit].getsuite();
    return temp;}

bool isempty () {return bool(Count == 0);}

bool full () {return bool(Count == Limit);}

void insert (const card Item);

card deal() ;

void clear () {Front=51; Rear =51; Limit=Max; Count = 0;}

void showdeck ();
private:
Decktype Deck;
int Front, Rear, Count, Limit;
};
#endif
