// nextday.C - determine tomorrow's date
#include <iostream.h>
#include <stdlib.h>
// The C++ Compiler on Oregano has bool as a data type
// enum bool {false, true}; 

struct date {
   int month, day, year;
};

int main()
{
//  Prototypes
	 void nextday(const date & d, date  & today);
//  Variables
    date d1 = { 7, 30, 1992 };
    date d2 = { 12, 31, 1989 };
    date d3 = { 2, 28, 1992 };

    date next;  char wait;
    
    nextday(d1, next);
    cout << next.month << ',' << next.day << ',' << next.year << endl;

    nextday(d2, next);
    cout << next.month << ',' << next.day << ',' << next.year << endl;

    nextday(d3, next);
    cout << next.month << ',' << next.day << ',' << next.year << endl;
    cout << "pause.  hit enter to continue";
    cin >> wait;
    return 0;
}

void nextday(const date & d, date & today)
{
// Prototype
   int mdays(const date & d);

   if (d.day != mdays(d)) {
      today.day = d.day + 1;                  // not end of month
      today.month = d.month;
      today.year = d.year;
   }
   else if (d.month != 12) {
      today.day = 1;                          // not end of year
      today.month = d.month + 1;
      today.year = d.year;
   }
   else {                                     // December 31
      today.day = 1;
      today.month = 1;
      today.year = d.year + 1;
   }
}

int mdays(const date & today) 
{
//Prototype
   bool leapyear(int year);
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

/************************************************************************

$ nextday
7,31,1992
1,1,1990
2,29,1992

*/
