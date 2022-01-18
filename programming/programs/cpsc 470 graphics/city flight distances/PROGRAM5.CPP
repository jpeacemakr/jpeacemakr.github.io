////////////////////////////////////////////////////////////////////////////
//	title:program5.cpp
// author:james peacemaker
// class:CPSC 321
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose:this program is designed to simulate travel flight distances between
//cities. The cities are put into a weighted graph. Information about the cities
//is read into from a file.
////////////////////////////////////////////////////////////////////////////



#include <iostream.h>
#include <stdio.h>
#include <iomanip.h>
#include <string.h>
#include <fstream.h>
#include <stdlib.h>
#include <dos.h>
#include "list.h"
#include "listnd.h"
#include "stack.h"
#include "queue.h"
#include "graph.h"

//struct of a graph edge between two vertices
struct edgetype
	{
	int vertex;     //vertex of the tocity
	char name[30];  //name of the to city
	int weight;     //distance to the to city
	};

//struct of a graph vertex
struct vertextype
	{
	int vertex;     //vertexof the fromcity
	char name[30];  //name of the fromcity
	int marked;     //whethter or not the city has ben visited
	list<edgetype> edges; //list of the adjacent tocities
	};


//friend function for list to compare two integers
int compare(const edgetype first, const edgetype second)
	{
	if (first.vertex==second.vertex)
		return 1;
	else return 0;
	};


//friend function for list used to compare two integers
int compare(const int first, const int second)
	{
	if (first== second)
		return 1;
	else return 0;
	};


void printdata(const int num)
	{
	cout<<num<<" ";
	};


void printdata(const edgetype tempedge)
	{
   cout<<tempedge.vertex<<") ";
	cout<<tempedge.name<<" is ";  //name of the to city
	cout<<tempedge.weight<<" miles away."<<endl;     //distance to the to city
	};

void nodecopy(int &temp1, int &temp2)
	{
	temp1=temp2;
	};

void nodecopy(edgetype &temp1, edgetype &temp2)
	{
	temp1.vertex=temp2.vertex;     //vertex of the tocity
	strcpy(temp1.name, temp2.name);  //name of the to city
	temp1.weight=temp2.weight;     //distance to the to city
   };



void main()
	{
	vertextype temp;   //a temp vertex
	vertextype temp2;  //a temp vertex
	int citynumber;   //holds a vertex value
	char cityname[50]; //holds a temp name
	int fromcity;  //holds a value for the fromcity
	int tocity; //holds a value for the tocity
	int code; //code for the
	int distance;  //temp weight(distance to another city)
	graphlist<edgetype, vertextype> thegraph;//the graph of cities
	int weight;

	//open the file that holds the information
	char datfilename[20];
	cout<<"\n\nEnter the name of the file to read data from: ";
	cin>>datfilename;
	ifstream datfile(datfilename);
   cout<<"Press Enter.\n\n";
	cin.get();
	datfile>>code;

	while (!datfile.eof())//while not end of file
		{
		if (datfile.eof())
			{break;}
		cout<<code<<"    ";
		if (code == 1) // add city
			{
			datfile>>citynumber;
			cout<<"   "<<citynumber;
			temp.vertex=citynumber;
			datfile.getline(cityname,50);
			strcpy(temp.name,cityname);
			cout<<"    "<<cityname;
			thegraph.addvertex(temp);
			cout<<endl;
			}

		if (code == 2) // add route
			{
			datfile>>fromcity;
			cout<<fromcity<<"    ";
			datfile>>tocity;
			cout<<tocity<<"    ";
			datfile>>distance;//(weight)
			cout<<distance;
			thegraph.addedge(fromcity,tocity,distance);
			cout<<endl;
			}

		if (code == 3) // breadth first search
			{
			cout<<"Breadth first search: \n";
			datfile>>fromcity;
			cout<<"fromcity: ";
			cout<<fromcity<<"    ";
			temp.vertex=fromcity;
			datfile>>tocity;
			cout<<"tocity: ";
			cout<<tocity<<endl;
			temp2.vertex=tocity;
			thegraph.breadthfirstsearch(temp, temp2);
			cout<<endl;
			}

		if (code == 4) //depth first search
			{
			cout<<"Depth first search: \n";
			datfile>>fromcity;
			cout<<"fromcity: ";
			cout<<fromcity<<"    ";
			temp.vertex=fromcity;
			datfile>>tocity;
			cout<<"tocity: ";
			cout<<tocity<<endl;
			temp2.vertex=tocity;
			thegraph.depthfirstsearch(temp, temp2);
			cout<<endl;
			}

		if (code == 5) //shortest path
			{
			datfile>>fromcity;
			cout<<fromcity<<"    ";
			temp.vertex=fromcity;
			datfile>>tocity;
			cout<<tocity<<"    ";
			temp2.vertex=tocity;
			thegraph.shortestpath(temp, temp2);
			cout<<endl;
			}

		if (code == 6) //weight is
			{
			datfile>>fromcity;
			cout<<fromcity<<"    ";
			datfile>>tocity;
			cout<<tocity<<"    ";
			weight=thegraph.getweight(fromcity, tocity);
			if (weight!=-1)
				{
				cout<<"the weight is: ";
				cout<<weight;
				cout<<endl;
				}
			else
				{cout<<"Vertices are not connected.\nCannot find weight.\n";}
			}
		//thegraph.printgraph();
		cout<<"Press Enter.\n\n";
		cin.get();
		code=7;
		datfile>>code;
		}//until file is empty
	};
