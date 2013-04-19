#ifndef GUARD_Hand_hpp_
#define GUARD_Hand_hpp_

#include <string>
#include <vector>

#include "Card.hpp"

class Hand {	
public:
	std::vector<Card> cards;
	Hand(std::vector<Card> c) : cards(c) {}
	Hand() {}

	int value() {
		int count = 0;
		int ace = 0;
		for each(Card c in cards.data) {
			count += c.value;
			if( c.rank == "Ace")
				ace++;
		}
		for( int i = 0; i < ace; i++ ) {
				if( count > 21 )
					count -= 10;
		}
		return count;
	}
};

#endif