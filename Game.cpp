#include "Game.h"
#include "rnGen.h"
#include <algorithm>
#include <vector>

using namespace std;
using user::List;

static UnsignRnNumGen randGen;

//return true if i<j
static bool compareActions (ACTION i, ACTION j){
   if (j == ACTION_BON || j == ACTION_LIGHT_GUN){ return true; }
   else if (i == ACTION_BON || i == ACTION_LIGHT_GUN){ return false; }
   else if ( (j == ACTION_EAT_FIRST || j == ACTION_EAT_MIDDLE ||
              j == ACTION_EAT_LAST  || j == ACTION_DRAW) ) { return true; } 
   else return false;
}


Game::Game(int playerNum,const Display& d) : 
                            dealerId_(0), playerNum_(playerNum), 
                            currentPlayerId_(0), loserId_(-1), winnerId_(-1), 
                            lianChuangNum_(0), players_(), 
                            usableCard_(Majong::EMPTY_CARD), seaCards_(), 
                            wallCards_(), display_(d)
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   for(int i =0;i<playerNum;i++){
      players_.insert(i,Player(i));
   }
   //should init display_ right? TODO
#ifndef NDEBUG
   END_EXCEPTION( "Game construtor" );
#endif
}

Majong::Card
Game::drawFromHead (int id)
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   Majong::Card drawnCard = wallCards_.popFront();
   drawnCard.belong = id;
   return drawnCard;
#ifndef NDEBUG
   END_EXCEPTION( "Game::drawFromHead" );
#endif
}

Majong::Card
Game::drawFromTail (int id)
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   Majong::Card drawnCard = wallCards_.popBack();
   drawnCard.belong = id;
   return drawnCard;
#ifndef NDEBUG
   END_EXCEPTION( "drawFromTail" );
#endif
}

void
Game::run()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   for(int i=0;i<4;i++){
      oneRound();
   }
   gameOver();
#ifndef NDEBUG
   END_EXCEPTION( "run()" );
#endif
}

Majong::Card
Game::getUsableCard() const
{
   return usableCard_;
}

int
Game::getCurrentPlayerId() const 
{
   return currentPlayerId_;
}

int
Game::howManyPlayers() const 
{
   return playerNum_;
}

int
Game::getLianChuangNum() const 
{
   return lianChuangNum_;
}
List<Majong::Card> 
Game::getSeaCards() const 
{
   return seaCards_;
}

List<Majong::Card>
Game::getWallCards() const
{
   return wallCards_;
}
//-------------------- Private --------------------//
void//one round means every player had been the dealer once
Game::oneRound()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   for(int i=0;i<4;){
      if (oneGame()){
         i++;
         lianChuangNum_ = 0;
         if (dealerId_ == playerNum_ - 1){ dealerId_ = 0; }
         else dealerId_ += 1;
      }
   }
   //when different orientation is implemented, should set orietation here
   //and also in oneGame(); TODO
#ifndef NDEBUG
   END_EXCEPTION( "oneRound()" );
#endif
}

bool//return true if dealer changed
Game::oneGame()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   initializeCards();
   givePlayersHands();
   currentPlayerId_ = dealerId_;
   winnerId_ = -1; loserId_ = -1;
   updateDisplay();
   updateUsableCard(players_[currentPlayerId_].doAction(ACTION_DRAW));
   updateDisplay();
   EndOfGame endStatus = oneTurn();
   while ( endStatus == NOT_YET ){
      oneTurn();
   }
   //below should do the winning counting TODO
   switch(endStatus){
      case ONE_WINS_ONE:
         players_[winnerId_].win();
         players_[loserId_].lose();
         break;
      case ONE_WINS_ALL:
         for(int i=0;i<playerNum_;i++){
            if (playerNum_ == winnerId_){
               continue;
            }
            players_[winnerId_].win();
            players_[i].lose();
         }
         break;
      case NO_WIN:
         break;
      default:
         break;
   }
   if ( endStatus != NO_WIN && (winnerId_ != dealerId_) ){
      return true;
   }
   else {
      lianChuangNum_++;
      return false;
   }
#ifndef NDEBUG
   END_EXCEPTION( "oneGame()" );
#endif
}

