/*=================================================
 File     : ErrorMessage.h
 Function : Exception handling
 Author   : Po-Han, Chen
 Version  : 1.0.0
 Last Modified : Fri May  4 09:20:34 CST 2012
 Copyright: Copyright (C) 2012 Po-Han, Chen
 ==================================================*/

#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

enum ERROR { ERROR_INT, ERROR_UNSIGNED, ERROR_FLOAT, ERROR_INDEX, ERROR_POINTER };

// Abstract class
class ErrorMessage
{
	//-------------------- Public --------------------//
	public :

		virtual const char *what () const = 0;

		virtual ERROR type () const = 0;

		virtual ErrorMessage *clone () const = 0;

		virtual void showPointer ()      const {};
		virtual int intValue ()          const { return 0; }
		virtual double floatValue ()     const { return 0; }
		virtual unsigned unsignedValue() const { return 0; }
		virtual unsigned indexValue ()   const { return 0; }
		virtual unsigned boundValue ()   const { return 0; }
};

class IntError : public ErrorMessage
{
	//-------------------- Public --------------------//
	public :

		IntError ( const char *str, const int &i ) : err( str ), data( i ) {}

		const char *what () const { return err; }

		ERROR type () const { return ERROR_INT; }

		IntError *clone () const { return new IntError( *this ); }

		int intValue () const { return data; }

		const char *err;
		int data;
};

class UnsignedError : public ErrorMessage
{
	//-------------------- Public --------------------//
	public :

		UnsignedError ( const char *str, const unsigned &i ) : err( str ), data( i ) {}

		const char *what () const { return err; }

		ERROR type () const { return ERROR_UNSIGNED; }

		UnsignedError *clone () const { return new UnsignedError( *this ); }

		unsigned unsignedValue () const { return data; }

		const char *err;
		unsigned data;
};

class FloatError : public ErrorMessage
{
	//-------------------- Public --------------------//
	public :

		FloatError ( const char *str, const double &d ) : err( str ), data( d ) {}

		const char *what () const { return err; }
		
		ERROR type () const { return ERROR_FLOAT; }

		FloatError *clone () const { return new FloatError( *this ); }

		double floatValue () const { return data; }

		const char *err;
		double data;
};

class IndexError : public ErrorMessage
{
	//-------------------- Public --------------------//
	public :

		IndexError ( const char *str, const unsigned &i, const unsigned &b ) 
		: err( str ), data( i ), bound( b ) {}

		const char *what () const { return err; }

		ERROR type () const { return ERROR_INDEX; }

		IndexError *clone () const { return new IndexError( *this ); }

		unsigned indexValue () const { return data; }
		unsigned boundValue () const { return bound;}

		const char *err;
		unsigned data,
				 bound;
};

class PointerError : public ErrorMessage
{
	//-------------------- Public --------------------//
	public :

		PointerError ( const char *str, void *p ) : err( str ), data( p ) {}

		const char *what () const { return err; }

		ERROR type () const { return ERROR_POINTER; }

		PointerError *clone () const { return new PointerError( *this ); }

		void showPointer () const { std::cout << data << "\n"; }

		const char *err;
		void *data;
};


#endif
