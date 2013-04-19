#ifndef GUARD_Card_hpp_
#define GUARD_Card_hpp_

#include <string>
#include <list>

class Card {
public:
	std::string suit;
	std::string rank;
	int value;

	Card( std::string s, std::string r, int v) : rank(r), suit(s), value(v) {}
	
	std::string name() {
		return rank + " of " + suit;
	}
};

#endif