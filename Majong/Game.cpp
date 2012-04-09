#include "Game.h"
#include "rnGen.h"
#include <algorithm>
#include <vector>

using namespace std;

static UnsignRnNumGen randGen();

//return true if i<j
static bool sortingActions (Action i, Action j){
   
}


Game::Game(int playerNum) : playerNum_(playerNum), 
                            players_(), seaCards_(), wallCards_(), currentPlayerId_(0)
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
   updateUsableCard(players_[currentPlayerId_].doAction(ACTION_DRAW),currentPlayerId_);
   while( true ){
      vector<ACTION> playerDecisions(playerNum_);
      int winCount = 0;
      for(int i =0;i<playerNum_;i++){
         playerDecisions[i] = players_.getDecision((*this));
         if (playerDecisions[i] == ACTION_WIN){
            winCount++;
         }
      }
      if (winCount < 1){
         priorityAction = max_element(sortedAction.begin(),sortedAction.end(),sortingAction);
         for(int i=0;i<playerNum_;i++){
            if (playerDecisions[i] == priorityAction ){
               updateUsableCard(players_[i].doAction(priorityAction),i);
               continue;
            }
         }
      }
      else { //someones win(s)
         if (winCount == 1){
            for(int i=0;i<playerNum_;i++){
               if (playerDecisions[i] == priorityAction ){
                  winPlayerId = i;
                  break;
               }
            }
         }
      }
      //'til now, haven't deal with multiple winning circumstances
   }
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

void
Game::oneTurn (){
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

