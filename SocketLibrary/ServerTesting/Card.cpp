#include <string>
#include "Card.hpp"

std::string Card::name() {
		return rank + " of " + suit;
	}