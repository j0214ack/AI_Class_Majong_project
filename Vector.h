/*=================================================
 File     : Vector.h
 Function : User's generic vector container
 Author   : Po-Han, Chen
 Version  : 1.0.0
 Last Modified : Thu May  3 10:13:15 CST 2012
 Copyright: Copyright (C) 2012 Po-Han, Chen
 ==================================================*/

#ifndef VECTOR_H
#define VECTOR_H

#ifndef NULL
#define NULL 0
#endif

#define START_EXCEPTION try {
#define END_EXCEPTION( str ) _END_EXCEPTION( str )
#define _END_EXCEPTION( str ) } catch ( ... ) \
{ std::cout << "Backtracking : in " << __FILE__ << " line-" << __LINE__ << " " << str << "\n"; throw; }

#include "ErrorMessage.h"

using std::cout;
using std::endl;
using std::ostream;

namespace user {

template <typename T> class Vector;

template <typename T> 
ostream &operator<< ( ostream &os, const Vector<T> & );

template <typename T>
class Vector 
{
	//-------------------- Public --------------------//
    public :

		// Nested class : Vector's iterator
		struct  Iterator;
		typedef Iterator iterator;

		typedef T elementType ;
		typedef Vector<T> vectorType ;

		// Constructor & Destructor
        explicit Vector ();
        explicit Vector ( unsigned num, const T &obj );
        Vector ( const Vector<T> &rhs );
        explicit Vector ( const Vector<T> &rhs, unsigned a, unsigned b ); // [a, b)
        explicit Vector ( const T *rhs, unsigned a, unsigned b ); // [a, b)
        ~Vector();

		// Access operator
        T &operator[] ( unsigned index ) const;
        T &operator* () const;
		Vector<T> operator+  ( const Vector<T> &rhs ) const;
        Vector<T> &operator= ( const Vector<T> &rhs );
        Vector<T> &operator+=( const Vector<T> &rhs );
		
		// Set attribute
		void clear ();

		// Get attribute
        unsigned size () const;
        void traverse () const;
        Iterator begin() const;
        Iterator end  () const;
		Iterator rbegin () const;
		Iterator rend   () const;

        friend ostream &operator<< <T> ( ostream &os, const Vector<T> &vec );

	//-------------------- Private --------------------//
    private :

        T *ptr_;

        unsigned length_;
};

template <typename T> 
struct Vector<T>::Iterator
{
	//-------------------- Public --------------------//

	T &operator* () const ;
	T *operator-> () const;

	Iterator operator++ ( int );
	Iterator &operator++ ();
	Iterator operator-- ( int );
	Iterator operator-- ();

	Iterator &operator= ( const Iterator &rhs );

	bool operator== ( const Iterator &rhs ) const;
	bool operator!= ( const Iterator &rhs ) const;

	Iterator ();
	Iterator ( const Iterator &rhs );
	Iterator ( T * );
		
	T *node;
};


///////////////////////////////////////////////////////////////////////
////////////////////////  Implementation  /////////////////////////////
///////////////////////////////////////////////////////////////////////

template <typename T>
Vector<T>::Vector () : ptr_( NULL ), length_( 0 ) {}

template <typename T>
Vector<T>::Vector ( unsigned num, const T &obj ) : ptr_( new T[num] ), length_( num )
{
	for ( unsigned i = 0; i < num; i++ )
		 ptr_[i] = obj;
}

template <typename T>
Vector<T>::Vector ( const Vector<T> &rhs ) : ptr_( new T[rhs.length_] ), length_( rhs.length_ )  
{
	for ( unsigned i = 0; i < length_; i++ )
		ptr_[i] = rhs.ptr_[i];
}

template <typename T>
Vector<T>::Vector ( const Vector<T> &rhs, unsigned a, unsigned b ) 
: ptr_( new T[b - a] ), length_( b - a ) 
{
#ifndef NDEBUG
	if ( b - a > rhs.length_ )
		throw IndexError( "in Vector<T>::Vector ( const Vector<T> &rhs, unsigned a, unsigned b )\n"
						  " ==> b - a > rhs.length_", b - a, rhs.length_ );
#endif
	for ( unsigned i = 0; i < b; i++ )
		ptr_[i] = rhs.ptr_[a + i];
}

template <typename T> 
Vector<T>::Vector ( const T *rhs, unsigned a, unsigned b ) 
: ptr_( new T[b - a] ), length_( b - a )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	for ( unsigned i = 0; i < b; i++ )
		ptr_[i] = rhs[a + i];
#ifndef NDEBUG
END_EXCEPTION( "Vector<T>::Vector ( const T *, unsigned , unsigned  )" );
#endif
}

