/***************************************************
** File: List.h
** Function: User's generic double link list 
** Author: Po-Han, Chen
** Version: 1.0.0
** Last Modified: Tue Apr 10 16:31:28 CST 2012
** Copyright: Copyright (C) 2012 Po-Han, Chen
****************************************************/

#ifndef USERLIST_H
#define USERLIST_H

#ifndef NDEBUG
#include <cassert> 
#endif

#ifndef NULL
#define NULL 0
#endif 

#include <iostream>
using std::cout;
using std::endl;

namespace user {

template <typename T> class List;

template <typename T>
class Node 
{
    friend class List<T>;

	//-------------------- Private --------------------//
    private :

		/*******  Constructor & Destructor *******/	
		Node ();
		Node ( const T &obj, Node<T> *rp, Node<T> *lp );
		Node ( const Node<T> & );
	   ~Node ();
	
	   	/*******  Operator  *******/
	   	Node<T> &operator= ( const Node<T> & );

        Node<T> *rlink_,
                *llink_;

        T object_;
};

template <typename T>
Node<T>::Node () : rlink_( NULL ),
				   llink_( NULL ),
				   object_() {}

template <typename T> 
Node<T>::Node ( const T &obj, Node<T> *rp, Node<T> *lp ) : rlink_( rp ),
														   llink_( lp ) ,
													  	   object_( obj ) {}
template <typename T> 
Node<T>::Node ( const Node<T> &rhs ) : rlink_( rhs.rlink_ ),
									   llink_( rhs.llink_ ),
									   object_( rhs.object_ ) {}
template <typename T>
Node<T>::~Node () 
{ 
	if ( rlink_ != NULL ) 
		delete rlink_;
#ifdef COUNT_NODE	
	cout << "Node destroy!" << endl;
#endif
}

template <typename T>
Node<T> &
Node<T>::operator= ( const Node<T> &rhs )
{
	rlink_ = rhs.rlink_;
	llink_ = rhs.llink_;
	object_ = rhs.object_;
	return *this;
}


template <typename T>
class List 
{
	//-------------------- Public --------------------//
    public :

        typedef Node<T> *iterator;
        typedef List<T> list_type;
        typedef T element_type;

		/*******  Constructor & Destructor  *******/
		List ();
		List ( const unsigned &num, const T &obj );
		List ( const List<T> & );
	   ~List ();

		/*******  Get and set attribute  *******/	
		T &getBack  ();
		T &getFront ();

		T  popBack  ();
		T  popFront ();

		void pushBack  ( const T & );
		void pushFront ( const T & );

	    void insert ( const unsigned &index, const T & ); // Insert before list[index].
		T    remove ( const unsigned &index ); // Remove list[index] and return it.

		unsigned size ();

		bool isEmpty ();
		
		iterator begin ();
		iterator end   ();

		void concatenate ( List<T> & );
		void traverse ();

	    /*******  Operator  *******/
	    List<T> &operator= ( const List<T> & );
	    T &operator[] ( const unsigned &index );
	    T &operator*  ();


    private :

        Node<T> *head_,
                *tail_,
                *current_,
                *previous_;

