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
	//void show (date & d);
	cout << month << '/' << day << '/' << year << endl;
	//show(*this);
	}//end display

void nextday(const date & d)
	{
	/*if (d.day==28&&d.month==2&&leapyear(d.year))
		{
		day = 29;                  // not end of month
		month = d.month;
		year = d.year;
		}
	else if (d.day==29&&d.month==2&&leapyear(d.year))
		{
		day = 1;                  // not end of month
		month = d.month +1;
		year = d.year;
		}
	else*/ if (d.day != mdays(d))
		{
		day = d.day + 1;                  // not end of month
		month = d.month;
		year = d.year;
		}
	else if (d.month != 12)
		{
		day = 1;                          // not end of year
		month = d.month + 1;
		year = d.year;
		}
	else
		{                                     // December 31
		day = 1;
		month = 1;
		year = d.year + 1;
		}
	}//end next day

previousday(const date & d)
	{
	/*if (d.day==1&&d.month==3&&leapyear(d.year))
		{
		day = 29;                  // not end of month
		month = d.month -1;
		year = d.year;
		}
	else if (d.day==29&&d.month==2&&leapyear(d.year))
		{
		day = 28;                  // not end of month
		month = d.month;
		year = d.year;
		}
	else*/ if (d.day != 1)
		{
		day = d.day - 1;                  // not end of month
		month = d.month;
		year = d.year;
		}
	else if (d.month != 1)
		{
		month = d.month - 1;
		day = mdays(d);                          // not end of year
      year = d.year;
		}
	else
		{                                     // December 31
		day = 31;
		month = 12;
		year = d.year - 1;
		}
	}//end next day


int dayofweek(date & d)
	{
	int weekday;
	unsigned int count=0;
	date c;

	while (d.compare2dates(d,c)!=0)
		{
		count= count+1;
		c.nextday(c);
		}
	c.display();
	weekday=(count-1)%7;
   //cout<<weekday<<count;
	return weekday;


	}





adddays(date & d, int num)
	{
	for (int i=0;i<num;i++)
		{
		nextday(d);
		}
	}

subtractdays(date & d, int num)
	{
	for (int i=0;i<num;i++)
		{
		previousday(d);
		}

	}



int subtract2dates(date & d,date & c)
	{
	if (compare2dates(d,c)==1)//d > c
		{
		int count=0;
		while (compare2dates(d,c)!=0)
			{
			count= count+1;
			c.nextday(c);
			}
		return count;
		}
	else if (compare2dates(d,c)==-1)//d < c
		{
		int count=0;
		while (compare2dates(d,c)!=0)
			{
			count= count+1;
			c.previousday(c);
			}
		return count;
		}
	else //d==c
		{
		return 0;
		}
	}

int compare2dates (date & d,date & c)
	{
	if (d.year>c.year)
		return 1;
	else if (d.year<c.year)
		return -1;
	else
		{
		if (d.month>c.month)
			return 1;
		else if (d.month<c.month)
			return -1;
		else
			{
			if (d.day>c.day)
				return 1;
			else if (d.day<c.day)
				return -1;
			else
				return 0;
			}
		}
	}







private:
	int month, day, year;
	int mdays(const date & today)
		{
		//Variables
		const int dpm[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (today.month == 2 && leapyear(today.year))
			return 29;
		else
			return dpm[today.month - 1];
		}

	int leapyear(int year)
		{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return 1;
		else
			return 0;
		}

}; //end struct date


