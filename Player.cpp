#include "Player.h"
#include "Game.h"
#include "List.h"
#include <iostream>
using namespace std;


void addAction (bool flag, ACTION action,List<ACTION> &actionList)
{
    if (flag)
    {
        actionList.pushBack(action);
    }
    return;
}

void Player::giveHand(const List<Majong::Card> &handCard)
{
    handHidden_ = List<Majong::Card>(handCard);
    return;
};

Majong::Card Player::doAction(ACTION action, const Game &game)
{
    switch (action)
    {
        case ACTION_EAT_FIRST:
            return doEatFirst( game );
        case ACTION_EAT_MIDDLE:
            return doEatMiddle( game );
        case ACTION_EAT_LAST:
            return doEatLast( game );
        case ACTION_BON:
            return doBon( game );
        case ACTION_LIGHT_GUN:
            return doLightGun( game );
        case ACTION_DARK_GUN:
            return doDarkGun( game );
        case ACTION_FLOWER_GUN:
            return doFlowerGun( game );
        case ACTION_LATE_GUN:
            return doLateGun( game );
        case ACTION_DRAW:
            return doDraw( game );
        case ACTION_WIN:
            return doWin( game );
        case ACTION_PASS:
            return doPass( game );
        case ACTION_DISCARD_CARD:
            return decideDiscardCard( game );
        default:
			throw "Error";
    }
};

List<ACTION> Player::getLegalActionForUsableCard ( const Game &game ) const
{
    List<ACTION> actionList;
    addAction(isEatableFirst(game),ACTION_EAT_FIRST,actionList);
    addAction(isEatableMiddle(game),ACTION_EAT_MIDDLE,actionList);
    addAction(isEatableLast(game),ACTION_EAT_LAST,actionList);
    addAction(isBonable(game),ACTION_BON,actionList);
    addAction(isLightGunable(game),ACTION_LIGHT_GUN,actionList);
    addAction(isPassable(game),ACTION_PASS,actionList);
    addAction(isWinableForUsableCard(game),ACTION_WIN,actionList);
    return actionList;
};

List<ACTION> Player::getLegalActionForDrawCard () const
{
    List<ACTION> actionList;
    addAction(isDarkGunable(),ACTION_DARK_GUN,actionList);
    addAction(isFlowerGunable(),ACTION_FLOWER_GUN,actionList);
    addAction(isLateGunable(),ACTION_LATE_GUN,actionList);
    addAction(isWinableForDrawCard(),ACTION_WIN,actionList);
    addAction(true,ACTION_DISCARD_CARD,actionList);
    return actionList;
}

int Player::countCard ( const List<Majong::Card> &cardList, const Majong::Card &card ) const
{
    List<Majong::Card>::iterator it;
    int count = 0;
    for (it=cardList.begin();it!=cardList.end();++it)
    {
        if ((*it)==card)
        {
            count++;
        }
    }
    return count;
}

bool Player::isEatableFirst (const Game &game) const
{
    Majong::Card currentCard = game.getUsableCard();
    Majong::Card middleCard = Majong::Card(currentCard.type,currentCard.num + 1, id_ );
    Majong::Card lastCard = Majong::Card(currentCard.type,currentCard.num + 2, id_ );
    int middleCardCount = countCard(handHidden_,middleCard);
    int lastCardCount = countCard(handHidden_,lastCard);
    return (middleCardCount && lastCardCount )? true: false;

};

bool Player::isEatableMiddle (const Game &game) const
{
#ifndef NDEBUG
START_EXCEPTION
#endif
    Majong::Card currentCard = game.getUsableCard();
    Majong::Card firstCard = Majong::Card(currentCard.type,currentCard.num - 1 , id_ );
    Majong::Card lastCard = Majong::Card(currentCard.type,currentCard.num + 1, id_ );
	if ( currentCard.num > 10 )
		throw IndexError( "currentCard.num > 10", currentCard.num, 10 );
    int firstCardCount = countCard(handHidden_, firstCard);
    int lastCardCount = countCard(handHidden_, lastCard);
    return (firstCardCount && lastCardCount)? true : false;
#ifndef NDEBUG
	END_EXCEPTION( "Player::isEatableLast ( const Game & )" );
#endif
};

