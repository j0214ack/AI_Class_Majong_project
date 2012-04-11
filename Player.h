/***************************************************
** File: 
** Function:
** Author: 
** Version: 
** Last Modified: 
** Copyright:
****************************************************/

enum ACTION { ACTION_EAT, ACTION_BON, ACTION_GUN, ACTION_WIN, ACTION_DRAW, ACTION_PASS };

class Player
{

	//-------------------- Public --------------------//
	public :

		Player( int id );

		ACTION getDecision ( const Game & ) const;

		Majong::Card doAction ( ACTION );

      void giveHand(const List<Majong::Card>& hand);



	//-------------------- Private --------------------//
	private :

		List<Majong::Card> handRevealed_,
						   handHidden_;
		int	id_;

		bool isEatable ( const Game & ) const;
		bool isBon ( const Game & ) const;
		bool isGun ( const Game & ) const;
		bool isWin ( const Game & ) const;
		bool isPass( const Game & ) const;

		Majong::Card doEat ();
		Majong::Card doBon ();
		Majong::Card doGun ();
		Majong::Card doWin ();
		Majong::Card doDraw(); 
		Majong::Card doPass();

		void receiveCard ( const Game & );
		Majong::Card discardCard ();

		List<ACTION> getLegalAction ( const Game & ) const;

};

inline void 
Player::doAction( ACTION )
{
	switch ( ACTION ) {
	
	
	
	
	}
}


