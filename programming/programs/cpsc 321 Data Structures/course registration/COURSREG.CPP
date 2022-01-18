
////////////////////////////////////////////////////////////////////////////
//	title:coursreg.cpp
// author:james peacemaker
// class:CPSC 321
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose:this program is designed to register students for classes
// description:courses are read in from a file. students are read in
// from a file. students are put into their classes as long as the class is
// not full. all classes with less than 5 students after enrollment are
// deleted. any student that did not get a class is outputted to a not approved
// file. rosters are outputted to a roster file.
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <iomanip.h>
#include <string.h>
#include <fstream.h>
#include "list.h"
#include "listnd.h"

//this structure is the node type for the course list
struct course
{
int refnum;
char deptcode[5];
int coursenum;
char coursename[50];
int numofstudents;
};

//this structure is the node type for the student list
struct student
{
char ssn[12];
char fname[25];
char lname[25];
char year[3];
};

//friend functions


//printdata:
//purpose: this friend function is used by the print function in order to
//print a node in the courselist
void printdata (course coursenode) //print course in a courselist
	{
	cout<<"Course Ref Num: ";
	cout<<coursenode.refnum<<endl;
	cout<<"Dept. Code: ";
	cout<<coursenode.deptcode<<endl;
	cout<<"Course Num: ";
	cout<<coursenode.coursenum<<endl;
	cout<<"Course Name: ";
	cout<<coursenode.coursename<<endl;
	cout<<"Num of Students: ";
	cout<<coursenode.numofstudents<<"\n\n";
	}


//printdata:
//purpose: this friend function is used by the print function in order to
//print a node in the studentlist
void printdata (const student studentnode) //print student in a roster
	{
	cout<<"SSN: ";
	cout<<studentnode.ssn<<endl;
	cout<<"First Name: ";
	cout<<studentnode.fname<<endl;
	cout<<"Last Name: ";
	cout<<studentnode.lname<<endl;
	cout<<"Year: ";
	cout<<studentnode.year<<"\n\n";
	}


//printdata:
//purpose this friend function is used by the print function in order to
//print a node in the courselist to a specific file
void printdata (course coursenode, ofstream &outfile) //print course in a courselist
	{
	outfile<<"Course Ref Num: ";
	outfile<<coursenode.refnum<<endl;
	outfile<<"Dept. Code: ";
	outfile<<coursenode.deptcode<<endl;
	outfile<<"Course Num: ";
	outfile<<coursenode.coursenum<<endl;
	outfile<<"Course Name: ";
	outfile<<coursenode.coursename<<endl;
	outfile<<"Num of Students: ";
	outfile<<coursenode.numofstudents<<"\n\n";
	}


//printdata:
//purpose this friend function is used by the print function in order to
//print a node in the studentlist to a specific file
void printdata (const student studentnode, ofstream &outfile) //print student in a roster
	{
	outfile<<"SSN: ";
	outfile<<studentnode.ssn<<endl;
	outfile<<"First Name: ";
	outfile<<studentnode.fname<<endl;
	outfile<<"Last Name: ";
	outfile<<studentnode.lname<<endl;
	outfile<<"Year: ";
	outfile<<studentnode.year<<"\n\n";
	}


//compare:
//purpose: friend function insert compare for students
//used by the search function to find where to insert a student
//returns 1(true) or 0(false)
int compare(const student temp, const student insertednode)
	{
	if(strcmp(temp.lname,insertednode.lname)>0)
		{
		return 0;
		}
	else
		{
		return 1;
		}
	}





//compare:
//purpose: friend function to compare courses
//used by the search function to find a student
//if key.refnum=-1 then compare deletes all nodes with numstudents less
//than 5. else compare finds the course with that course refnum
//returns 1(true) or 0(false)
int compare(const course temp, const course key)
	{
	if (key.refnum==-1)
		{
		if (temp.numofstudents<key.numofstudents)
			return 0;
		else
			return 1;
		}
	else
		{
		if(temp.refnum==key.refnum)
			return 0;
		else
			return 1;
		}
	}


//validatefriend:
//purpose: this friend checks to see if a course node is valid
//returns a 1(true) or 0(false)
int validatefriend(course &temp)
	{
	if(temp.numofstudents<15)
		{
		temp.numofstudents=temp.numofstudents+1;
		return 1;
		}
	else
		{
		cout<<"Invalid course.\n";
		return 0;
		}
	}


//validatefriend:
//purpose: this friend checks to see if a student node is valid
//returns a 1(true) or 0(false)
//this function is not used in this program, but needed for compilation
int validatefriend(student temp)
	{
	if(strcmp(temp.lname," ")>0)
		return 0;
	else return 1;
	}




