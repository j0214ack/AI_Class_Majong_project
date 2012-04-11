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
   enum EndOfGame { ONE_WINS_ONE, THREE_WIN_ONE, ONE_WINS_ALL, NO_WIN, NOT_YET }
public :

   Game (int playerNum);

   Majong::Card draw (int id);

   void run ();

   Majong::Card getUsableCard() const;

   int getCurrentPlayerId() const;

//-------------------- Private --------------------//
private :
   
   void updateUsableCard(Majong::Card newCard, int playerId);

   void oneRound ();
   void oneGame ();
   EndOfGame oneTurn ();

   void show ();

   void gameOver ();

   void initailizeCards ();

   Majong::Card drawCardFromWall();

   //Members
   int dealerId_;
   int playerNum_;
   int currentPlayerId_;
   int loserId_;
   int winnerId_;
   List<Player> players_;
   Majong::Card usableCard;
   List<Majong::Card> seaCard,
                     wallCard;

};

