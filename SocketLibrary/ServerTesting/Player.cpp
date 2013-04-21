//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012

#include <vector>
#include "Hand.hpp"
#include "Card.hpp"
#include "Player.hpp"



//name:createBet
//purpose: based on the player we store the bet, and decrement the credits. 
bool Player::createBet( int h, int b ) {
	if( credit >=  b ) {
		if( h == 1 && bets.size() == 1 )
			bets.push_back(0);
		credit -= b;
		bets[h] += b;
		return true;
	}
	else
	{
		return false;
	}
}

//name:winBet
//purpose: this function is called if a player has won their bet 
void Player::winBet( int h ) {
	credit += (bets[h] * 2);
	bets[h] = 0;
}

//name:loseBet
//purpose: this function is called if the player has lost their bet 
void Player::loseBet( int h ) {
	bets[h] = 0;
}

//name:tieBet
//purpose: this function is called if a player has tied the dealer in a bet 
void Player::tieBet( int h ) {
	credit += bets[h];
	bets[h] = 0;
}