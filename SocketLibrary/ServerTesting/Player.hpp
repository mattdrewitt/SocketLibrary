#ifndef GUARD_Player_hpp_
#define GUARD_Player_hpp_

#include <vector>
#include "Hand.hpp"
#include "Card.hpp"


class Player {
public:
	Player() {
		ready = true;
	}
	int credit;
	int Id;
	bool ready;
	// A hand and its bet
	std::vector<Hand> hands;
	std::vector<int> bets;

	bool createBet( int h, int b );
	void winBet( int h );
	void loseBet( int h );
	void tieBet( int h );
};

#endif