#include <vector>
#include "Hand.hpp"
#include "Card.hpp"


class Player {
public:
	int credit;
	// A hand and its bet
	std::vector<Hand, int> hands;

	bool createBet( int h, int b );
	void winBet( int h );
	void lostBet( int h );
};