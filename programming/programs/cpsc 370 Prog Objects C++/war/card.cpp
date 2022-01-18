#include <iostream.h>
#include <iomanip.h>
#include "card.h"
void card::showcard () {
if ((face > 1) && (face <11))
	cout << setw(5) <<face;
else if (face == 14)
	cout <<"  Ace";
else if (face == 11)
	cout <<" Jack" ;
else if (face == 12)
	cout <<"Queen";
else if (face == 13)
	 cout <<" King";
cout << " of ";
switch(suite) {
case club: cout <<"Clubs    "; break;
case spade: cout <<"Spades   "; break;
case diamond: cout <<"Diamonds "; break;
case heart: cout <<"Hearts   "; break;
}; //end switch
}//END ShowCard