/*=================================================
 File     : Handle.h
 Function : User's generic Handle class
 Author   : Po-Han, Chen
 Version  : 1.0.0
 Last Modified : Fri May  4 13:02:32 CST 2012
 Copyright: Copyright (C) 2012 Po-Han, Chen
 ==================================================*/

#ifndef USERHANDLE_H
#define USERHANDLE_H

#ifndef NULL
#define NULL 0
#endif 

#ifndef DEBUG_MACRO
#define DEBUG_MACRO
#define START_EXCEPTION try {
#define END_EXCEPTION( str ) _END_EXCEPTION( str )
#define _END_EXCEPTION( str ) } catch ( ... ) \
{ std::cout << "Backtracking : in " << __FILE__ << " line-" << __LINE__ << " " << str << "\n"; throw; }
#endif

#include "ErrorMessage.h"

namespace user {

// T is base class,
// it must need clone() member to return the address of clone.
template <typename T> 
class Handle
{
	//-------------------- Public --------------------//
	public :

		// Deference
		T &operator* () const;
		T *operator->() const;

	    // Desttrctor
		Handle<T> &operator= ( const Handle<T> &handle );
		Handle<T> &operator= ( const T &obj );
		Handle<T> &operator= ( T * );

		// Compare
		bool operator== ( const Handle<T> &handle ) const;
		bool operator!= ( const Handle<T> &handle ) const;
		bool operator== ( const T *op ) const;
		bool operator!= ( const T *op ) const;

		// Contructor
		explicit Handle ();
		explicit Handle ( T *tp );
		Handle ( const Handle<T> &handle );
		Handle ( const T &obj );
	   ~Handle () throw ();

		unsigned getUse () const;

	//-------------------- Private --------------------//
	private :
	
		// Common used object, point type is 'dynamic binding' to base class.
		T *ptr_;

		// Count how many handle point to ptr_.
		unsigned *use_;
};

template <typename T>
Handle<T>::Handle () : ptr_ ( NULL ),
					   use_ () {}					 

template <typename T> 
Handle<T>::Handle ( T *tp ) : ptr_( tp ),
							  use_( tp == NULL ? NULL : new unsigned ( 1 ) ) {}

template <typename T>
Handle<T>::Handle ( const Handle<T> &handle ) : ptr_( handle.ptr_ ),
											    use_( handle.use_ ) 
{
	if ( handle.use_ != NULL )
		++*use_;
}

template <typename T>
Handle<T>::Handle ( const T &obj ) : ptr_( obj.clone() ),
								     use_( new unsigned(1) ) {}

template <typename T> 
Handle<T>::~Handle() throw ()
{
	if ( ptr_ && --*use_ == 0  ) 
		delete ptr_, delete use_;
	ptr_ = NULL;
	use_ = NULL;
}

template <typename T>
Handle<T> &
Handle<T>::operator= ( const Handle<T> &handle ) 
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( ptr_ && --*use_ == 0 )	
		delete ptr_, delete use_;
	ptr_ = NULL;
	if ( handle.ptr_ ) {
		ptr_ = handle.ptr_;
		use_ = handle.use_;
		++*use_;
	}
	return *this;
#ifndef NDEBUG
END_EXCEPTION( "Handle<T>::operator= ( const Handle<T> & )" );
#endif
}

template <typename T>
Handle<T> &
Handle<T>::operator= ( const T &obj )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( ptr_ && --*use_ == 0 )	
		delete ptr_;
	ptr_ = obj.clone();
	use_ = new unsigned(1);
	return *this;
#ifndef NDEBUG
END_EXCEPTION( "Handle<T>::operator= ( const T & )" );
#endif
}

template <typename T>
Handle<T> &
Handle<T>::operator= ( T *tp )
{
#ifndef NDEBUG
START_EXCEPTION
#endif
	if ( ptr_ && --*use_ == 0 )	
		delete ptr_;
	ptr_ = NULL;
	if ( tp ) {
		ptr_ = tp;
		use_ = new unsigned(1);
	}
	return *this;
#ifndef NDEBUG
END_EXCEPTION( "Handle<T>::operator= ( T * )" );
#endif
}

template <typename T>
T &
Handle<T>::operator* () const
{
#ifndef NDEBUG
	if ( ptr_ == NULL )
		throw PointerError( " in Handle<T>::operator*() ==> ptr_ == NULL", ptr_ );
#endif
	return *ptr_; 
}

template <typename T>
T *
Handle<T>::operator-> () const
{
#ifndef NDEBUG
	if ( ptr_ == NULL )
		throw PointerError( " in Handle<T>::operator->() ==> ptr_ == NULL", ptr_ );
#endif
	return  ptr_;
}

template <typename T>
bool 
Handle<T>::operator== ( const Handle<T> &handle ) const 
{
	return ptr_ == handle.ptr_;
}

template <typename T>
bool 
Handle<T>::operator!= ( const Handle<T> &handle ) const 
{
	return ptr_ != handle.ptr_;
}

template <typename T>
bool 
Handle<T>::operator== ( const T *op ) const 
{
	return ptr_ == op;
}

template <typename T>
bool 
Handle<T>::operator!= ( const T *op ) const 
{
	return ptr_ != op;
}

template <typename T>
unsigned 
Handle<T>::getUse () const
{
	if ( use_ == NULL )
		return 0;
	return *use_; 
}

}
#endif 
