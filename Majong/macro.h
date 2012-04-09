/***************************************************
** File: macro.h
** Function: Contain some useful macro
** Author: Po-Han, Chen
** Version: 1.0.0
** Last Modified: Tue Apr  3 14:17:10 CST 2012
** Copyright: Copyright (C) 2012 Po-Han, Chen
****************************************************/

#ifndef USER_MACRO_H
#define USER_MACRO_H

// game.exe return value
#define MAJONG_SUCCESS 0
#define MAJONG_FAILURE 1

// Start try {} catch {} statement
#define START_EXCEPTION try {
#define END_EXCEPTION } catch ( const char *err ) { \
	std::cout << "Runtime error : " << err << std::endl;\
	return MAJONG_FAILURE;}

// Check runtime error and pause
#define CHECK( condition, err ) _CHECK( condition, err )
#define _CHECK( condition, err ) if ( condition ) { \
	std::cout << "Error ==> " << __FILE__ << " : line " << __LINE__ << std::endl\
		  	  << "          " << err << std::endl;\
	std::cout << "Press any key to continue...";\
	std::cin.get(); } 

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

#endif
