//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012

#ifndef GUARD_Shoe_hpp_
#define GUARD_Shoe_hpp_

#include <vector>
#include <string>
#include "Card.hpp"

//purpose: this class's purpose is to maintain the decks of cards in the  game play.
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

#endif