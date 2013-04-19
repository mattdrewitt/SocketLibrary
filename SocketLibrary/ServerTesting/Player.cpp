#include <vector>
#include "Hand.hpp"
#include "Card.hpp"
#include "Player.hpp"

bool Player::createBet( int h, int b ) {
		if( credit >=  b ) {
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

	void Player::lostBet( int h ) {
		bets[h] = 0;
	}