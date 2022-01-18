#ifndef LIST_H
#define LIST_H

#include <iostream.h>
#include <assert.h>
#include "listnd.h"

template< class NODETYPE >
class list
	{
	friend void printdata(const NODETYPE*);
		//purpose: friend that prints a node of the list
	friend void printdata(const NODETYPE*, ofstream);
		//purpose: friend that prints the node to a file
	friend int compare(const NODETYPE, const NODETYPE);
		//purpose: friend used to know when to stop searching the list
	friend int validatefriend(&NODETYPE);
		//purpose: friend to validate a node
public:
	list();
		// purpose:constructor
	~list();
		// purpose: destructor
	void insertatfront( const NODETYPE & );
		//purpose: inserts a node at the beginning of the list
	void insertatrear( const NODETYPE & );
		//purpose: inserts a node at the end of the list
	int removefromfront( NODETYPE & );
		//purpose: removes the node at the front of the list
		//it returns an integer (1=successful; 0=unsuccessful)
	int removefromrear( NODETYPE & );
		//purpose: removes the node from the rear of the list
		//it returns an integer (1=successful; 0=unsuccessful)
	int isempty() const;
		//purpose: tells if the list is empty
		//it returns an integer (1=true; 0=false)
	void print() const;
		//purpose: prints the list node by node
		//requires a printdata friend function that prints a node
	void print(ofstream &) const;
		//purpose: prints the list node by node to a file
		//requires a printdata friend function that prints a node
		//and it requires a file to be open
	int search(const NODETYPE);
		//purpose: can be used to search for a specific node or used to find out
		//where to insert a node
	void insertnode(const NODETYPE &);
		//purpose: used to to insert a node in the list
		//it inserts the node at the currentptr position
		//ths search function can be called to set currentptr
		//this function calls insertatfront and insertatrear
	void removenode(NODETYPE &);
		//purpose: used to to remove a node in the list
		//it removes the node at the currentptr position
		//ths search function can be called to set currentptr
		//this function calls removefromfront and removefromrear
	int validate(NODETYPE);
		//purpose: used to validate a node
	NODETYPE getnodedata();
		//purpose: used to return the data at the currentptr
private:
	listnode< NODETYPE > *firstptr;  // pointer to first node
	listnode< NODETYPE > *lastptr;   // pointer to last node
	listnode< NODETYPE > *currentptr; //pointer to the current node
	listnode< NODETYPE > *getnewnode( const NODETYPE & );
		//purpose: to allocate a new node
	};

//constructor
template< class NODETYPE >
list< NODETYPE >::list() : firstptr( 0 ), lastptr( 0 ) { }


// Destructor
template< class NODETYPE >
list< NODETYPE >::~list()
	{
	if ( !isempty() )
		{
		listnode< NODETYPE > *tempptr;
		currentptr = firstptr;
		while ( currentptr != 0 )
			{
			tempptr = currentptr;
			currentptr = currentptr->nextptr;
			delete tempptr;
			}
		}
	}


// Insert a node at the front of the list
template< class NODETYPE >
void list< NODETYPE >::insertatfront( const NODETYPE &value )
	{
	listnode< NODETYPE > *newptr = getnewnode( value );
	if (isempty())
		{
		firstptr=newptr;
		lastptr=newptr;
		}
	else
		{
		newptr->nextptr = firstptr;
		firstptr = newptr;
		}
	}


// Insert a node at the back of the list
template< class NODETYPE >
void list< NODETYPE >::insertatrear( const NODETYPE &value )
	{
	listnode< NODETYPE > *newptr = getnewnode( value );
	if ( isempty() )
		{
		firstptr=newptr;
		lastptr=newptr;
		}
	else
		{
		lastptr->nextptr = newptr;
		lastptr = newptr;
		}
	}


// Delete node from the front of the list
template<class NODETYPE>
int list<NODETYPE>::removefromfront(NODETYPE &value)
	{
	if (isempty())
		return 0;
	else
		{
		listnode<NODETYPE> *tempptr=firstptr;
		if (firstptr==lastptr)
			firstptr=lastptr = 0;
		else
			firstptr=firstptr->nextptr;
		value=tempptr->data;
		delete tempptr;
		return 1;
		}
	}


