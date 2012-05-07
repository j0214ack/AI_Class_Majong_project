/***************************************************
** File:
** Function:
** Author:
** Version:
** Last Modified:
** Copyright:
****************************************************/
#ifndef PLAYER_H
#define PLAYER_H
#include "Display.h"
#include "Game.h"
#include "Grid.h"
#include "List.h"

using user::List;

class Game;
class Display;

enum ACTION { ACTION_EAT_FIRST, ACTION_EAT_MIDDLE, ACTION_EAT_LAST,
              ACTION_BON,
              ACTION_LIGHT_GUN, ACTION_DARK_GUN, ACTION_FLOWER_GUN, ACTION_LATE_GUN,
              ACTION_WIN,
              ACTION_DRAW,
              ACTION_PASS,
              ACTION_DISCARD_CARD
            };

class Player
{

	//-------------------- Public --------------------//
   friend class Display;
	public :

		Player( int id ):id_(id),winCount(0),loseCount(0) {}

		ACTION getDecisionFromUsableCard ( const Game & ) const;
		ACTION getDecisionFromDrawCard ( const Game & ) const;

		Majong::Card doAction ( ACTION, const Game & );

        void giveHand(const List<Majong::Card>& hand);

        List<Majong::Card>& getHiddenCards(){return handHidden_;}
        List<Majong::Card>& getRevealedCards(){return handRevealed_;}
        void win(){ winCount++;}
        void lose() {loseCount++;}
        int getWinCount(){ return winCount;}
        int getLoseCount(){return loseCount;}

	//-------------------- Private --------------------//
	private :

		List<Majong::Card> handRevealed_,
						   handHidden_;
		int	id_;
      int winCount;// = 0;
      int loseCount;// = 0&;

      Majong::Card theCardFromDraw;
      //-----Functions----------//
        int countCard ( const List<Majong::Card> &, const Majong::Card &card ) const;
		bool isEatableFirst ( const Game & ) const;
		bool isEatableMiddle ( const Game & ) const;
		bool isEatableLast ( const Game & ) const;
		bool isBonable ( const Game & ) const;
		bool isLightGunable ( const Game & ) const;
		bool isDarkGunable () const;
		bool isFlowerGunable () const;
		bool isLateGunable () const;
		bool isWinable(const Majong::Card &)const ;
		bool isWinable() const;
		bool isWinableForDrawCard()const ;
		bool isWinableForUsableCard (const Game & )const ;
		bool isPassable( const Game & ) const;
		bool isDrawable( const Game & ) const;

		Majong::Card doEatFirst ( const Game & );
		Majong::Card doEatMiddle (  const Game & );
		Majong::Card doEatLast (  const Game & );
		Majong::Card doBon (  const Game & );
		Majong::Card doLightGun (  const Game & );
		Majong::Card doDarkGun ( const Game & );
		Majong::Card doFlowerGun ( const Game & );
		Majong::Card doLateGun (const Game &);
		Majong::Card doWin (  const Game & );
		Majong::Card doDraw(  const Game &);
		Majong::Card doPass(  const Game &);

        Majong::Card makeDecisionForLateGun(const Game &game,List<Majong::Card> &); //AI
        Majong::Card makeDecisionForDarkGun(const Game &game,List<Majong::Card> &); //AI
        ACTION makeDecisionForUsableCard ( Game &, List<ACTION> &); // AI
        ACTION makeDecisionForDrawCard ( Game &, List<ACTION> &); // AI
		Majong::Card decideDiscardCard ( const Game & );  // AI
        // void receiveCard ( Game & );
		bool takeCard(const Majong::Card &,List<Majong::Card> &,const int &num)const;
		bool isComplete(const List<Majong::Card> &);
        void takeCardFromHandHidden (Majong::Card card);
		List<ACTION> getLegalActionForUsableCard ( const Game & ) const;
		List<ACTION> getLegalActionForDrawCard () const;
		List<Majong::Card> getPossibleGan(const List<Majong::Card> &card) const;
};

#endif