        unsigned length_;
};

template <typename T> 
List<T>::List () : head_( NULL ),
				   tail_( NULL ),
				   current_( NULL ),
				   previous_( NULL ),
				   length_(0) {}

template <typename T> 
List<T>::List ( const unsigned &num, const T &obj ) : head_( NULL ), 
													  tail_( NULL ),
													  current_( NULL ),
													  previous_( NULL ),
													  length_( num )
{
	if ( length_ != 0 ) {
		head_ = new Node<T>( obj, NULL, NULL ); //Construct first node
		current_ = head_;
		for ( unsigned i = 1; i < length_; i++ ) {
			current_->rlink_ = new Node<T>( obj, NULL, current_ );
			current_ = current_->rlink_;
		}
		tail_ = current_;
	}
}

template <typename T>
List<T>::List ( const List<T> &rhs ) : head_( NULL ), 
									   tail_( NULL ),
									   current_( NULL ),
									   previous_( NULL ),
									   length_( rhs.length_ )
{
	Node<T> *rhs_current_ = rhs.head_;
	if ( length_ != 0 ) {
		head_ = new Node<T>( rhs_current_->object_, NULL, NULL );
		current_ = head_;
		for ( unsigned i = 1; i < length_; i++ ) {
			current_->rlink_ = new Node<T>( (rhs_current_)->rlink_->object_, NULL, current_ );
			current_ = current_->rlink_;
			rhs_current_ = rhs_current_->rlink_;
		}
		tail_ = current_;
	}
}

template <typename T>
List<T>::~List () 
{ 
	if ( head_ ) 
		delete head_;
}

template <typename T>
List<T> &
List<T>::operator= ( const List<T> &rhs )
{
	if ( head_ )
		delete head_;
	length_ = rhs.length_;
	if ( length_ != 0 ) {
		head_ = new Node<T>( rhs.head_->object_, NULL, NULL );
		current_ = head_;
		Node<T> *rhs_current_ = rhs.head_;
		for ( unsigned i = 1; i < length_; i++ ) {
			current_->rlink_ = new Node<T>( (rhs_current_)->rlink_->object_, NULL, current_ );
			current_ = current_->rlink_;
			rhs_current_ = rhs_current_->rlink_;
		}
		tail_ = current_;
	}
	return *this;
}

template <typename T>
T & 
List<T>::operator[] ( const unsigned &index )
{
#ifndef NDEBUG
	assert ( index < length_ && index >= 0 );
#endif
	/*******  Traverse from head_  *******/
	if ( (length_ - index) >= length_ / 2 ) {
		current_ = head_;
		for ( unsigned i = 0; i < index; i++ )
			current_ = current_->rlink_;
		return current_->object_;
	}
	/*******  Traverse from tail_  *******/
	else {
		current_ = tail_;
		for ( unsigned i = 0; i < length_ - index - 1; i++ )
			current_ = current_->llink_;
		return current_->object_;
	}
}

template <typename T>
T &
List<T>::operator* () 
{
#ifndef NDEBUG
	assert( head_ != NULL );
#endif
	return head_->object_; 
}

template <typename T>
void
List<T>::insert ( const unsigned &index, const T &obj )
{
#ifndef NDEBUG
	assert ( index < length_ && index >= 0 );
#endif
	if ( index == 0 )
		pushFront(obj);
	else if ( (length_ - index) >= length_ / 2 ) {
		current_ = head_;
		for ( unsigned i = 0; i < index; i++ )
			current_  = current_->rlink_;
		previous_ = current_->llink_;
		previous_->rlink_ = new Node<T>( obj, current_, previous_ );
		current_->llink_ = previous_->rlink_;
		++length_;
	} 
	else {
		current_ = tail_;
		for ( unsigned i = 0; i < length_ - index; i++ )
			current_ = current_->llink_;
		previous_ = current_->rlink_;
		previous_->llink_ = new Node<T>( obj, previous_, current_ );
		current_->rlink_  = previous_->llink_;
		++length_;
	}
}

template <typename T>
T &
List<T>::getBack () 
{ 
#ifndef NDEBUG
	assert( tail_ != NULL );
#endif
	return tail_->object_; 
}

template <typename T>
T &
List<T>::getFront () 
{ 
#ifndef NDEBUG
	assert( head_ != NULL );
#endif
	return head_->object_;
}

template <typename T>
void 
List<T>::pushBack ( const T &obj )
{
	if ( head_ ) {
		tail_->rlink_ = new Node<T>( obj, NULL, tail_ );
		tail_ = tail_->rlink_;
		++length_;
	}
	else {
		head_ = new Node<T>( obj, NULL, NULL );	
		tail_ = head_;
		++length_;
	}
}

template <typename T>
void 
List<T>::pushFront ( const T &obj )
{
	if ( head_ ) {
		head_->llink_ = new Node<T>( obj, head_, NULL );
		head_ = head_->llink_;
		++length_;
	}
	else {
		head_ = new Node<T>( obj, NULL, NULL );	
		tail_ = head_;
		++length_;
	}
}

template <typename T>
T 
List<T>::popBack ()
{
#ifndef NDEBUG
	assert ( length_ > 0 );
#endif
	T obj( tail_->object_ );
	if ( length_ > 1 ) {
		tail_ = tail_->llink_;
		delete tail_->rlink_;
		tail_->rlink_ = NULL;
	}
	else {
		delete head_;
		head_ = NULL;
	}
	--length_;
	return obj;
}

template <typename T>
T 
List<T>::popFront ()
{
#ifndef NDEBUG
	assert ( length_ > 0 );
#endif
	T obj( head_->object_ );
	if ( length_ > 1 ) {
		Node<T> *temp = head_->rlink_;
		head_->rlink_ = NULL;
		delete head_;
		temp->llink_ = NULL;
		head_ = temp;
	}
	else {
		delete head_;
		head_ = NULL;
	}
	--length_;
	return obj;
}

template <typename T>
T 
List<T>::remove ( const unsigned &index )
{
#ifndef NDEBUG
	assert ( index < length_ && index >= 0 );
#endif
	if ( index == 0 )
		return popFront();
	else if ( index == length_ - 1)
		return popBack();
	else if ( (length_ - index) >= length_ / 2 ) {
		current_ = head_;
		for ( unsigned i = 0; i < index; i++ )
			current_ = current_->rlink_;
		previous_ = current_->llink_;
		Node<T> *temp = current_->rlink_;
		T obj( current_->object_ );
		current_->rlink_ = NULL;
		delete current_;
		previous_->rlink_ = temp;
		temp->llink_ = previous_;
		--length_;
		return obj;
	} 
	else {
		current_ = tail_;
		for ( unsigned i = 0; i < length_ - index - 1; i++ )
			current_  = current_->llink_;
		previous_ = current_->rlink_;
		Node<T> *temp = current_->llink_;
		T obj( current_->object_ );
		current_->rlink_ = NULL;
		delete current_;
		temp->rlink_ = previous_;
		previous_->llink_ = temp;
		--length_;
		return obj;
	}
}

template <typename T>
void 
List<T>::concatenate ( List<T> &rhs )
{
	if ( rhs.head_ != NULL ) {
		tail_->rlink_ = rhs.head_;
		tail_ = rhs.tail_;
		length_ += rhs.length_;
		rhs.head_ = NULL;
		rhs.~List();
	}
}

template <typename T>
void
List<T>::traverse ()
{
	current_ = head_;
	for ( unsigned i = 0; current_; i++ ) {
		cout << "Node" << i << " = " << current_->object_ << endl;
		current_ = current_->rlink_;
	}
}

template <typename T>
bool 
List<T>::isEmpty () 
{
	return length_ == 0; 
}

template <typename T>
Node<T> *
List<T>::begin ()
{
	return head_;
}

template <typename T>
Node<T> *
List<T>::end ()
{
	return tail_;
}

template <typename T> 
unsigned 
List<T>::size ()
{
	return length_;
}

}
#endif


