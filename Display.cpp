/***************************************************
 File: Display.h
 Function: show majong card
 Author: Po-Han, Chen
 Version: 1.0.0
 Last Modified: Sun Apr 22 23:20:38 CST 2012
 Copyright: Copyright (C) 2012 Po-Han, Chen
****************************************************/

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

#include "Game.h"
#include "Player.h"
#include "Display.h"

#define GRID_WIDTH  3
#define GRID_HEIGHT 5
#define GRID_HORIZONTAL 12
#define CARD_TYPE_NUM 12

#define SHOW_CARD_TOP() for ( unsigned i_ = 0; i_ < GRID_WIDTH; i_++ ) cout << "--"
const char *hashNumToChinese [10] = { "零", "一", "二", "三", "四", "五", "六", "七", "八", "九" };
const char *hashNumToFlower  [8]  = { "梅", "蘭", "竹", "菊", "春", "夏", "秋", "冬" };

void 
Display::operator() ( const Game &game, const List<Player>& players ) const
{
	for ( unsigned i = 0; i < game.howManyPlayers(); i++ )
	showPlayer( players[i] );

	showSeaCards ( game.getSeaCards() );

	showWallCards( game.getWallCards() );

	showPrompt( game.getUsableCard() );
}

void 
Display::showPlayer ( const Player &player ) const
{
	cout << "==> Player " << player.id_ << " hand revealed card :\n";
	for ( unsigned i = 0; i < GRID_HEIGHT; i++ ) {
		for ( List<Majong::Card>::iterator iter = player.handRevealed_.begin();
										   iter != player.handRevealed_.end(); iter++ ) 
			showCardDiagram( *iter, i );
		cout << "\n";
	}
	cout << "hand hidden card :\n";
	for ( unsigned i = 0; i < GRID_HEIGHT; i++ ) {
		for ( List<Majong::Card>::iterator iter = player.handRevealed_.begin();
										   iter != player.handRevealed_.end(); iter++ ) 
			showCardDiagram( *iter, i );
		cout << "\n";
	}
								
}

void 
Display::showSeaCards  ( const List<Majong::Card> &seaCards  ) const
{
	cout << "==> Sea card  :\n";
	for ( unsigned i = 0; i < seaCards.size(); i += GRID_HORIZONTAL )
		for ( unsigned j = 0; j < GRID_HEIGHT; j++ ) {
			for ( unsigned k = i; k < i + GRID_HORIZONTAL && k < seaCards.size(); k++ )
				showCardDiagram( seaCards[k], j );
			cout << "\n";
		}
}

void 
Display::showWallCards ( const List<Majong::Card> &wallCards ) const
{
	cout << "==> Wall card  :\n";
	for ( unsigned i = 0; i < wallCards.size(); i += GRID_HORIZONTAL )
		for ( unsigned j = 0; j < GRID_HEIGHT; j++ ) {
			for ( unsigned k = i; k < i + GRID_HORIZONTAL && k < wallCards.size(); k++ )
				showCardDiagram( wallCards[k], j );
			cout << "\n";
		}
}

void 
Display::showPrompt ( const Majong::Card &usableCard ) const
{
	cout << "==> Current usable card is :\n";
	for ( unsigned i = 0; i < GRID_HEIGHT; i++ )
		showCardDiagram( usableCard, i );
	cout << ">>> Do what action ( Eat/Bon/Gun/Win/Draw/Pass ) ?\n"
			">>> ";
}

void 
Display::showCardDiagram ( const Majong::Card &card, const unsigned &row ) const
{
	if ( row == 0 || row == GRID_HEIGHT - 1 ) {
		SHOW_CARD_TOP();
		return;
	}

	switch ( card.type ) 
	{
		case TYPE_MILLION :
			if ( row == 1) 
				showCardWord( ::hashNumToChinese[card.num] );
			else if ( row == 2 )
				showCardWord( "  " );
			else if ( row == 3 )
				showCardWord( "萬" );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";
			break;

		case TYPE_CIRCLE :
			if ( row == 1) 
				showCardWord( ::hashNumToChinese[card.num] );
			else if ( row == 2 )
				showCardWord( "  " );
			else if ( row == 3 )
				showCardWord( "筒" );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";

			break;

		case TYPE_STRING :
			if ( row == 1) 
				showCardWord( ::hashNumToChinese[card.num] );
			else if ( row == 2 )
				showCardWord( "  " );
			else if ( row == 3 )
				showCardWord( "條" );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";
			break;

		case TYPE_N :
			if ( row == 1) 
				showCardWord( "  " );
			else if ( row == 2 )
				showCardWord( "北" );
			else if ( row == 3 )
				showCardWord( "  " );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";
			break;

		case TYPE_S :
			if ( row == 1) 
				showCardWord( "  " );
			else if ( row == 2 )
				showCardWord( "南" );
			else if ( row == 3 )
				showCardWord( "  " );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";
			break;

		case TYPE_E :
			if ( row == 1) 
				showCardWord( "  " );
			else if ( row == 2 )
				showCardWord( "東" );
			else if ( row == 3 )
				showCardWord( "  " );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";
			break;

		case TYPE_W :
			if ( row == 1) 
				showCardWord( "  " );
			else if ( row == 2 )
				showCardWord( "西" );
			else if ( row == 3 )
				showCardWord( "  " );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";
			break;

		case TYPE_M :
			if ( row == 1) 
				showCardWord( "  " );
			else if ( row == 2 )
				showCardWord( "中" );
			else if ( row == 3 )
				showCardWord( "  " );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";
			break;

		case TYPE_RICH :
			if ( row == 1) 
				showCardWord( "  " );
			else if ( row == 2 )
				showCardWord( "發" );
			else if ( row == 3 )
				showCardWord( "  " );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";

			break;

		case TYPE_WHITE :
			if ( row == 1) 
				showCardWord( "  " );
			else if ( row == 2 )
				showCardWord( "白" );
			else if ( row == 3 )
				showCardWord( "  " );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";
			break;

		case TYPE_FLOWER :
			if ( row == 1) 
				showCardWord( "  " );
			else if ( row == 2 )
				showCardWord( ::hashNumToFlower[card.num] );
			else if ( row == 3 )
				showCardWord( "  " );
			else
				throw "Invalid row num in Display::showCardDiagram() !\n";
			break;

		default :
			throw "Invalid card type in Display::showCardDiagram() !\n";
			break;
	}
}

void
Display::showCardWord ( const char *word ) const
{
	cout << "| ";
	for ( unsigned i = 0; i < GRID_WIDTH / 3 - 1; i++ ) 
		cout << " ";
	cout<< word;
	for ( unsigned i = 0; i < GRID_WIDTH / 3 - 1; i++ ) 
		cout << " ";
	cout << " |";
}
