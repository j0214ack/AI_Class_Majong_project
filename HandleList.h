/***************************************************
** File: HandleList.h
** Function: User's generic handle class container
** Author: Po-Han, Chen
** Version: 1.0.0
** Last Modified: Tue Apr 10 18:08:55 CST 2012
** Copyright: Copyright (C) 2012 Po-Han, Chen
****************************************************/

#ifndef HANDLELIST_H
#define HANDLELIST_H

#include "List.h"
#include "Handle.h"
#include "ErrorMessage.h"

#ifndef DEBUG_MACRO
#define DEBUG_MACRO
#define START_EXCEPTION try {
#define END_EXCEPTION( str ) _END_EXCEPTION( str )
#define _END_EXCEPTION( str ) } catch ( ... ) \
{ std::cout << "Backtracking : in " << __FILE__ << " line-" << __LINE__ << " " << str << "\n"; throw; }
#endif

namespace user {

// T is base class,
// it must need clone() member to return the address of clone.
template <typename T>
class HandleList
{
	//-------------------- Public --------------------//
	public :

		typedef Handle<T> handleType;
		typedef typename List<handleType>::Iterator iterator;

		// Contructor
		HandleList ();
		HandleList ( const HandleList<T> & );
	   ~HandleList () throw ();

	   // Get attribute
		T &getBack  () const;
		T &getFront () const;

		T &popBack  ();
		T &popFront ();

		void pushBack  ( const T & );
		void pushFront ( const T & );

	    unsigned insert ( const unsigned &index, const T & ); // Insert before list[index].
		typename List<handleType>::Iterator 
		insert ( const typename List<handleType>::Iterator &iter, const T & );

		T &remove ( const unsigned &index ); // Remove list[index] and return it.
		T &remove ( typename List<handleType>::Iterator &iter ); 

		void reverse ();
		void clear ();	

		bool isEmpty () const;

		unsigned size () const;

		// Get iterator
		typename List<handleType>::Iterator begin () const;
		typename List<handleType>::Iterator end   () const;
		typename List<handleType>::Iterator rbegin () const;
		typename List<handleType>::Iterator rend   () const;
		
		void append ( const HandleList<T> & );
		void traverse () const;

	    /*******  Operator  *******/
	    HandleList<T> &operator= ( const HandleList<T> & );
	    T &operator[] ( const unsigned &index ) const;
	    T &operator* () const;

	//-------------------- Private --------------------//
	private :

		List<handleType> hlist_;

		// For memory consideration in popBack(), popFront(), remove().
		static Handle<T> *htemp_;

};

template <typename T>
Handle<T> *HandleList<T>::htemp_ = NULL;

template <typename T> 
HandleList<T>::HandleList () : hlist_() {}

template <typename T>
HandleList<T>::HandleList ( const HandleList &hl ) : hlist_( hl.hlist_ ) {}

template <typename T>
HandleList<T>::~HandleList () throw ()
{
	if ( htemp_ != NULL ) {
		delete htemp_;
		htemp_ = NULL;
	}
}

template <typename T>
T &
HandleList<T>::getBack () const
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	return *hlist_.getBack(); 
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::getBack ()" );
#endif
}

template <typename T>
T &
HandleList<T>::getFront () const
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	return *hlist_.getFront(); 
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::getFront ()" );
#endif
}

template <typename T>
T &
HandleList<T>::popBack () 
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( htemp_ != NULL ) {
		delete htemp_;
		htemp_ = NULL;
	}
	htemp_ = new Handle<T>( hlist_.popBack()->clone() );
	return **htemp_;
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::popBack ()" );
#endif
}

template <typename T>
T &
HandleList<T>::popFront ()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( htemp_ != NULL ) {
		delete htemp_;
		htemp_ = NULL;
	}
	htemp_ = new Handle<T>( hlist_.popFront()->clone() );
	return **htemp_;
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::popFront ()" );
#endif
}

template <typename T>
void
HandleList<T>::pushBack ( const T &obj )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	hlist_.pushBack( handleType( obj ) );
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::pushBack ( const T & )" );
#endif
}

template <typename T>
void 
HandleList<T>::pushFront ( const T &obj )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	hlist_.pushFront( handleType( obj ) );
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::pushFront ( const T & )" );
#endif
}

template <typename T>
unsigned
HandleList<T>::insert ( const unsigned &index, const T &obj )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	hlist_.insert( index, handleType( obj ) );
	return index;
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::insert ( const unsigned &, const T & )" );
#endif
}

template <typename T>
typename List< Handle<T> >::Iterator
HandleList<T>::insert ( const typename List< Handle<T> >::Iterator &iter, const T &obj )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	hlist_.insert( iter, handleType( obj ) );
	return iter;
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::insert ( const Iterator &, const T & )" );
#endif
}

template <typename T>
T &
HandleList<T>::remove ( const unsigned &index )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( htemp_ != NULL ) {
		delete htemp_;
		htemp_ = NULL;
	}
	htemp_ = new Handle<T>( hlist_.remove( index )->clone() );
	return **htemp_;
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::remove ( const unsigned & )" );
#endif
}

template <typename T>
T &
HandleList<T>::remove ( typename List< Handle<T> >::Iterator &iter )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( htemp_ != NULL ) {
		delete htemp_;
		htemp_ = NULL;
	}
	htemp_ = new Handle<T>( hlist_.remove( iter )->clone() );
	return **htemp_;
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::remove ( Iterator & )" );
#endif
}

template <typename T>
void
HandleList<T>::reverse ()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	hlist_.reverse();
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::reverse ()" );
#endif
}

template <typename T>
void
HandleList<T>::clear ()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	hlist_.clear();
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::clear ()" );
#endif
}

template <typename T>
unsigned
HandleList<T>::size () const
{
	return hlist_.size();
}

template <typename T>
bool
HandleList<T>::isEmpty () const
{
	return hlist_.isEmpty();
}

template <typename T>
void 
HandleList<T>::append( const HandleList &hl )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	hlist_.append( hl.hlist_ );
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::append ()" );
#endif
}

template <typename T>
void
HandleList<T>::traverse () const
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( hlist_.size() == 0 )
		cout << "Handle List ==> NULL\n";
	for ( unsigned i = 0; i < hlist_.size(); i++ )
		hlist_[i]->show();
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::traverse ()" );
#endif
}

template <typename T>
HandleList<T> &
HandleList<T>::operator= ( const HandleList<T> &hl )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	hlist_ = hl.hlist_;
	return *this;
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::operator= ( const HandleList<T> & )" );
#endif
}

template <typename T>
T &
HandleList<T>::operator[] ( const unsigned &index ) const
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	return *hlist_[index];
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::operator[] ( const unsigned & )" );
#endif
}

template <typename T>
T &
HandleList<T>::operator* () const
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	return **hlist_;
#ifndef NDEBUG
END_EXCEPTION( "HandleList<T>::operator* ()" );
#endif
}

template <typename T>
typename List< Handle<T> >::Iterator
HandleList<T>::begin () const
{
	return hlist_.begin();
}

template <typename T>
typename List< Handle<T> >::Iterator
HandleList<T>::end () const
{
	return hlist_.end();
}

template <typename T>
typename List< Handle<T> >::Iterator
HandleList<T>::rbegin () const
{
	return hlist_.rbegin();
}

template <typename T>
typename List< Handle<T> >::Iterator
HandleList<T>::rend () const
{
	return hlist_.rend();
}

}
#endif
