/***************************************************
** File: list.h
** Function: User's generic double link list 
** Author: Po-Han, Chen
** Version: 1.0.0
** Last Modified: Sat Mar 31 00:36:44 CST 2012
** Copyright: Copyright (C) 2012 Po-Han, Chen
****************************************************/
#ifndef LIST_H
#define LIST_H

#ifndef NDEBUG
#include <cassert> 
#endif

using std::cout;
using std::endl;

namespace user {

template <typename T> class List;

template <typename T>
class Node {

    friend class List<T>;

    private :

        Node () : rlink( NULL ), llink( NULL ), object() {}
        Node ( const T &obj, Node<T> *rp, Node<T> *lp ) : rlink( rp ), llink( lp ) , object( obj ) {}
        Node ( const Node<T> &rhs ) : rlink( rhs.rlink ), llink( rhs.llink ), object( rhs.object ) {}

        ~Node () { 
			if ( rlink ) delete rlink;
#ifdef COUNT_NODE	
			cout << "Node destroy!" << endl;
#endif
		}

        Node<T> & operator= ( const Node<T> &rhs )
        {
            rlink = rhs.rlink;
            llink = rhs.llink;
            object = rhs.object;
        }

        Node<T> *rlink,
                *llink;

        T object;
};


template <typename T>
class List {

    public :

        typedef Node<T> *iterator;
        typedef List<T> list_type;
        typedef T element_type;

#ifndef NDEBUG	
		static unsigned nList;
#endif

        List () : head_( NULL ), tail_( NULL ), current_( NULL ), previous_( NULL ), length_(0) {
#ifndef NDEBUG
			nList++;
#endif
		}

        List ( const unsigned &num, const T &obj ) : head_( NULL ), current_( NULL ), previous_( NULL ), length_( num )
        {
#ifndef NDEBUG
			nList++;
#endif
            if ( length_ ) {
                head_ = new Node<T>( obj, NULL, NULL ); //Construct first node
                current_ = head_;
                for ( count_ = 1; count_ < length_; count_++ ) {
                    current_->rlink = new Node<T>( obj, NULL, current_ );
                    current_ = current_->rlink;
                }
                tail_ = current_;
            }
        }

        List ( const List<T> &rhs ) : head_( NULL ), current_( NULL ), previous_( NULL ), length_( rhs.length_ )
        {
			Node<T> *rhs_current_ = rhs.head_;
            if ( length_ ) {
                head_ = new Node<T>( rhs_current_->object, NULL, NULL );
                current_ = head_;
                for ( count_ = 1; count_ < length_; count_++ ) {
                    current_->rlink = new Node<T>( (rhs_current_)->rlink->object, NULL, current_ );
                    current_ = current_->rlink;
                    rhs_current_ = rhs_current_->rlink;
                }
                tail_ = current_;
            }
        }

        ~List () { 
			if ( head_ ) delete head_;
#ifdef NEED_COUNT
			cout << "list destroy!" << endl;
			nList--; 
#endif
		}

        List<T> & operator= ( const List<T> &rhs )
        {
            if ( head_ )
                delete head_;
            length_ = rhs.length_;
            if ( length_ ) {
                head_ = new Node<T>( rhs.head_->object, NULL, NULL );
                current_ = head_;
				Node<T> *rhs_current_ = rhs.head_;
                for ( count_ = 1; count_ < length_; count_++ ) {
                    current_->rlink = new Node<T>( (rhs_current_)->rlink->object, NULL, current_ );
                    current_ = current_->rlink;
                    rhs_current_ = rhs_current_->rlink;
                }
                tail_ = current_;
            }
            return *this;
        }

        T & operator[] ( unsigned p )
        {
#ifndef NDEBUG
			assert ( p < length_ || p > 0 );
#endif
			/*******  Traverse form head_ or tail_ ( close )  *******/
            if ( (length_ - p) >= length_ / 2 ) {
                count_ = 0;
                current_ = head_;
                while ( count_++ != p )
                    current_ = current_->rlink;
                return current_->object;
            } else {
                count_ = 0;
                current_ = tail_;
                p = length_ - p - 1;
                while ( count_++ != p )
                    current_ = current_->llink;
                return current_->object;
            }
        }

        T & operator* () { return head_->object; }

