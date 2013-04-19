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

	int value();
	std::string to_string();
};

#endif