bool Player::isEatableLast (const Game &game) const
{
    Majong::Card currentCard = game.getUsableCard();
    Majong::Card firstCard = Majong::Card(currentCard.type,currentCard.num - 2 , id_ );
    Majong::Card middleCard = Majong::Card(currentCard.type,currentCard.num - 1 , id_ );
    int firstCardCount = countCard(handHidden_, firstCard);
    int middleCardCount = countCard(handHidden_, middleCard);
    return (firstCardCount && middleCardCount)? true : false;
};

bool Player::isBonable (const Game &game) const
{
    Majong::Card currentCard = game.getUsableCard();
    List<Majong::Card>::iterator it;
    int currentCardCount = countCard(handHidden_, currentCard);
    return (currentCardCount>=2)?true:false;
};

bool Player::isLightGunable (const Game &game) const
{
    Majong::Card currentCard = game.getUsableCard();
    if (currentCard.belong == id_ - 1 || currentCard.belong == id_ -1 + game.howManyPlayers() ) // Card is from the up player
    {
        return false;
    }
    else
    {
        List<Majong::Card>::iterator it;
        int currentCardCount = countCard(handHidden_, currentCard);
        return (currentCardCount>=3)?true:false;
    }
};

bool Player::isDarkGunable () const
{
    List<Majong::Card> tempList = List<Majong::Card>(handHidden_);
    List<Majong::Card>::iterator listIt;
    while (!tempList.isEmpty())
    {
        Majong::Card currentCard = tempList.popFront();
        int num = 0;
        for (listIt=tempList.begin();listIt!=tempList.end();++listIt)
        {
            if (currentCard==*listIt)
            {
                tempList.remove(listIt);
                num++;
            }
            if (num==3)
            {
                return true;
            }
        }
    }
    return false;
};

bool Player::isFlowerGunable() const
{
    List<Majong::Card>::iterator listIt;
    for (listIt = handHidden_.begin(); listIt!=handHidden_.end(); ++listIt)
    {
        if (listIt->type==TYPE_FLOWER)
        {
            return true;
        }
    }
    return false;
};

bool Player::isLateGunable() const
{
    List<Majong::Card> tempList = List<Majong::Card>(handHidden_);
    List<Majong::Card>::iterator listIt;
    for (listIt = handRevealed_.begin();listIt!=handRevealed_.end(); ++listIt)
    {
        if (listIt->belong!=id_)
        {
            if ((*(listIt-1) == *listIt) && (*(listIt+1) == *listIt))
            {
                tempList.pushBack(*listIt);
                if(countCard(handHidden_,*listIt)>0)
                {
                    return true;
                }
            }
        }
    }
    return false;
};

bool Player::isPassable (const Game &game) const
{
    Majong::Card currentCard = game.getUsableCard();
    // int playerNum = ???
    if (currentCard.belong==id_-1 || currentCard.belong==id_-1 + game.howManyPlayers())
    {
        return false;
    }
    else
    {
        return true;
    }
};

List<Majong::Card> Player::getPossibleGan(const List<Majong::Card> &cardList) const
{
    List<Majong::Card> ganList;
    List<Majong::Card> tempList = List<Majong::Card>(cardList);
    Majong::Card tempCard;
    while (tempList.size()!=0)
    {
        tempCard = tempList.popFront();
        int count = 0;
        List<Majong::Card>::iterator listIt;
        for (listIt=tempList.begin();listIt!=tempList.end();++listIt)
        {
            if (*listIt==tempCard)
            {
                count++;
                tempList.remove(listIt);
            }
        }
        if (count>=1)
        {
            ganList.pushBack(tempCard);
        }
    }
    return ganList;
}

