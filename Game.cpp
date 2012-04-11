#include "Game.h"
#include "rnGen.h"
#include <algorithm>
#include <vector>

using namespace std;

static UnsignRnNumGen randGen();

//return true if i<j
static bool compareActions (Action i, Action j){
   if (j == ACTION_BON || j == ACTION_GUN){ return true; }
   else if (i == ACTION_BON || i == ACTION_GUN){ return false; }
   else if ( (j == ACTION_EAT || j == ACTION_DRAW) ) { return true; } 
   else return false;
}


Game::Game(int playerNum) : dealerId_(0), playerNum_(playerNum), currentPlayerId_(0),
                            loserId_(-1), winnerId_(-1), players_(), seaCards_(), wallCards_()
{
   initializeCards();
   usableCard = Majong::EMPTY_CARD;
   for(int i =0;i<playerNum;i++){
      List<Majong::Card> hand();
      for(int j =0;j<16;j++){
         hand.pushBack(draw(i));
      }
      players.insert(i,Player(i,hand));
   }
}

Majong::Card
Game::draw (int id){
   drawnCard = wallCards_.remove(randGen(players_.size()));
   drawnCard.belong = id;
   return drawnCard;
}

void
Game::run() {
}

Majong::Card
Game::getUsableCard() const {
}

int
Game::getCurrentPlayerId() const {
}

//-------------------- Private --------------------//
void
Game::refreshUsableCard (){
}

void//one round means every player had been the dealer once
Game::oneRound(){
}

void
Game::oneGame(){
   updateUsableCard(players_[currentPlayerId_].doAction(ACTION_DRAW),0);
   EndOfGame endStatus = oneTurn();
   while ( endStatus == NOT_YET ){
      oneTurn();
   }
   if ( endStatus != NO_WIN && (winnerId_ != dealerId_) ){
      if (dealerId_ == playerNum_ - 1){ dealerId_ = 0; }
      else dealerId_ += 1;
   }
   switch(endStatus){
      case ONE_WINS_ONE:
         break;
      case THREE_WIN_ONE:
         break;
      case ONE_WINS_ALL:
         break;
      case NO_WIN:
         break;
   }
}

EndOfGame
Game::oneTurn(){
   if ( usableCard_ == WIN_CARD ){
      return ONE_WINS_ALL;
   }
   if ( wallCard_.size() <= 16 ){
      winnerId_ = -1;
      return NO_WIN;
   }
   vector<ACTION> playerDecisions(playerNum_);
   int winCount = 0;
   for(int i =0;i<playerNum_;i++){
      playerDecisions[i] = players_.getDecision((*this));
      if (playerDecisions[i] == ACTION_WIN){
         winCount++;
      }
   }
   if (winCount < 1){
      priorityAction = max_element(sortedAction.begin(),sortedAction.end(),compareActions);
      for(int i=0;i<playerNum_;i++){
         if (playerDecisions[i] == priorityAction ){
            updateUsableCard(players_[i].doAction(priorityAction),i);
            if ( usableCard_ == WIN_CARD ){
               return ONE_WINS_ALL;
            }
            else return NOT_YET
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
      else if ( winCount == 3){
         return THREE_WIN_ONE;
      }
      else {
         for(winnerId_ = usableCard_.belong;winnerId<playerNum_;winnerId++){
            if (playerDecicsions[winnerId_] == ACTION_WIN){
               return ONE_WINS_ONE
            }
         }
         for(winnerId_ = 0;winnerId<usableCard_.belong;winnerId++){
            if (playerDecicsions[winnerId_] == ACTION_WIN){
               return ONE_WINS_ONE
            }
         }
      }
   }
}

void
Game::show (){
}

void
Game::gameOver (){
}

void
Game::updateUsableCard(Majong::Card newCard,int playerId){
   currentPlayerId_ = playerId;
   usableCard_ = newCard;
   seaCard_.pushBack(newCard);
}

void
Game::initailizeCards(){
   //feed {x,y,z} as parameter only available with c++0x
   for(int i =0;i<4;i++){
      for (int j=1;j<=9;j++){
         wallCards_.pushBack({TYPE_MILLION,j,-1});
         wallCards_.pushBack({TYPE_CIRCLE,j,-1});
         wallCards_.pushBack({TYPE_STRING,j,-1});
      }
      wallCards_.pushBack({TYPE_N,0,-1});
      wallCards_.pushBack({TYPE_S,0,-1});
      wallCards_.pushBack({TYPE_E,0,-1});
      wallCards_.pushBack({TYPE_W,0,-1});
      wallCards_.pushBack({TYPE_M,0,-1});
      wallCards_.pushBack({TYPE_RICH,0,-1});
      wallCards_.pushBack({TYPE_WHITE,0,-1});
      for(int j=1;j<=8;j++){
         wallCards_.pushBack({TYPE_FLOWER,j,-1});
      }
   }
}

