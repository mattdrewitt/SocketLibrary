#include <vector>
#include "Hand.hpp"
#include "Card.hpp"


class Player {
public:
	int credit;
	int bet;
	std::vector<Hand> hands;

	bool createBet( int b ) {
		if( credit >=  b ) {
			credit -= b;
			bet += b;
			return true;
		}
		else
		{
			return false;
		}
	}
};