template <typename T>
Vector<T>::~Vector () 
{
	if ( ptr_ ) 
		delete [] ptr_; 
	ptr_ = NULL;
	length_ = 0;
}

template <typename T>
T & 
Vector<T>::operator[] ( unsigned index ) const
{
#ifndef NDEBUG
	if ( index > length_ || index < 0 )
		throw IndexError( "in Vector<T>::operator[] ( unsigned ) ==> index out of bound", index, length_ );
#endif
	return ptr_[index];
}

template <typename T>
T & 
Vector<T>::operator* () const
{
#ifndef NDEBUG
	if ( ptr_ == NULL )
		throw PointerError( "in Vector<T>::operator* () ==> ptr_ == NULL", ptr_ );
#endif
	return *ptr_;
}

template <typename T>
Vector<T> & 
Vector<T>::operator= ( const Vector<T> &rhs )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( ptr_ )
		if ( rhs.ptr_ && rhs.length_ != length_ ) {
			delete [] ptr_;
			length_ = rhs.length_;
			ptr_ = new T[length_];
			for ( unsigned i = 0; i < length_; i++ )
				ptr_[i] = rhs.ptr_[i];
		} 
		else if ( rhs.ptr_ && rhs.length_ == length_ ) {
			for ( unsigned i = 0; i < length_; i++ )
				ptr_[i] = rhs.ptr_[i];
		} 
		else {
			delete [] ptr_;
			ptr_ = NULL;
			length_ = 0;
		}
	else if ( rhs.ptr_ ) {
			length_ = rhs.length_;
			ptr_ = new T[rhs.length_];
			for ( unsigned i = 0; i < length_; i++ )
				ptr_[i] = rhs.ptr_[i];
		}
	return *this;
#ifndef NDEBUG
	END_EXCEPTION( "Vector<T>::operator= ( const Vector<T> & )" );
#endif
}

template <typename T> 
Vector<T>
Vector<T>::operator+ ( const Vector<T> &rhs ) const
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( ptr_ ) {
		if ( rhs.ptr_ ) {
			Vector<T> vecTemp( length_ + rhs.length_, 0);
			for ( unsigned i = 0; i < length_; i++ )
				vecTemp[i] = ptr_[i];
			for ( unsigned i = 0; i < rhs.length_; i++ )
				vecTemp[i + length_] = rhs.ptr_[i];
			return vecTemp;
		}
		else
			return Vector<T>( *this );
	}
	else
		if ( rhs.ptr_ ) {
			return Vector<T>( rhs );
		}
		else
			return Vector<T>();
#ifndef NDEBUG
END_EXCEPTION( "Vector<T>::operator+ ( const Vector<T> & )" );
#endif
}

template <typename T>
Vector<T> & 
Vector<T>::operator += ( const Vector<T> &rhs )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	return *this = *this + rhs;
#ifndef NDEBUG
END_EXCEPTION( "Vector<T>::operator+= ( const Vector<T> & )" );
#endif
}

template <typename T>
void
Vector<T>::clear () 
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( ptr_ )
		delete [] ptr_;
	ptr_ = NULL;
	length_ = 0;
#ifndef NDEBUG
	END_EXCEPTION( "Vector<T>::clear ()" );
#endif
}

template <typename T>
void 
Vector<T>::traverse () const
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	cout << "Vector : ";
	for ( unsigned i = 0; i < length_; i++ )
		cout << ptr_[i] << " ";
	cout << "\n";
#ifndef NDEBUG
	END_EXCEPTION( "Vector<T>::traverse ()" );
#endif
}

template <typename T>
unsigned 
Vector<T>::size () const
{
	return length_; 
}

