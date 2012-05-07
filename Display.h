/***************************************************
 File: Display.h
 Function: show majong card
 Author: Po-Han, Chen
 Version: 1.0.0
 Last Modified: Sun Apr 22 23:20:38 CST 2012
 Copyright: Copyright (C) 2012 Po-Han, Chen
****************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Grid.h"
#include "List.h"
class Game;
class Player;
using user::List;

// Function object
class Display
{
	//-------------------- Public --------------------//
	public :

		// Show game state	
		void operator() ( const Game &, const List<Player>&) const;

	//-------------------- Private --------------------//
	private:

		void showPlayer      ( const Player &player ) const;
		void showSeaCards    ( const List<Majong::Card> &seaCards  ) const;
		void showWallCards   ( const List<Majong::Card> &wallCards ) const;
		void showPrompt      ( const Majong::Card &usableCard ) const;
		void showCardDiagram ( const Majong::Card &card, const unsigned &row ) const;
		void showCardWord    ( const char *word ) const;
};

#endif 
