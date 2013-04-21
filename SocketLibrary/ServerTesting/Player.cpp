#include <vector>
#include "Hand.hpp"
#include "Card.hpp"
#include "Player.hpp"




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

void Player::winBet( int h ) {
	credit += (bets[h] * 2);
	bets[h] = 0;
}

void Player::loseBet( int h ) {
	bets[h] = 0;
}
void Player::tieBet( int h ) {
	credit += bets[h];
	bets[h] = 0;
}