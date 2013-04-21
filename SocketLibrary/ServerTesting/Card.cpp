//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012

#include <string>
#include "Card.hpp"

//name: to_string
//purpose: Helper function that returns the rank and suit of a card. 
std::string Card::to_string() {
		return rank + " of " + suit;
	}