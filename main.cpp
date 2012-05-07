/*=================================================
 File     : main.cpp
 Function : run game
 Author   : 
 Version  : 1.0.0
 Last Modified : Sat May  5 23:47:54 CST 2012
 Copyright:
 ==================================================*/

// Import atoi()
#include <cstdlib>

#include "Game.h"
#include "macro.h"

int main() 
{

START_MAIN_EXCEPTION

    Display display;
	Game game(2,display);
	game.run();

END_MAIN_EXCEPTION
	
	return MAJONG_SUCCESS;
} 
