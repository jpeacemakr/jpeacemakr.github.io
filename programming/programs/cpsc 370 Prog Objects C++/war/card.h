#ifndef booltype_
#define booltype_
enum bool {false, true};
#endif
#ifndef card_
#define card_
class carddeck;
enum colors {club, diamond, heart, spade};
enum {Jack=11, Queen=12, King=13, Ace=14};
class card {
friend carddeck;
public:
card(){};
card(card& oldcard)
  {face = oldcard.face;
   suite = oldcard.suite;
} //end copy constructor
~card(){};
void setcard(int nuface, colors nusuite)
   {setface(nuface); setsuite(nusuite);}
void setface(int nuface){face = nuface;}
void setsuite(colors nusuite){suite = nusuite;}
int getface(){return face;}
colors getsuite(){return suite;}
void showcard();
card getinfo () {
  card one;
  one.face = face;
  one.suite = suite;
return one;
}

private:
int face;
colors suite;
}; 
#endif
