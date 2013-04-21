#include <string>
#include <vector>
#include "Hand.hpp"
#include "Card.hpp"

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

std::string Hand::to_string() {
	std::string str = "";
	for( size_t i = 0; i < cards.size(); i++) {
		str += cards[i].rank + " of " + cards[i].suit + ", ";
	}
	str += "Totaling: " + std::to_string(value()) + " points.";
	return str; 
}