//#include <iostream.h>
//#include <stdlib.h>

class date {
public:
	//default constructor
	date () {month = 1; day = 1; year = 1970;};

	//constructor hat sets date to the first of a year
	date (int yr) {month = 1; day =1; year = yr;};

	//constructor that sets date to a month, day, and year
	date (int mon, int da, int yr){setdate(mon, da, yr);};

	//copy constructor
	date (date & d) {month = d.month; day = d.day; year = d.year;};

	//destructor
	~date(){};

	//returns the month
	int getmonth(){return month;};

	//returns the day
	int getday(){return day;};

	//returns the year
	int getyear(){return year;};

	//sets the date to a specified month, day, and year
	void setdate (int mon, int da, int yr)
		{
		month = mon; day = da; year = yr;
		};

	//displays date in form month/day/year
	void display ()
		{
		cout << month << '/' << day << '/' << year << endl;
		};//end display

	//changes date to the nevt date
	//pre: d is defined
	//post: the date of the following day is returned
	void nextday(const date & d)
		{
		if (d.day != mdays(d))    // not end of month
			{
			day = d.day + 1;
			month = d.month;
			year = d.year;
			}
		else if (d.month != 12)     // not end of year
			{
			day = 1;
			month = d.month + 1;
			year = d.year;
			}
		else                       // December 31
			{
			day = 1;
			month = 1;
			year = d.year + 1;
			}
		};//end next day

	//changes the date to the previous date
	//pre: d is defined
	//post: the date of the previous day is returned
	void previousday(const date & d)
		{
		if (d.day != 1)  // not beginning of month
			{
			day = d.day - 1;
			month = d.month;
			year = d.year;
			}
		else if (d.month != 1) // not beginning of year
			{
			month = d.month - 1;
			day = mdays(d);
			year = d.year;
			}
		else                 // Jamuary 1
			{
			day = 31;
			month = 12;
			year = d.year - 1;
			}
		};//end next day

	//my dayof week function. it works, but not as fast.
	// i understand how this one works.
	/*int mydayofweek(date & d)
		{
		int weekday;
		unsigned int count=0;
		date c(0);

		while (d.compare2dates(d,c)!=0)
			{
			count= count+1;
			c.nextday(c);
			}
		c.display();
		weekday=(count)%7;
		return weekday;
		}*/

	//returns a number 0-6 corresponding to the days of the week sun-sat
	//pre: d is defined
	//post: the day of the week is returned as an integer
	int dayofweek(date & d)
		{
		int weekday;
		if(month<3)
			{
			year=year-1;
			weekday=(23*month/9+day+4+(year+1)+year/4-year/100+year/400)%7;
			}
		else
			weekday=(23*month/9+day+4+(year-2)+year/4-year/100+year/400)%7;
		return weekday;
		};

	//adds a certain number of days to a date
	//pre: d is defined
	//post: a certain number of days (num) is added to the date d
	void adddays(date & d, int num)
		{
		for (int i=0;i<num;i++)
			{
			nextday(d);
			}
		};
	//overloads + operator to add days to a date
	//pre: d is defined
	//post: a certain number of days (num) is added to the date d
	date operator + (int num)
		{
		date d(this->month,this->day,this->year);
		d.adddays(d, num);
		return d;
		};

	//subtracts a certain number of days to a date
	//pre: d is defined
	//post: a certain number of days (num) is subtracted from the date d
		void subtractdays(date & d, int num)
		{
		for (int i=0;i<num;i++)
			{
			previousday(d);
			}
		};

	//overloads the - operator to subtract days from a date
	//pre: d is defined
	//post: a certain number of days (num) is delted from the date d
	date operator - (int num)
		{
		date d(this->month,this->day,this->year);
		d.subtractdays(d, num);
		return d;
		};

	//subtracts two dates and returns the difference
	//pre: d and c are defined
	//post: the smaller of the two days is subtracted from the larger
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
		};
	//overloads the - operator to subtract 2 dates
	//pre: c is defined
	//post: the smaller of the two days is subtracted from the larger
	int operator - (date & d)
		{
		date c(this->month,this->day,this->year);
		int num=c.subtract2dates(c,d);
		return num;
		};

	//compares 2 dates, similiar to string compare
	//pre: d and c are both defined
	//post:
	//returns a 1 if the first is greater
	//returns a -1 if the second is greater
	//returns a 0 if they are equal
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
		};

private:
	//the attributes of a date
	int month, day, year;

	//determines the number of days in a month
	int mdays(const date & today)
		{
		//Variables
		const int dpm[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (today.month == 2 && leapyear(today.year))
			return 29;
		else
			return dpm[today.month - 1];
		};

	//determines if a year is a leap year
	int leapyear(int year)
		{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return 1;
		else
			return 0;
		};

}; //end struct date


