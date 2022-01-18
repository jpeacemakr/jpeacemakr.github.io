//#ifdef STACK_H
//#define STACK_H
#include "list.h"
template <class STACKTYPE>
class stack
	{
	public:
		void push (const STACKTYPE &d)
			{s.insertatfront(d);}
         //purpose: inserts a node at the beginning of the list
		int pop (STACKTYPE &d)
			{return s.removefromfront(d);}
         //purpose: removes the node at the front of the list
			//it returns an integer (1=successful; 0=unsuccessful)
		int stackisempty() const
			{return s.isempty();}
         //purpose: tells if the list is empty
		   //it returns an integer (1=true; 0=false)
		void printstack() const
			{s.print();}
         //purpose: prints the list node by node
			//requires a printdata friend function that prints a node
	private:
		list <STACKTYPE>s;
	};
   //#endif