        void insert ( unsigned p, const T &obj )
        {
#ifndef NDEBUG
			assert ( p < length_ || p > 0 );
#endif
            if ( p == 0 )
                pushFront(obj);
            else if ( (length_ - p) >= length_ / 2 ) {
				/*******  Traverse form head_  *******/
                count_ = 0;
                current_  = head_;
                previous_ = current_->llink;
                while ( count_++ != p ) {
                    current_  = current_->rlink;
                    previous_ = current_->llink;
                }
                previous_->rlink = new Node<T>( obj, current_, previous_ );
                ++length_;
				current_->llink = previous_->rlink;
            } else {
				/*******  Traverse form tail_  *******/
                count_ = 0;
                current_  = tail_;
                previous_ = current_->llink;
                p = length_ - p - 1;
                while ( count_++ != p ){
                    current_  = current_->llink;
                    previous_ = current_->llink;
                }
                previous_->rlink = new Node<T>( obj, current_, previous_ );
                ++length_;
				current_->llink  = previous_->rlink;
            }
        }

		T &getBack ()
		{
			return tail_->object;
		}

		T &getFront ()
		{
			return head_->object;
		}

        void pushBack ( const T &obj )
        {
			if ( head_ ) {
				tail_->rlink = new Node<T>( obj, NULL, tail_ );
				++length_;
				tail_ = tail_->rlink;
			}
			else {
				head_ = new Node<T>( obj, NULL, NULL );	
				tail_ = head_;
				++length_;
			}
        }

        void pushFront ( const T &obj )
        {
			if ( head_ ) {
				head_->llink = new Node<T>( obj, head_, NULL );
				++length_;
				head_ = head_->llink;
			}
			else {
				head_ = new Node<T>( obj, NULL, NULL );	
				tail_ = head_;
				++length_;
			}
        }

        T popBack ()
        {
#ifndef NDEBUG
			assert ( length_ > 0 );
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
			}
            --length_;
            return obj;
        }

        T popFront ()
        {
#ifndef NDEBUG
			assert ( length_ > 0 );
#endif
			T obj( head_->object );
			if ( length_ > 1 ) {
				Node<T> *temp = head_->rlink;
				head_->rlink = NULL;
				delete head_;
				temp->llink = NULL;
				head_ = temp;
			}
			else {
				delete head_;
				head_ = NULL;
			}
            --length_;
            return obj;
        }

		T remove ( unsigned p )
        {
#ifndef NDEBUG
			assert ( p < length_ || p > 0 );
#endif
            if ( p == 0 )
                return popFront();
            else if ( p == length_ - 1)
                return popBack();
            else if ( (length_ - p) >= length_ / 2 ) {
				/*******  Traverse from head_  *******/
                count_ = 0;
                current_  = head_;
				previous_ = current_->llink;
				while ( count_++ != p ) {
                    current_  = current_->rlink;
                    previous_ = current_->llink;
                }
                Node<T> *temp = current_->rlink;
                current_->rlink = NULL;
				T obj( current_->object );
                delete current_;
                previous_->rlink = temp;
                temp->llink = previous_;
                --length_;
                return obj;
            } else {
				/*******  Traverse from tail_  *******/
                count_ = 0;
                current_  = tail_;
                previous_ = current_->llink;
                p = length_ - p - 1;
                while ( count_++ != p ) {
                    current_  = current_->llink;
                    previous_ = current_->llink;
                }
                Node<T> *temp = current_->rlink;
                current_->rlink = NULL;
				T obj( current_->object );
                delete current_;
                previous_->rlink = temp;
                temp->llink = previous_;
                --length_;
                return obj;
            }
        }

        void concatenate ( List<T> &rhs )
        {
			if ( rhs.head_ != NULL )
				tail_->rlink = rhs.head_;
				tail_ = rhs.tail_;
				length_ += rhs.length_;
				rhs.head_ = NULL;
				rhs.~List();
        }

        void traverse ()
        {
            count_ = 0;
            current_ = head_;
            while ( current_ ) {
                cout << "Node" << count_++ << " = " << current_->object << endl;
                current_ = current_->rlink;
            }
        }

		bool isEmpty ()
		{
			return length_ == 0;
		}

        Node<T> *begin () { return head_; }
        Node<T> *end () { return tail_; }

        unsigned size () { return length_; }

    private :

        Node<T> *head_,
                *tail_,
                *current_,
                *previous_;

        unsigned length_;

        static unsigned count_;
};

template <typename T>
unsigned List<T>::count_ = 0;

#ifndef NDEBUG
template <typename T>
unsigned List<T>::nList = 0;
#endif

}

#endif


