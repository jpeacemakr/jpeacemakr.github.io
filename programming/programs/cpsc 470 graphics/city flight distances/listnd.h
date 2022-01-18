#ifndef LISTND_H
#define LISTND_H

template<class NODETYPE> class list;  // forward declaration to the list class

template<class NODETYPE>
class listnode
	{
	friend class list<NODETYPE>; // makes list a friend
	public:
		listnode(const NODETYPE &);  // constructor
		NODETYPE getdata() const;      // returns the data in the node
	private:
		NODETYPE data;                 // data
		listnode<NODETYPE> *nextptr; // next node in the list
	};


template<class NODETYPE>
listnode<NODETYPE>::listnode(const NODETYPE &info)
   : data( info ), nextptr( 0 ) { }


template<class NODETYPE>
NODETYPE listnode<NODETYPE>::getdata() const {return data;}

#endif
