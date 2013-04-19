#include <vector>
#include <string>
#include "Card.hpp"


class Shoe {
	std::vector<Card> deck;
	std::vector<Card> discarded;
	std::vector<Card> inPlay;
public:
	Shoe( int c ) {
		init(c);
	}

	Shoe() {
		init(1);
	}

	void init( int c );
	Card Draw();
	void Discard();
};