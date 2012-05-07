/*=================================================
 File     : macro.h
 Function : some useful macro
 Author   : Po-Han, Chen
 Version  : 1.0.0
 Last Modified : Sat May  5 22:51:53 CST 2012
 Copyright: Copyright (C) 2012 Po-Han, Chen
 ==================================================*/

#ifndef USER_MACRO_H
#define USER_MACRO_H

#include <cfloat>

#include "ErrorMessage.h"
#include "HandleList.h"

#define START_MAIN_EXCEPTION try {
#define END_MAIN_EXCEPTION } \
	catch ( ErrorMessage &error ) {\
\
		switch ( error.type() )\
		{\
			case ERROR_INT :\
				cout << "Int value error : in " << __FILE__ << "\n"\
						"### " << error.what() << "\n"\
						"### int number = " << error.intValue() << "\n";\
				break;\
\
			case ERROR_UNSIGNED :\
				cout << "Unsigned value error : in " << __FILE__ << "\n"\
						"### " << error.what() << "\n"\
						"### unsigned number = " << error.unsignedValue() << "\n";\
				break;\
\
			case ERROR_FLOAT :\
				cout << "Float value error : in " << __FILE__ << "\n"\
						"### " << error.what() << "\n"\
						"### float number = " << error.floatValue() << "\n";\
				break;\
				\
			case ERROR_CHAR :\
				cout << "Char value error : in " << __FILE__ << "\n"\
						"### " << error.what() << "\n"\
						"### char token = " << error.charValue() << "\n";\
				break;\
				\
			case ERROR_INDEX :\
				cout << "Index error : in " << __FILE__ << "\n"\
						"### " << error.what() << "\n"\
						"### index = " << error.indexValue() << "\n"\
						"### bound = " << error.boundValue() << "\n";\
				break;\
\
			case ERROR_POINTER :\
				cout << "Pointer error : in " << __FILE__ << "\n"\
						"### " << error.what() << "\n"\
						"### pointer = ";\
				error.showPointer();\
				break;\
			\
			default : \
				cout << "Error : in " << __FILE__ << "\n"\
					    "### " << error.what() << "\n";\
				break;\
\
			return 1;\
		}\
	}\
	catch ( user::HandleList<ErrorMessage> &errorList ) {\
\
	  for ( user::HandleList<ErrorMessage>::iterator iter = errorList.begin();\
			  										 iter != errorList.end(); iter++ ) {\
\
		switch ( (*iter)->type() )\
		{\
			case ERROR_INT :\
				cout << "Int value error : in " << __FILE__ << "\n"\
						"### " << (*iter)->what() << "\n"\
						"### int number = " << (*iter)->intValue() << "\n";\
				break;\
\
			case ERROR_UNSIGNED :\
				cout << "Unsigned value error : in " << __FILE__ << "\n"\
						"### " << (*iter)->what() << "\n"\
						"### unsigned number = " << (*iter)->unsignedValue() << "\n";\
				break;\
\
			case ERROR_FLOAT :\
				cout << "Float value error : in " << __FILE__ << "\n"\
						"### " << (*iter)->what() << "\n"\
						"### float number = " << (*iter)->floatValue() << "\n";\
				break;\
				\
			case ERROR_CHAR :\
				cout << "Char value error : in " << __FILE__ << "\n"\
						"### " << (*iter)->what() << "\n"\
						"### char token = " << (*iter)->charValue() << "\n";\
				break;\
				\
			case ERROR_INDEX :\
				cout << "Index error : in " << __FILE__ << "\n"\
						"### " << (*iter)->what() << "\n"\
						"### index = " << (*iter)->indexValue() << "\n"\
						"### bound = " << (*iter)->boundValue() << "\n";\
				break;\
\
			case ERROR_POINTER :\
				cout << "Pointer error : in " << __FILE__ << "\n"\
						"### " << (*iter)->what() << "\n"\
						"### pointer = ";\
				(*iter)->showPointer();\
				break;\
			\
			default : \
				cout << "Error : in " << __FILE__ << "\n"\
					    "### " << (*iter)->what() << "\n";\
				break;\
		}\
	  }\
			return 1;\
	}\
	catch ( const char *error ) {\
		cout << "Error : in " << __FILE__ << "\n"\
				"### " << error << "\n";\
		return 2;\
	}\
	catch ( ... ) {\
		cout << "Error : in " << __FILE__ << "\n"\
				"### Unexpect error !\n";\
		return 3;\
	}

#ifndef DEBUG_MACRO
#define DEBUG_MACRO
#define START_EXCEPTION try {
#define END_EXCEPTION( str ) _END_EXCEPTION( str )
#define _END_EXCEPTION( str ) } catch ( ... ) \
{ std::cout << "Backtracking : in " << __FILE__ << " line-" << __LINE__ << " " << str << "\n"; throw; }
#endif 

// Check runtime error and pause
#define CHECK( condition, err ) _CHECK( condition, err )
#define _CHECK( condition, err ) if ( condition ) { \
	std::cout << "Error ==> " << __FILE__ << " : line " << __LINE__ << std::endl\
		  	  << "          " << err << std::endl;\
	std::cout << "Press any key to continue...";\
	std::cin.get(); }

// Detect float number is illegal or not
#define IS_NAN( x ) _IS_NAN( x )
#define _IS_NAN( x ) x != x
#define IS_INF( x ) _IS_INF( x )
#define _IS_INF( x ) x >= DBL_MAX || x <= -DBL_MAX

// Define anonymous variables
#define ANONYMOUS( type ) _ANONYMOUS( type, __LINE__ )
#define _ANONYMOUS( type, line ) __ANONYMOUS( type, _anonymous, line )
#define __ANONYMOUS( type, var, line ) type var##line

// Return array size
#define ARRAY_SIZE( arr ) ( sizeof( arr )/sizeof( arr[0] ) )

// Print array
#define PRINT_ARRAY( arr, size ) \
	for ( unsigned i = 0; i < size; i++ )\
		cout << arr[i] << " ";\
	cout << endl

// Transform text to c-style string
#define STR( text ) _STR( text )
#define _STR( text ) #text

// Swap two variable
#define SWAP( type, x, y ) _SWAP( type, x, y )
#define _SWAP( type, x, y ) type temp( x ); x = y; y = temp

#define GA_SUCCESS 0

#endif
