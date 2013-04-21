//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#ifndef GUARD_Card_hpp_
#define GUARD_Card_hpp_

#include <string>

//purpose: The card class acts like a data structure to contain information about a card in a deck. 
class Card {
public:
	std::string suit;
	std::string rank;
	int value;

	Card( std::string s, std::string r, int v) : rank(r), suit(s), value(v) {}
	
	std::string to_string();
};

#endif