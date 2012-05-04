/***************************************************
** File: Grid.h
** Function:
** Author: 
** Version: 
** Last Modified: 
** Copyright: 
****************************************************/
#ifndef GRID_H
#define GRID_H
enum TYPE { TYPE_MILLION,
         TYPE_CIRCLE,
         TYPE_STRING,
         TYPE_N,
         TYPE_S,
         TYPE_E,
         TYPE_W,
         TYPE_M,
         TYPE_RICH,
         TYPE_WHITE,
         TYPE_FLOWER,
         DUMMY_END
};

namespace Majong
{
   struct Card
   {
    public:
      TYPE type;
      char num,
           belong;
      bool operator==(const Card& rhs){
         return (type==rhs.type && num== rhs.num &&belong==rhs.belong);
      }
   };

   const Majong::Card EMPTY_CARD = {DUMMY_END,-1,-1};
   const Majong::Card WIN_CARD = {DUMMY_END,88,88};
};
#endif

