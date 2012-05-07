/*=================================================
 File     : List.h
 Function : User's generic list container
 Author   : Po-Han, Chen
 Version  : 1.0.0
 Last Modified : Thu May  3 16:44:25 CST 2012
 Copyright: Copyright (C) 2012 Po-Han, Chen
 ==================================================*/

#ifndef USERLIST_H
#define USERLIST_H

#ifndef NULL
#define NULL 0
#endif 

#define START_EXCEPTION try {
#define END_EXCEPTION( str ) _END_EXCEPTION( str )
#define _END_EXCEPTION( str ) } catch ( ... ) \
{ std::cout << "Backtracking : in " << __FILE__ << " line-" << __LINE__ << " " << str << "\n"; throw; }

#include <iostream>
using std::cout;
using std::endl;

#include "ErrorMessage.h"

namespace user {

template <typename T>
class List 
{
	//-------------------- Public --------------------//
    public :

		struct Iterator;
		struct Node; 
		typedef Iterator iterator;

        typedef List<T> listType;
        typedef T elementType;

		// Constructor & Destructor
		explicit List ();
		explicit List ( const unsigned &num, const T &obj );
		List ( const List<T> & );
	   ~List () throw ();

		// Get and set attribute
		T &getBack  () const;
		T &getFront () const;

		T  popBack  ();
		T  popFront ();

		void pushBack  ( const T & );
		void pushFront ( const T & );

	    unsigned insert ( const unsigned &index, const T & ); // Insert before list[index].
		Iterator insert ( Iterator &iter, const T & );
		T remove ( const unsigned &index ); // Remove list[index] and return it.
		T remove ( Iterator &iter ); 

		void reverse ();
		void clear ();

		unsigned size () const;

		bool isEmpty () const;
		
		Iterator begin () const;
		Iterator end   () const;
		Iterator rbegin () const;
		Iterator rend   () const;

		void append( const List<T> & );
		void traverse () const;

	    // Operator
	    List<T> &operator= ( const List<T> & );
	    T &operator[] ( const unsigned &index ) const;
	    T &operator* () const;

	//-------------------- Private --------------------//
    private :

        Node *head_,
			 *tail_;

        unsigned length_;

		Node *f_copy_  ( Node *, Node *, const unsigned & );
		void f_insert_ ( Node *, Node *, const T & );
		T	 f_remove_ ( Node *, Node * );
};

template <typename T>
struct List<T>::Iterator
{
	//-------------------- Public --------------------//

	// Deference
	T &operator* () const;
	T *operator-> () const;

	// Operator
	Iterator operator++ ( int );
	Iterator &operator++ ();
	Iterator operator-- ( int );
	Iterator &operator-- ();

	Iterator operator+ ( const unsigned & );
	Iterator operator- ( const unsigned & );
	Iterator operator+=( const unsigned & );
	Iterator operator-=( const unsigned & );
	
	bool operator== ( const Iterator &rhs );
	bool operator!= ( const Iterator &rhs );

	Iterator &operator= ( const Iterator &rhs );
		
	Iterator ();
	Iterator ( const Iterator &rhs );
	Iterator ( List<T>::Node *rhs );
	~Iterator() throw ();

	List<T>::Node *node;

	// For remove action
	static List<T>::Node *nodeTemp;

	static bool isNodeTempReleased ();

	//-------------------- Implementation --------------------//
	private :

		void f_toRight_ ( Iterator & );
		void f_toLeft_  ( Iterator & );
};


///////////////////////////////////////////////////////////////////////
////////////////////////  Implementation  /////////////////////////////
///////////////////////////////////////////////////////////////////////

////////////////////////// Node /////////////////////////////////
template <typename T>
struct List<T>::Node 
{
	//-------------------- Public --------------------//
	
	explicit Node ();
	explicit Node ( const T &obj, Node *rp, Node *lp );
	explicit Node ( const Node & );
   ~Node () throw ();

	Node &operator= ( const Node & );

	Node *rlink,
		 *llink;