bool Player::isWinableForUsableCard (const Game &game) const
{
    Majong::Card currentCard = game.getUsableCard();
    return isWinable(currentCard);
};

bool Player::isWinableForDrawCard() const
{
    return isWinable();
};

bool Player::isWinable (const Majong::Card &card)  const
{
    List<Majong::Card> tempList = List<Majong::Card>(handHidden_);
    tempList.pushBack(card);
    List<Majong::Card> ganList = getPossibleGan(tempList);
    bool flag = false;
    List<Majong::Card>::iterator listIt;
    for (listIt=ganList.begin();listIt!=ganList.end();++listIt)
    {
        List<Majong::Card> tempList2 = List<Majong::Card>(tempList);
        if (takeCard(*listIt,tempList2,2))
        {
            flag = flag || isComplete(tempList2);
            if (flag)
            {
                return true;
            }
        }
        else
        {
            cout<<"isWinable has a bug !!!"<<endl;
        }
    }
    return false;
};

bool Player::isWinable () const
{
    List<Majong::Card> tempList = List<Majong::Card>(handHidden_);
    List<Majong::Card> ganList = getPossibleGan(tempList);
    bool flag = false;
    List<Majong::Card>::iterator listIt;
    for (listIt=ganList.begin();listIt!=ganList.end();++listIt)
    {
        List<Majong::Card> tempList2 = List<Majong::Card>(tempList);
        if (takeCard(*listIt,tempList2,2))
        {
            flag = flag || isComplete(tempList2);
            if (flag)
            {
                return true;
            }
        }
        else
        {
            cout<<"isWinable has a bug !!!"<<endl;
        }
    }
    return false;
};
bool Player::takeCard(const Majong::Card &card,List<Majong::Card> &cardList,const int &num) const
{
    List<Majong::Card>::iterator listIt;
    int count = countCard(cardList,card);
    if (count<num)
    {
        return false;
    }
    else
    {
        for (listIt=cardList.begin();listIt!=cardList.end();++listIt)
        {
            if (*listIt==card)
            {
                cardList.remove(listIt);
                num--;
                if (num==0)
                {
                    return true;
                }
            }
        }
    }
    cout<<"take card error!"<<endl;
    return false;
}

bool Player::isComplete(const List<Majong::Card> &cardList)
{
    if (cardList.size()==0)
    {
        return true;
    }
    else
    {
        List<Majong::Card> tempList = List<Majong::Card>(cardList);
        Majong::Card firstCard = tempList.popFront();
        Majong::Card beforeCard = Majong::Card(firstCard.type,firstCard.num-1,id_);
        Majong::Card beforeBeforeCard = Majong::Card(firstCard.type,firstCard.num-2,id_);
        Majong::Card afterCard = Majong::Card(firstCard.type,firstCard.num+1,id_);
        Majong::Card afterAfterCard = Majong::Card(firstCard.type,firstCard.num+2,id_);
        int beforeCardCount = countCard(tempList,beforeCard);
        int beforeBeforeCardCount =countCard(tempList,beforeBeforeCard);
        int firstCardCount = countCard(tempList,firstCard);
        int afterCardCount = countCard(afterCard,firstCard);
        int afterAfterCardCount = countCard(afterAfterCard,firstCard);
        if (beforeCardCount && beforeBeforeCardCount)
        {
            List<Majong::Card> tempList2 = List<Majong::Card>(tempList);
            takeCard(beforeBeforeCard,tempList2,1);
            takeCard(beforeCard,tempList2,1);
            if (isComplete(tempList2))
            {
                return true;
            }
        }
        else if (beforeCardCount && afterCardCount)
        {
            List<Majong::Card> tempList2 = List<Majong::Card>(tempList);
            takeCard(beforeCard,tempList2,1);
            takeCard(afterCard,tempList2,1);
            if (isComplete(tempList2))
            {
                return true;
            }
        }
        else if (afterCardCount && afterAfterCardCount)
        {
            List<Majong::Card> tempList2 = List<Majong::Card>(tempList);
            takeCard(afterCard,tempList2,1);
            takeCard(afterAfterCard,tempList2,1);
            if (isComplete(tempList2))
            {
                return true;
            }
        }
        else if (firstCardCount>=2)
        {
            List<Majong::Card> tempList2 = List<Majong::Card>(tempList);
            takeCard(firstCard,tempList2,2);
            if (isComplete(tempList2))
            {
                return true;
            }
        }
    }
    return false;
};

