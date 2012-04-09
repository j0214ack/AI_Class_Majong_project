/***************************************************
** File: Grid.h
** Function:
** Author: 
** Version: 
** Last Modified: 
** Copyright: 
****************************************************/

class Majong
{
	//-------------------- Public --------------------//
	public :

		struct Card
		{
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
						TYPE_FLOWER
                  DUMMY_END
			};

			TYPE type;
			char num,
				 belong;
		};

   static const Card EMPTY_CARD;
   static const Card WIN_CARD;

	//-------------------- Private --------------------//
	private :


};
static const Card EMPTY_CARD = {DUMMY_END,-1,-1};
static const Card WIN_CARD = {DUMMY_END,888,888};