	T object;
};

template <typename T>
List<T>::Node::Node () : rlink( NULL ),
					     llink( NULL ),
					     object() {}

template <typename T> 
List<T>::Node::Node ( const T &obj, Node *rp, Node *lp ) : rlink( rp ),
														   llink( lp ) ,
														   object( obj ) {}
template <typename T> 
List<T>::Node::Node ( const Node &rhs ) : rlink( rhs.rlink ),
										  llink( rhs.llink ),
										  object( rhs.object ) {}
template <typename T>
List<T>::Node::~Node ()  throw ()
{ 
	if ( rlink != NULL ) 
		delete rlink;
	rlink = NULL;
#ifdef COUNT_NODE	
	cout << "Node destroy!" << endl;
#endif
}

template <typename T>
typename List<T>::Node &
List<T>::Node::operator= ( const Node &rhs )
{
	rlink = rhs.rlink;
	llink = rhs.llink;
	object = rhs.object;
	return *this;
}

////////////////////////// List /////////////////////////////////

template <typename T> 
List<T>::List () : head_( NULL ),
				   tail_( NULL ),
				   length_(0) {}

template <typename T> 
List<T>::List ( const unsigned &num, const T &obj ) : head_( NULL ), 
													  tail_( NULL ),
													  length_( num )
{
	if ( length_ != 0 ) {
		head_ = new Node( obj, NULL, NULL ); //Construct first node
		Node *current = head_;
		for ( unsigned i = 1; i < length_; i++ ) {
			current->rlink = new Node( obj, NULL, current );
			current = current->rlink;
		}
		tail_ = current;
	}
}

template <typename T>
List<T>::List ( const List<T> &rhs ) : head_( NULL ), 
									   tail_( NULL ),
									   length_( rhs.length_ )
{
	if ( rhs.length_ != 0 ) {
		head_ = new Node( rhs.head_->object, NULL, NULL );
		tail_ = f_copy_( head_, rhs.head_, length_ );
	}
}

template <typename T>
typename List<T>::Node *
List<T>::f_copy_ ( Node *current, Node *rhs_current, const unsigned &end )
{
	for ( unsigned i = 1; i < end; i++ ) {
		current->rlink = new Node( rhs_current->rlink->object, NULL, current );
		current = current->rlink;
		rhs_current = rhs_current->rlink;
	}
	return current;
}

template <typename T>
List<T>::~List () throw ()
{ 
	if ( head_ ) 
		delete head_;
	head_ = NULL;
	tail_ = NULL;
}

template <typename T>
List<T> &
List<T>::operator= ( const List<T> &rhs )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( head_ ) {
		delete head_;
		head_ = NULL;
	}
	if ( rhs.length_ != 0 && head_ != rhs.head_ ) {
		head_ = new Node( rhs.head_->object, NULL, NULL );
		tail_ = f_copy_( head_, rhs.head_, rhs.length_ );
	}
	length_ = rhs.length_;
	return *this;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::operator= ()" );
#endif
}

template <typename T>
T & 
List<T>::operator[] ( const unsigned &index ) const
{
#ifndef NDEBUG
	if ( index > length_ || index < 0 )
		throw IndexError( "in List<T>::operator[] => index out of bound", index, length_ );
#endif
	// Traverse from head_
	if ( (length_ - index) >= length_ / 2 ) {
		Node *current = head_;
		for ( unsigned i = 0; i < index; i++ )
			current = current->rlink;
		return current->object;
	}
	// Traverse from tail_
	else {
		Node *current = tail_;
		for ( unsigned i = 0; i < length_ - index - 1; i++ )
			current = current->llink;
		return current->object;
	}
}

template <typename T>
T &
List<T>::operator* () const
{
#ifndef NDEBUG
	if ( head_ == NULL )
		throw "in List<T>::operator*() ==> head_ == NULL !";
#endif
	return head_->object; 
}

template <typename T>
unsigned
List<T>::insert ( const unsigned &index, const T &obj )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
#ifndef NDEBUG
	if ( index > length_ || index < 0 )
		throw IndexError( "in List<T>::insert => index out of bound", index, length_ );
#endif
	if ( index == 0 )
		pushFront(obj);
	else if ( (length_ - index) >= length_ / 2 ) {
		Node *current = head_;
		for ( unsigned i = 0; i < index; i++ )
			current  = current->rlink;
		f_insert_( current->llink, current, obj );
	} 
	else {
		Node *current = tail_;
		for ( unsigned i = 0; i < length_ - index - 1; i++ )
			current = current->llink;
		f_insert_( current->llink, current, obj );
	}
	return index;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::insert ( const unsigned &, const T & )" );
