// nextda3.cpp - determine tomorrow's date
#include <iostream.h>
#include <stdlib.h>

class date {
public:
date () {month = 1; day = 1; year = 0;}
date (int mon, int da, int yr){setdate(mon, da, yr);}
void setdate (int mon, int da, int yr)
{
month = mon; day = da; year = yr;
}//end setdate
int getmonth(){return month;}
int getday(){return day;}
int getyear(){return year;}
~date(){};
date (date & d) {month = d.month; day = d.day; year = d.year;}
void display ()
{
void show (date & d);
//cout << month << '/' << day << '/' << year << endl;
show(*this);
}//end display

void nextday(const date & d)
{
   if (d.day != mdays(d)) {
      day = d.day + 1;                  // not end of month
      month = d.month;
      year = d.year;
   }
   else if (d.month != 12) {
      day = 1;                          // not end of year
      month = d.month + 1;
      year = d.year;
   }
   else {                                     // December 31
      day = 1;
      month = 1;
      year = d.year + 1;
   }
}//end next day

private:
int month, day, year;

int mdays(const date & today)
{
//Variables
   const int dpm[] = { 31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31 };

   if (today.month == 2 && leapyear(today.year))
      return 29;
   else
      return dpm[today.month - 1];
}

bool leapyear(int year)
{
   if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
      return true;
   else
      return false;
}

}; //end struct date

int main()
{
//  Variables
    //date d1, d2, d3;
    date next;  char wait; int month, day, year ;

    date d1( 7, 30, 1992 );
    date d2( 12, 31, 1989 );
    date d3( 2, 28, 1992 );

    next.display();
    next.nextday(d1);
    cout << "If today is:  ";
    d1.display();
    cout << "Tomorrow is:  ";
    next.display ();
    cout <<endl << endl;

    next.nextday(d2);
    cout << "If today is:  ";
    d2.display();
    cout << "Tomorrow is:  ";
    next.display ();
    cout << endl <<endl;

    next.nextday(d3);
    cout << "If today is:  ";
    d3.display();
    cout << "Tomorrow is:  ";
    next.display ();
    cout << endl <<endl;

    cout <<"Please enter a date as month day year [enter] " <<endl;
    cin >> month >> day >> year;
    d1.setdate(month, day, year);
    next.nextday( d1);
    cout << "If today is:  ";
    d1.display();
    cout << "Tomorrow is:  ";
    next.display ();
    cout <<endl <<endl;

    cout << "pause.  hit any key then enter to continue";
    cin >> wait;
    return 0;
}
void show (date & d){
cout << d.getmonth() << '/' << d.getday() << '/' << d.getyear() << endl;
}
