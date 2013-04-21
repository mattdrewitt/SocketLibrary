//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012

#include <string>
#include <vector>
#include "Hand.hpp"
#include "Card.hpp"

//name:value
//purpose:returns the value of a hand of cards. 
int Hand::value() {
	int count = 0;
	int ace = 0;
	for( size_t i = 0; i < cards.size(); i++) {
		count += cards[i].value;
		if( cards[i].rank == "Ace")
			ace++;
	}
	for( int i = 0; i < ace; i++ ) {
		if( count > 21 )
			count -= 10;
	}
	return count;
}

//name:
//purpose: returns the total value of a hand of cards in a nice print out message. 
std::string Hand::to_string() {
	std::string str = "";
	for( size_t i = 0; i < cards.size(); i++) {
		str += cards[i].rank + " of " + cards[i].suit + ", ";
	}
	str += "Totaling: " + std::to_string(value()) + " points.";
	return str; 
}