#endif
}

template <typename T>
void
List<T>::f_insert_ ( Node *previous, Node *current, const T &obj )
{
	previous->rlink = new Node( obj, current, previous );
	current->llink  = previous->rlink;
	++length_;
}

template <typename T> 
typename List<T>::Iterator
List<T>::insert ( Iterator &iter, const T &obj )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	unsigned insertIndex = 0;
	Node *current = head_;
	for ( unsigned i = 0; i < length_; i++ ) {
		if ( current == iter.node ) {
			insertIndex = i;
			break;
		}
		current = current->rlink;
	}
	insert( insertIndex, obj );
	return iter;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::insert ( Iterator &, const T & )" );
#endif
}

template <typename T>
T &
List<T>::getBack () const
{ 
#ifndef NDEBUG
	if ( tail_ == NULL )
		throw "in List<T>::getBack() ==> tail_ == NULL !";
#endif
	return tail_->object; 
}

template <typename T>
T &
List<T>::getFront () const
{ 
#ifndef NDEBUG
	if ( head_ == NULL )
		throw "in List<T>::getFront() ==> head_ == NULL !";
#endif
	return head_->object;
}

template <typename T>
void 
List<T>::pushBack ( const T &obj )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( head_ ) {
		tail_->rlink = new Node( obj, NULL, tail_ );
		tail_ = tail_->rlink;
		++length_;
	}
	else {
		head_ = new Node( obj, NULL, NULL );	
		tail_ = head_;
		++length_;
	}
#ifndef NDEBUG
END_EXCEPTION( "List<T>::pushBack ()" );
#endif
}

template <typename T>
void 
List<T>::pushFront ( const T &obj )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( head_ ) {
		head_->llink = new Node( obj, head_, NULL );
		head_ = head_->llink;
		++length_;
	}
	else {
		head_ = new Node( obj, NULL, NULL );	
		tail_ = head_;
		++length_;
	}
#ifndef NDEBUG
END_EXCEPTION( "List<T>::pushFront ( const T & )" );
#endif
}

template <typename T>
T 
List<T>::popBack ()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
#ifndef NDEBUG
	if ( length_ == 0 )
		throw "in List<T>::popBack() ==> length_ == 0 cannot pop !";
#endif
	T obj( tail_->object );
	if ( length_ > 1 ) {
		tail_ = tail_->llink;
		delete tail_->rlink;
		tail_->rlink = NULL;
	}
	else {
		delete head_;
		head_ = NULL;
		tail_ = NULL;
	}
	--length_;
	return obj;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::popBack()" );
#endif
}

template <typename T>
T 
List<T>::popFront ()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
#ifndef NDEBUG
	if ( length_ == 0 )
		throw "in List<T>::popFront() ==> length_ == 0 cannot pop !";
#endif
	T obj( head_->object );
	if ( length_ > 1 ) {
		Node *temp = head_->rlink;
		head_->rlink = NULL;
		delete head_;
		temp->llink = NULL;
		head_ = temp;
	}
	else {
		delete head_;
		head_ = NULL;
		tail_ = NULL;
	}
	--length_;
	return obj;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::popFront ()" );
#endif
}

template <typename T>
T 
List<T>::remove ( const unsigned &index )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
#ifndef NDEBUG
	if ( index > length_ || index < 0 )
		throw IndexError( "in List<T>::remove => index out of bound", index, length_ );
#endif
	if ( index == 0 )
		return popFront();
	else if ( index == length_ - 1)
		return popBack();
	else if ( (length_ - index) >= length_ / 2 ) {
		Node *current = head_;
		for ( unsigned i = 0; i < index; i++ )
			current = current->rlink;
		return f_remove_( current->llink, current );
	} 
	else {
		Node *current = tail_;
		for ( unsigned i = 0; i < length_ - index - 1; i++ )
			current  = current->llink;
		return f_remove_( current->llink, current );
	}
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::remove ( const unsigned & )" );
#endif
}

