/***************************************************
** File: main.cpp
** Function: Running the game 'Majong''
** Author: 
** Version:
** Last Modified:
** Copyright:
****************************************************/

// Import atoi()
#include <cstdlib>

#include "Game.h"

int main( int argc, char *argv[] ) 
{

START_EXCEPTION
   Display display();
	Game game(2,display);
	game.run();

END_EXCEPTION
	
	return MAJONG_SUCCESS;
} 
