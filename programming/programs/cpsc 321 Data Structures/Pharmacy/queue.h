//#ifdef QUEUE_H
//#define QUEUE_H
#include "list.h"
template <class QUEUETYPE>

class queue :private list<QUEUETYPE>
	{
	public:
		void enqueue (const QUEUETYPE &d)
			{insertatfront(d);}
			//purpose: inserts a node at the beginning of the list
		int dequeue (QUEUETYPE &d)
			{return removefromrear(d);}
			//purpose: removes the node at the rear of the list
			//it returns an integer (1=successful; 0=unsuccessful)
		int queueisempty() const
			{return isempty();}
         //purpose: tells if the list is empty
		   //it returns an integer (1=true; 0=false)
		void printqueue() const
			{print();}
			//purpose: prints the list node by node
			//requires a printdata friend function that prints a node
	};
	//#endif


