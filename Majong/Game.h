/***************************************************
** File: Game.h
** Function: 
** Author: 
** Version: 
** Last Modified: 
** Copyright: 
****************************************************/

#define PLAYER_NUM 2

#include "macro.h"

class Game
{

	//-------------------- Public --------------------//
	public :
	
		Game (int playerNum);
	
		Majong::Card draw (int id);

		void run ();

      Majong::Card getUsableCard() const;

      int getCurrentPlayerId() const;

	//-------------------- Private --------------------//
	private :
		
		void refreshUsableCard ();

		void oneTurn ();

		void show ();

		void gameOver ();

		void initailizeCards ();

      Majong::Card drawCardFromWall();

      void updateUsableCard(Majong::Card newCard, int playerId);

      //Members
      int playerNum_;
		List<Player> players_;
		Majong::Card usableCard;
	 	List<Majong::Card> seaCard,
					 	      wallCard;
      int currentPlayerId_;

};

inline void
Game::run ()
{

	List<ACTION> legalAction_p1( player_[0].getLegalAction() ),
	             legalAction_p2( player_[1].getLegalAction() ),
	             legalAction_p3( player_[2].getLegalAction() ),
	             legalAction_p4( player_[3].getLegalAction() );

	List<Player> doOrder( sort( legalAction_p1,
								legalAction_p2,
								legalAction_p2,
								legalAction_p4 ) );

	

}
