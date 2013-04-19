#include <string>
#include <vector>
#include "Hand.hpp"
#include "Card.hpp"

int Hand::value() {
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

std::string Hand::to_string() {
	std::string str = "";
	for each(Card c in cards.data) {
		str += c.rank + " of " + c.suit + ", ";
	}
	str += "Totaling: " + std::to_string(value()) + "points.";
	return str; 
}