/***************************************************
** File: Game.h
** Function: 
** Author: 
** Version: 
** Last Modified: 
** Copyright: 
****************************************************/
#ifndef GAME_H 
#define GAME_H
#include "macro.h"
#include "List.h"
#include "Grid.h"
#include "Display.h"
#include "Player.h"

class Display;
class Player;


using user::List;

enum EndOfGame { ONE_WINS_ONE, ONE_WINS_ALL, NO_WIN, NOT_YET };
class Game
{

//-------------------- Public --------------------//
public:

   Game (int playerNum,const Display& d);

   Majong::Card drawFromHead (int id);
   Majong::Card drawFromTail (int id);

   void run ();

   Majong::Card getUsableCard() const;

   int getCurrentPlayerId() const;
   int howManyPlayers() const;
   int getLianChuangNum() const;

   List<Majong::Card> getSeaCards() const;
   List<Majong::Card> getWallCards() const;

//-------------------- Private --------------------//
private:
   
   void updateUsableCard(Majong::Card newCard);

   void givePlayersHands();

   void oneRound ();
   bool oneGame ();
   EndOfGame oneTurn ();

   void gameOver ();

   void initializeCards ();

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
#endif