bool Player::isDrawable (const Game &game) const
{
    Majong::Card currentCard = game.getUsableCard();
    return (currentCard.belong==id_-1 || currentCard.belong==id_-1+game.howManyPlayers())?false:true;
};

void Player::takeCardFromHandHidden(const Majong::Card card)
{
    List<Majong::Card>::iterator ListIt;
    bool flag = false;
    for (ListIt=handHidden_.begin();ListIt!=handHidden_.end();++ListIt)
    {
        if (*ListIt==card)
        {
            handHidden_.remove(ListIt);
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        cerr<<"no this card in handHidden!"<<endl;
    }
    return;
};

Majong::Card Player::doEatFirst ( Game &game )
{
    Majong::Card currentCard = game.getUsableCard();
    Majong::Card middleCard = Majong::Card(currentCard.type,currentCard.num + 1, id_ );
    Majong::Card lastCard = Majong::Card(currentCard.type,currentCard.num + 2, id_ );
    takeCardFromHandHidden(middleCard);
    takeCardFromHandHidden(lastCard);
    handRevealed_.push_back(middleCard);
    handRevealed_.push_back(CurrentCard);
    handRevealed_.push_back(lastCard);
    return decideDiscardCard(game);
};

Majong::Card Player::doEatMiddle ( const Game &game )
{
    Majong::Card currentCard = game.getUsableCard();
    Majong::Card firstCard = Majong::Card(currentCard.type,currentCard.num - 1, id_ );
    Majong::Card lastCard = Majong::Card(currentCard.type,currentCard.num + 1, id_ );
    takeCardFromHandHidden(firstCard);
    takeCardFromHandHidden(lastCard);
    handRevealed_.push_back(firstCard);
    handRevealed_.push_back(currentCard);
    handRevealed_.push_back(lastCard);
    return decideDiscardCard(game);
}

Majong::Card Player::doEatLast ( const Game &game )
{
    Majong::Card currentCard = game.getUsableCard();
    Majong::Card firstCard = Majong::Card(currentCard.type,currentCard.num - 1, id_ );
    Majong::Card middleCard = Majong::Card(currentCard.type,currentCard.num - 2, id_ );
    takeCardFromHandHidden(firstCard);
    takeCardFromHandHidden(middleCard);
    handRevealed_.push_back(firstCard);
    handRevealed_.push_back(currentCard);
    handRevealed_.push_back(middleCard);
    return decideDiscardCard(game);
}

Majong::Card Player::doBon ( const Game &game )
{
    Majong::Card currentCard = game.getUsableCard();
    Majong::Card currentCardInHidden = Majong::Card(currentCard.type,currentCard.num,id_);
    takeCardFromHandHidden(currentCardInHidden);
    takeCardFromHandHidden(currentCardInHidden);
    handRevealed_.push_back(currentCardInHidden);
    handRevealed_.push_back(currentCard);
    handRevealed_.push_back(currentCardInHidden);
    return decideDiscardCard(game);
};

Majong::Card Player::doLightGun ( const Game &game )
{
    Majong::Card currentCard = game.getUsableCard();
    Majong::Card currentCardInHidden = Majong::Card(currentCard.type,currentCard.num,id_);
    takeCardFromHandHidden(currentCardInHidden);
    takeCardFromHandHidden(currentCardInHidden);
    takeCardFromHandHidden(currentCardInHidden);
    handRevealed_.push_back(currentCardInHidden);
    handRevealed_.push_back(currentCardInHidden);
    handRevealed_.push_back(currentCardInHidden);
    handRevealed_.push_back(currentCard);
    return decideDiscardCard(game);
};

Majong::Card Player::doDarkGun (const Game &game)
{
    List<Majong::Card> possibleDarkGunList;
    List<Majong::Card> tempList = List<Majong::Card>(handHidden_);
    List<Majong::Card> listIt;
    while (!tempList.isEmpty())
    {
        Majong::Card currentCard = tempList.popFront();
        int num = 0;
        for (listIt=tempList.begin();listIt!=tempList.end();++listIt)
        {
            if (currentCard==*listIt)
            {
                tempList.remove(listIt);
                num++;
            }
            if (num==3)
            {
                possibleDarkGunList.pushBack(currentCard);
            }
        }
    }
    Majong::Card darkGunCard = makeDecisionForDarkGun(game,possibleDarkGunList);
    takeCardFromHandHidden(darkGunCard);
    takeCardFromHandHidden(darkGunCard);
    takeCardFromHandHidden(darkGunCard);
    takeCardFromHandHidden(darkGunCard);
    handRevealed_.pushBack(darkGunCard);
    handRevealed_.pushBack(darkGunCard);
    handRevealed_.pushBack(darkGunCard);
    handRevealed_.pushBack(darkGunCard);
    return doDraw(game);
};

Majong::Card Player::doFlowerGun ()
{
    List<Majong::Card>::iterator listIt;
    Majong::Card flowerCard;
    for (listIt=handHidden_.begin();listIt!=handHidden_.end();++listIt)
    {
        if (listIt->type==TYPE.FLOWER)
        {
            flowerCard = *listIt;
        }
    }
    takeCardFromHandHidden(flowerCard);
    handRevealed_.push_back(flowerCard);
    return doDraw(game);
};

Majong::Card Player::doLateGun (const Game &game)
{
    List<Majong::Card>::iterator listIt;
    List<Majong::Card> tempList;
    List<Majong::Card> possibleLateGunList;

    for (listIt = handRevealed_.begin();listIt!=handRevealed_.end(); ++listIt)
    {
        if (listIt->belong!=id_)
        {
            if ((*(listIt-1) == *listIt) && (*(listIt+1) == *listIt))
            {
                tempList.pushBack(*listIt);
            }
        }
    }

    for (listIt=tempList.begin();listIt!=tempList.end();++listIt)
    {
        int num = countCard(*listIt,handHidden_);
        if (num>0)
        {
            possibleLateGunList.pushBack(*listIt);
        }
    }

    Majong::Card lateGunCard = makeDecisionForLateGun(game,possibleLateGunList);
    takeCardFromHandHidden(lateGunCard);
    handRevealed_.pushBack(lateGunCard);
    return doDraw(game);
};

Majong::Card Player::doPass ( const Game &game )
{
    return PASS_CARD;
    // return Pass Card;
};

Majong::Card Player::doWin ( const Game &game )
{
    return Majong::WIN_CARD;
};

Majong::Card Player::doDraw ( Game &game )
{
    handHidden_.pushFront(game.draw(id_));
    List<ACTION> legalAction = getLegalActionForDrawCard();
    ACTION action = makeDecisionForDrawCard(game,legalAction);
    return doAction(action);
};

Majong::Card player::makeDecisionForLateGun(const Game &game,List<Majong::Card> &)
{

};

Majong::Card player::makeDecisionForDarkGun(const Game &game,List<Majong::Card> &)
{

};

ACTION player::makeDecisionForDrawCard(const Game &game, List<ACTION> &actionList)
{

};

ACTION player::makeDecisionForUsableCard (const Game &game, List<ACTION> &actionList)
{

};

Majong::Card decideDiscardCard(const Game &game)
{

};