int main (void)
	{//begin main
	list<  course > courselist;//list of courses
	list<  student > roster[20];//array of 20 student lists
	int num;//number of classes a student is taking
	course tempcourse;//temporary course to hold node info
	student tempstudent;//temporary student to hold node info
	int courserefnum;//course refnum to insert a student into

	//open the file that holds the course information
	char courseinfilename[20];
	cout<<"\n\nEnter the name of the file to read courses from: ";
	cin>>courseinfilename;
	ifstream courseinfile(courseinfilename);

	//open the file that holds the student information
	char studentinfilename[20];
	cout<<"\n\nEnter the name of the file to read students from: ";
	cin>>studentinfilename;
	ifstream studentinfile(studentinfilename);

	//opens the output file for rosters
	char rosteroutfilename[20];
	cout<<"\n\nEnter the name of the file to print the rosters to: ";
	cin>>rosteroutfilename;
	ofstream rosteroutfile(rosteroutfilename);

	//opens the output file for not approved student information
	char notapprovedoutfilename[20];
	cout<<"\n\nEnter the name of the file to print\n";
	cout<<"the not approved students to: ";
	cin>>notapprovedoutfilename;
	ofstream notapprovedoutfile(notapprovedoutfilename);


	//load the courses into the list
	int length=1;
	//while (not end of file) or (count =20);
	while ((!courseinfile.eof())&&(length<21))
		{
		courseinfile>>tempcourse.refnum;
		courseinfile>>tempcourse.deptcode;
		courseinfile>>tempcourse.coursenum;
		courseinfile.getline(tempcourse.coursename,40,'\n');
		tempcourse.numofstudents=0;
		if(!courseinfile.eof())
			courselist.insertatrear(tempcourse);
		length=length + 1;
		}

	//print the courses to the screen
	cout<<"\n\nBefore students loaded.\n";
	cout<<"----------------------------------------------\n\n";
	courselist.print();


	//load the students into the array of rosters
	course tempcourseval;
	while (!studentinfile.eof())
		{
		studentinfile>>tempstudent.ssn;
		studentinfile>>tempstudent.fname;
		studentinfile>>tempstudent.lname;
		studentinfile>>tempstudent.year;
		studentinfile>>num;
		if (!studentinfile.eof())
			{
			for(int i=0; i<num; i++)
				{
				//get courseref number
				studentinfile>>courserefnum;
				tempcourseval.refnum=courserefnum;
				//validate:returns true if course exists and course enrollment <15
				if(courselist.validate(tempcourseval))
					{
					roster[courserefnum-1].search(tempstudent);
					roster[courserefnum-1].insertnode(tempstudent);
					}
				else
					{
					notapprovedoutfile<<"\nThis student is not approved:\n";
					printdata(tempstudent, notapprovedoutfile);
					notapprovedoutfile<<"for the class with the class ref num: ";
					notapprovedoutfile<<courserefnum;
					notapprovedoutfile<<"\n\n";
					}
				}
			}
		}

	//print classes to the screen after the students are loaded
	cout<<"After students loaded:\n";
	cout<<"------------------------------------\n\n";
	courselist.print();

	//get rid of courses with less than 5 students
	//set coursekey used in validate
	course coursekey;
	coursekey.refnum =-1;
	coursekey.numofstudents=5;

	course removednode;//course that is removed from the list
	int looprun = 1;//set looprun = 1(true)

	//print a header to the not approved file
	notapprovedoutfile<<"NOT APPROVED classes.\n";
	notapprovedoutfile<<"---------------------------\n\n";


	for(int j=1;j<20;j++)
		{
		looprun = 1;
		while(looprun==1)
			{
			//cout<<"Searching courselist for classes less than 5.\n";
			looprun = courselist.search(coursekey);//???
			if (looprun==1)
				{
				notapprovedoutfile<<"\n\nThis course is not approved.\n";
				removednode=courselist.getnodedata();
				printdata(removednode, notapprovedoutfile);
				notapprovedoutfile<<"\nThese people were on the roster.\n";
				roster[removednode.refnum-1].print(notapprovedoutfile);
				cout<<"\nremoving course node: "<<removednode.refnum<<"\n";
				courselist.removenode(removednode);
				}
			}
		}

	//print rosters to the output file
	rosteroutfile<<"ROSTERS for courses.\n";
	rosteroutfile<<"---------------------------\n\n";
	course tempcourse2;
	rosteroutfile<<"\nCourse ref numbers:\n";
	courselist.print(rosteroutfile);
	for(int i=0; i<20; i++)
		{
		tempcourse2.refnum=(i+1);
		if (courselist.search(tempcourse2))
			{
			rosteroutfile<<"\n\nThis is the roster for course reference number "<<(i+1)<<"\n\n";
			roster[i].print(rosteroutfile);
			}
		}
	return 0;
	}//end main



