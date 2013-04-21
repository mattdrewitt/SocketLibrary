//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#ifndef GUARD_Hand_hpp_
#define GUARD_Hand_hpp_

#include <string>
#include <vector>

#include "Card.hpp"

//purpose: This classes purpose is to keep track a list of cards aka a hand. each client gets a hand when they
//			join the game. 
class Hand {	
public:
	std::vector<Card> cards;
	Hand(Card c) {
		cards.push_back(c);
	}
	Hand() {}
	
	int value();
	std::string to_string();
};

#endif