template <typename T> 
typename Vector<T>::Iterator
Vector<T>::begin () const
{
	if ( ptr_ )
		return Vector<T>::Iterator( ptr_ ); 
	else
		return Iterator( NULL );
}

template <typename T>
typename Vector<T>::Iterator
Vector<T>::end () const
{
	if ( ptr_ )
		return Vector<T>::Iterator( ptr_ + length_ ); 
	else
		return Iterator ( NULL );
}

template <typename T>
typename Vector<T>::Iterator
Vector<T>::rbegin () const
{
	if ( ptr_ )
		return Vector<T>::Iterator( ptr_ + length_ - 1 );
	else
		return Vector<T>::Iterator( NULL );
}

template <typename T>
typename Vector<T>::Iterator
Vector<T>::rend () const
{
	if ( ptr_ )
		return Vector<T>::Iterator( ptr_ - 1 );
	else
		return Vector<T>::Iterator( NULL );
}

template <typename T>
ostream & 
operator<< ( ostream &os, const Vector<T> &vec )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	os << "Vector : ";
	if ( vec.size() != 0 )
		for ( unsigned i = 0; i < vec.size(); i++ )
			os << vec[i] << " ";
	else
		os << "NULL";
	os << "\n";
	return os;
#ifndef NDEBUG
	END_EXCEPTION( "operator<< ( ostream &, const Vector<T> & )" );
#endif
}

template <typename T>
Vector<T>::Iterator::Iterator () : node( NULL ) {}

template <typename T>
Vector<T>::Iterator::Iterator ( const Iterator &rhs ) : node( rhs.node ) {}

template <typename T>
Vector<T>::Iterator::Iterator ( T *n ) : node( n ) {}

template <typename T>
typename Vector<T>::Iterator &
Vector<T>::Iterator::operator= ( const Iterator &rhs ) 
{
	node = rhs.ptr_;
	return *this;
} 

template <typename T>
T &
Vector<T>::Iterator::operator* () const 
{
#ifndef NDEBUG
	if ( node == NULL )
		throw PointerError( "in Vector<T>::Iterator::operator* () ==> node == NULL", node );
#endif
	return *node; 
}

template <typename T>
T *
Vector<T>::Iterator::operator-> () const
{
#ifndef NDEBUG					
	if ( node == NULL )
		throw PointerError( "in Vector<T>::Iterator::operator-> () ==> node == NULL", node );
#endif
	return node;

}

template <typename T>
typename Vector<T>::Iterator 
Vector<T>::Iterator::operator++ ( int )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
#ifndef NDEBUG
	if ( node == NULL )
		throw PointerError( "in Vector<T>::Iterator::operator++ ( int ) ==> node == NULL", node );
#endif
	Iterator tempIter( *this );
	++node;
	return tempIter;
#ifndef NDEBUG
	END_EXCEPTION( "Vector<T>::Iterator::operator++ ( int )" );
#endif
}

template <typename T>
typename Vector<T>::Iterator &
Vector<T>::Iterator::operator++ () 
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	this->operator++( int( 0 ) );
	return *this;
#ifndef NDEBUG
	END_EXCEPTION( "Vector<T>::Iterator::operator++ ()" );
#endif
}

template <typename T>
typename Vector<T>::Iterator 
Vector<T>::Iterator::operator-- ( int )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
#ifndef NDEBUG
	if ( node == NULL )
		throw PointerError( "in Vector<T>::Iterator::operator-- () ==> node == NULL", node );
#endif
	Iterator tempIter( *this );
	--node;
	return tempIter;
#ifndef NDEBUG
	END_EXCEPTION( "Vector<T>::Iterator::operator-- ( int )" );
#endif
}

template <typename T>
typename Vector<T>::Iterator 
Vector<T>::Iterator::operator-- () 
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	this->operator--( 0 );
	return *this;
#ifndef NDEBUG
	END_EXCEPTION( "Vector<T>::Iterator::operator-- ()" );
#endif
}

template <typename T>
bool 
Vector<T>::Iterator::operator== ( const Iterator &rhs ) const
{
	return node == rhs.node;
}

template <typename T>
bool
Vector<T>::Iterator::operator!= ( const Iterator &rhs ) const 
{
	return node != rhs.node; 
}
	
}
#endif