template <typename T> 
T
List<T>::remove( Iterator &iter )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	Node *current = head_;
	unsigned removeIndex = 0;
	for ( unsigned i = 0; i < length_; i++ ) {
		if ( current == iter.node ) {
			removeIndex = i;
			break;
		}
		current = current->rlink;
	}
	Iterator::nodeTemp = new Node ( iter.node->object, current->rlink, NULL );
	iter.node = Iterator::nodeTemp;
	T tempObj( current->object );
	this->remove( removeIndex );
	return tempObj;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::remove ( Iterator & )" );
#endif
}

template <typename T>
T
List<T>::f_remove_ ( Node *previous, Node *current )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	Node *tempNode = current->rlink;
	T obj( current->object );
	current->rlink = NULL;
	delete current;
	previous->rlink = tempNode;
	tempNode->llink = previous;
	--length_;
	return obj;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::f_remove_ ( Node *, Node * )" );
#endif
}

template <typename T> 
void
List<T>::reverse ()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	Node *left = head_, *right = tail_;
	T temp;
	for ( unsigned i = 0; i < length_ / 2; i++ ) {
		temp = left->object;
		left->object = right->object;
		right->object = temp;
		left  = left ->rlink;
		right = right->llink;
	}
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::reverse ()" );
#endif
}

template <typename T>
void
List<T>::clear ()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( head_ ) {
		delete head_;
		head_ = NULL;
	}
	length_ = 0;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::clear ()" );
#endif
}

template <typename T>
void 
List<T>::append ( const List<T> &rhs )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( rhs.length_ != 0 ) {
		Node *rhs_current = rhs.head_;
		if ( length_ == 0 ) {
			head_ = new Node( rhs_current->object, NULL, NULL );
			tail_ = f_copy_( head_, rhs.head_, rhs.length_ );
			length_ = rhs.length_;
		}
		else {
			tail_ = new Node( rhs_current->object, NULL, tail_ );
			tail_->llink->rlink = tail_;
			tail_ = f_copy_( tail_, rhs.head_, rhs.length_ );
			length_ += rhs.length_;
		}
	}
#ifndef NDEBUG
END_EXCEPTION( "List<T>::append ( const List<T> & )" );
#endif
}

template <typename T>
void
List<T>::traverse () const
{
	if ( length_ == 0 ) {
		cout << "List == > NULL\n";
		return ;
	}
	Node *current = head_;
	for ( unsigned i = 0; current != NULL; i++ ) {
		cout << current->object << " ";
		current = current->rlink;
	}
}

template <typename T>
bool 
List<T>::isEmpty () const
{
	return length_ == 0; 
}

template <typename T>
typename List<T>::Iterator
List<T>::begin () const
{
	if ( head_ == NULL )
		return Iterator();
	return Iterator( head_ );
}

template <typename T>
typename List<T>::Iterator
List<T>::end () const
{
	if ( tail_ == NULL )
		return Iterator();
	return Iterator( tail_->rlink );
}

template <typename T>
typename List<T>::Iterator
List<T>::rbegin () const
{
	if ( tail_ == NULL )
		return Iterator();
	return Iterator( tail_ );
}

template <typename T>
typename List<T>::Iterator
List<T>::rend () const
{
	if ( head_ == NULL )
		return Iterator();
	return Iterator( head_->llink );
}

template <typename T> 
unsigned 
List<T>::size () const
{
	return length_;
}

////////////////////////// Iterator /////////////////////////////////

template <typename T> 
typename List<T>::Node *List<T>::Iterator::nodeTemp = NULL;

template <typename T>
List<T>::Iterator::Iterator () : node( NULL ) {}

template <typename T>
List<T>::Iterator::Iterator ( const Iterator &rhs ) : node( rhs.node ) {}

template <typename T>
List<T>::Iterator::Iterator ( List<T>::Node *rhs ) : node( rhs ) {}

template <typename T>
List<T>::Iterator::~Iterator () throw ()
{
	if ( nodeTemp ) {
		nodeTemp->rlink = NULL;
		delete nodeTemp;
		nodeTemp = NULL;
	}
}

template <typename T>
typename List<T>::Iterator &
List<T>::Iterator::operator= ( const Iterator &rhs ) 
{
	node = rhs.node;
	return *this; 
} 

