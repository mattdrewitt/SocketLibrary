#include <string>
#include "Card.hpp"

std::string Card::to_string() {
		return rank + " of " + suit;
	}