// Delete node from the rear of the list
template< class NODETYPE >
int list<NODETYPE>::removefromrear(NODETYPE &value )
	{
	if (isempty())
	return 0;
	else
		{
		listnode<NODETYPE> *tempptr=lastptr;
		if (firstptr ==lastptr)
			{
			firstptr = 0;
			lastptr = 0;
			}
		else
			{
			currentptr = firstptr;
			while ( currentptr->nextptr != lastptr )
				currentptr = currentptr->nextptr;
			lastptr = currentptr;
			currentptr->nextptr = 0;
			}
		value = tempptr->data;
		delete tempptr;
		return 1;
		}
	}


// Is the list empty?
template< class NODETYPE >
int list< NODETYPE >::isempty() const
	{
	return firstptr==0;
	}


// Return a pointer to a newly allocated node
template<class NODETYPE>
listnode<NODETYPE > *list<NODETYPE>::getnewnode(const NODETYPE &value )
	{
	listnode<NODETYPE> *ptr = new listnode< NODETYPE >( value );
	assert( ptr != 0 );
	return ptr;
	}


// Display the List
template< class NODETYPE >
void list< NODETYPE >::print() const
	{
	if ( isempty() )
		{
		cout << "The list is empty\n\n";
		return;
		}
	listnode< NODETYPE > *currentptr = firstptr;
	cout << "The list is: ";
	while ( currentptr != 0 )
		{
		printdata(currentptr->data);
		currentptr = currentptr->nextptr;
		}
	cout << "\n\n";
	}



// Display the List
template< class NODETYPE >
void list< NODETYPE >::print(ofstream &outfile) const
	{
	if ( isempty() )
		{
		outfile << "The list is empty\n\n";
		return;
		}
	listnode< NODETYPE > *currentptr = firstptr;
	outfile << "The list is: ";
	while ( currentptr != 0 )
		{
		printdata(currentptr->data, outfile);
		currentptr = currentptr->nextptr;
		}
	outfile<< "\n\n";
	}




//search
template<class NODETYPE>
int list<NODETYPE>::search(const NODETYPE key)
	{
	int contin = 1;
	if (isempty())
		{
		return 0;
		}
	else
		{
		currentptr=firstptr;
		while (contin==1)
			{
			if(currentptr!=0)
				{
				if (compare(currentptr->data, key))
					{
					currentptr=currentptr->nextptr;
					contin=1;
					}
				else
					contin=0;
				}
			else
				contin=0;
			}

		if (currentptr==0)
			{
			return 0;//return false
			}
		else
			{
			return 1;//return true
			}
		}
	}


//deletenode from anywhere
template<class NODETYPE>
void list<NODETYPE>::removenode (NODETYPE &value)
	{
	if ((currentptr==firstptr)&&(currentptr==lastptr))
		{
		firstptr=0;
		lastptr=0;
		value=currentptr->data;
		delete(currentptr);
		}
	else if(currentptr==lastptr)
		removefromrear(value);
	else if(currentptr==firstptr)
		removefromfront(value);
	else
		{
		listnode<NODETYPE> *tempptr=firstptr;
		while(tempptr->nextptr!=currentptr)
			tempptr=tempptr->nextptr;
		tempptr->nextptr=currentptr->nextptr;
		value=currentptr->data;
		delete(currentptr);
		}
	}

//insert a node anywhere
template<class NODETYPE>
void list<NODETYPE>::insertnode (const NODETYPE &value)
	{
	listnode<NODETYPE> *tempptr=new listnode<NODETYPE>(value);
	listnode<NODETYPE> *temp2ptr=new listnode<NODETYPE>(value);
	if(isempty())
		{
		firstptr=tempptr;
		lastptr=tempptr;
		}
	else if(currentptr==0)
		insertatrear(value);
	else if(currentptr==firstptr)
		insertatfront(value);
	else
		{
		temp2ptr=firstptr;
		while(temp2ptr->nextptr!=currentptr)
			temp2ptr=temp2ptr->nextptr;
		tempptr->nextptr=currentptr;
		temp2ptr->nextptr=tempptr;
		}
	}

template<class NODETYPE>
int list<NODETYPE>::validate (NODETYPE key)
	{

	currentptr=firstptr;
	int contin=1;
	while((contin==1)&&(currentptr!=0))
		{
		if (currentptr!=0)
			{
			if (compare(currentptr->data,key))
				currentptr=currentptr->nextptr;
			else
				contin=0;
			}
		}
	if(currentptr!=0)
		{
		return validatefriend(currentptr->data);
		}
	else
		return 0;
	}

template<class NODETYPE>
NODETYPE list<NODETYPE>::getnodedata ()
	{
	return (currentptr->data);
	}


#endif
