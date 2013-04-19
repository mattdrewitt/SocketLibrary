#include <vector>
#include "Hand.hpp"
#include "Card.hpp"
#include "Player.hpp"

bool Player::createBet( int h, int b ) {
		if( credit >=  b ) {
			credit -= b;
			hands[h][1] += b;
			return true;
		}
		else
		{
			return false;
		}
	}

	void Player::winBet( int h ) {
		credit += (hands[h][1] * 2);
		hands[h][1] = 0;
	}

	void Player::lostBet( int h ) {
		hands[h][1] = 0;
	}