EndOfGame
Game::oneTurn()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   if ( usableCard_ == Majong::WIN_CARD ){
      return ONE_WINS_ALL;
   }
   if ( wallCards_.size() <= 16 ){
      winnerId_ = -1;
      return NO_WIN;
   }
   vector<ACTION> playerDecisions(playerNum_);
   int winCount = 0;
   for(int i =0;i<playerNum_;i++){
      playerDecisions[i] = players_[i].getDecisionFromUsableCard((*this));
      if (playerDecisions[i] == ACTION_WIN){
         winCount++;
      }
   }
   if (winCount < 1){
      ACTION priorityAction = *max_element(playerDecisions.begin(),playerDecisions.end(),compareActions);
      for(int i=0;i<playerNum_;i++){
         if (playerDecisions[i] == priorityAction ){
            currentPlayerId_ = i;
            updateUsableCard(players_[i].doAction(priorityAction));
            if ( usableCard_ == Majong::WIN_CARD ){
               return ONE_WINS_ALL;
            }
            else return NOT_YET;
         }
      }
   }
   else { //someones win(s)
      loserId_ = usableCard_.belong;
      if (winCount == 1){
         for(winnerId_=0;winnerId_<playerNum_;winnerId_++){
            if (playerDecisions[winnerId_] == ACTION_WIN ){
               return ONE_WINS_ONE;
            }
         }
      }
      else {
         for(winnerId_ = usableCard_.belong;winnerId_<playerNum_;winnerId_++){
            if (playerDecisions[winnerId_] == ACTION_WIN){
               return ONE_WINS_ONE;
            }
         }
         for(winnerId_ = 0;winnerId_<usableCard_.belong;winnerId_++){
            if (playerDecisions[winnerId_] == ACTION_WIN){
               return ONE_WINS_ONE;
            }
         }
      }
   }
   throw 123;
#ifndef NDEBUG
   END_EXCEPTION( "oneTurn()" );
#endif
}

void
Game::givePlayersHands()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   for(int i =0;i<playerNum_;i++){
      List<Majong::Card> hand;
      for(int j =0;j<16;j++){
         hand.pushBack(drawFromHead(i));
      }
      players_[i].giveHand(hand);
   }
#ifndef NDEBUG
   END_EXCEPTION( "givePlayersHands()" );
#endif
}

void
Game::gameOver ()
{//TODO
#ifndef NDEBUG
START_EXCEPTION
#endif
/*
   End of whole Majong Game,
   shall we show statistics of each player?
*/
#ifndef NDEBUG
END_EXCEPTION( "gameOver()");
#endif
}

void
Game::updateUsableCard(Majong::Card newCard)
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   usableCard_ = newCard;
   seaCards_.pushBack(newCard);
   updateDisplay();
#ifndef NDEBUG
   END_EXCEPTION( "updateUsableCard");
#endif
}

void
Game::initializeCards()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   //feed {x,y,z} as parameter only available with c++0x
   List<Majong::Card> newCards;
   for(int i =0;i<4;i++){
      for (int j=1;j<=9;j++){
         newCards.pushBack(Majong::Card(TYPE_MILLION,j,-1));
         newCards.pushBack(Majong::Card(TYPE_CIRCLE,j,-1));
         newCards.pushBack(Majong::Card(TYPE_STRING,j,-1));
      }
      newCards.pushBack(Majong::Card(TYPE_N,0,-1));
      newCards.pushBack(Majong::Card(TYPE_S,0,-1));
      newCards.pushBack(Majong::Card(TYPE_E,0,-1));
      newCards.pushBack(Majong::Card(TYPE_W,0,-1));
      newCards.pushBack(Majong::Card(TYPE_M,0,-1));
      newCards.pushBack(Majong::Card(TYPE_RICH,0,-1));
      newCards.pushBack(Majong::Card(TYPE_WHITE,0,-1));
   }
   for(int j=1;j<=8;j++){
      newCards.pushBack(Majong::Card(TYPE_FLOWER,j,-1));
   }
   while(newCards.size() > 0 ){
      wallCards_.pushBack(newCards.remove(randGen(newCards.size())));
   }
#ifndef NDEBUG
   END_EXCEPTION( "initializeCards()");
#endif
}

void
Game::updateDisplay()
{
#ifndef NDEBUG
START_EXCEPTION
#endif
   display_((*this),players_);
#ifndef NDEBUG
   END_EXCEPTION( "updateDisplay()");
#endif
}

