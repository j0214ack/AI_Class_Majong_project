/***************************************************
** File: Game.h
** Function: 
** Author: 
** Version: 
** Last Modified: 
** Copyright: 
****************************************************/
#include "macro.h"

class Game
{

//-------------------- Public --------------------//
   enum EndOfGame { ONE_WINS_ONE, ONE_WINS_ALL, NO_WIN, NOT_YET }
public :

   Game (int playerNum,const Display& d);

   Majong::Card draw (int id);

   void run ();

   Majong::Card getUsableCard() const;

   int getCurrentPlayerId() const;
   int howManyPlayers() const;
   int getLianChuangNum() const;

   List<Majong::Card> getSeaCards_() const;
   List<Majong::Card> getWallCards_() const;

//-------------------- Private --------------------//
private :
   
   void updateUsableCard(Majong::Card newCard);

   void oneRound ();
   bool oneGame ();
   EndOfGame oneTurn ();

   void gameOver ();

   void initailizeCards ();

   Majong::Card drawCardFromWall();

   void updateDisplay();

   //Members
   int dealerId_;
   int playerNum_;
   int currentPlayerId_;
   int loserId_;
   int winnerId_;
   int lianChuangNum_;
   List<Player> players_;
   Majong::Card usableCard_;
   List<Majong::Card> seaCards_,
                     wallCards_;
   Display display_;

};