template <typename T>
T &
List<T>::Iterator::operator* () const 
{
#ifndef NDEBUG
	if ( node == NULL )
		throw PointerError( "in List<T>::Iterator::operator*() ==> node == NULL !", node );
	else if ( node == nodeTemp )
		throw PointerError( "in List<T>::Iterator::operator*() ==> node == nodeTemp !", node );
#endif
	return node->object; 
}

template <typename T>
T *
List<T>::Iterator::operator-> () const
{
#ifndef NDEBUG					
	if ( node == NULL )
		throw PointerError( "in List<T>::Iterator::operator->() ==> node == NULL !", node );
#endif
	return &(node->object);
}

template <typename T>
typename List<T>::Iterator 
List<T>::Iterator::operator++ ( int )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	Iterator tempIter( *this );
	f_toRight_( *this );
	return tempIter;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::Iterator::operator++ ( int )" );
#endif
}

template <typename T>
typename List<T>::Iterator &
List<T>::Iterator::operator++ () 
{
	this->operator++( int( 0 ) );
	return *this;
}

template <typename T>
typename List<T>::Iterator 
List<T>::Iterator::operator-- ( int )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	Iterator tempIter( *this );
	f_toLeft_( *this );
	return tempIter;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::Iterator::operator-- ( int )" );
#endif
}

template <typename T>
typename List<T>::Iterator &
List<T>::Iterator::operator-- ()
{
	this->operator--( 0 );
	return *this;
}

template <typename T>
bool 
List<T>::Iterator::operator== ( const Iterator &rhs ) 
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	// For List<T>::remove implementation  
	if ( node && node->rlink == NULL && node == nodeTemp )
		return false;
	return node == rhs.node;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::Iterator::operator== ( const Iterator & )" );
#endif
}

template <typename T>
bool 
List<T>::Iterator::operator!= ( const Iterator &rhs ) 
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	// For List<T>::remove implementation  
	if ( node && node->rlink == NULL && node == nodeTemp ) 
		return false;
	return node != rhs.node;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::Iterator::operator!= ( const Iterator & )" );
#endif
}

template <typename T> 
typename List<T>::Iterator
List<T>::Iterator::operator+ ( const unsigned &index ) 
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	Iterator temp( *this );
	for ( unsigned i = 0; i < index; i++ )
		f_toRight_( temp );
	return temp;
#ifndef NDEBUG
END_EXCEPTION( "List<T>::Iterator::operator+ ( const unsigned & )" );
#endif
}

template <typename T> 
typename List<T>::Iterator
List<T>::Iterator::operator- ( const unsigned &index ) 
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	Iterator temp( *this );
	for ( unsigned i = 0; i < index; i++ )
		f_toLeft_( temp );
	return temp;
#ifndef NDEBUG
	END_EXCEPTION( "List<T>::Iterator::operator- ( const unsigned & )" );
#endif
}

template <typename T> 
typename List<T>::Iterator
List<T>::Iterator::operator+= ( const unsigned &index )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	return *this = *this + index;
#ifndef NDEBUG
END_EXCEPTION( "List<T>::Iterator::operator+= ( const unsigned & )" );
#endif
}

template <typename T> 
typename List<T>::Iterator
List<T>::Iterator::operator-= ( const unsigned &index )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	return *this = *this - index;
#ifndef NDEBUG
END_EXCEPTION( "List<T>::Iterator::operator-= ( const unsigned & )" );
#endif
}

template <typename T>
bool
List<T>::Iterator::isNodeTempReleased () 
{
	return nodeTemp == NULL;
}

template <typename T>
void
List<T>::Iterator::f_toRight_ ( Iterator &iter )
{
#ifndef NDEBUG
	if ( iter.node == NULL )
		throw PointerError( "in List<T>::Iterator f_toRight_() ==> iter.node is NULL !", iter.node );
#endif
	iter.node = iter.node->rlink;
}

template <typename T>
void
List<T>::Iterator::f_toLeft_ ( Iterator &iter )
{
#ifndef NDEBUG
	if ( iter.node == NULL )
		throw PointerError( "in List<T>::Iterator f_toRight_() ==> iter.node is NULL !", iter.node );
#endif
	iter.node = iter.node->llink;
}

}
#endif



