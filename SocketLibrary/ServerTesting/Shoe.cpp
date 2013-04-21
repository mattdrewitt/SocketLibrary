//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012

#include <vector>
#include <string>
#include <algorithm>
#include <ctime> 
#include "Card.hpp"
#include "Shoe.hpp"

//name: myRand
//purpose: randomly generates numbers 
int myRand (int i) { return std::rand()%i;}

//name: init 
//purpose: sets up the shoe upon creation. 
void Shoe::init( int c ) {
	std::string suits[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };
	std::vector<std::pair<std::string, int>> ranks;
	ranks.push_back( std::pair<std::string, int>("Two", 2) );
	ranks.push_back( std::pair<std::string, int>("Three", 3) );
	ranks.push_back( std::pair<std::string, int>("Four", 4) );
	ranks.push_back( std::pair<std::string, int>("Five", 5) );
	ranks.push_back( std::pair<std::string, int>("Six", 6) );
	ranks.push_back( std::pair<std::string, int>("Seven", 7) );
	ranks.push_back( std::pair<std::string, int>("Eight", 8) );
	ranks.push_back( std::pair<std::string, int>("Nine", 9) );
	ranks.push_back( std::pair<std::string, int>("Ten", 10) );
	ranks.push_back( std::pair<std::string, int>("Jack", 10) );
	ranks.push_back( std::pair<std::string, int>("Queen", 10) );
	ranks.push_back( std::pair<std::string, int>("King", 10) );
	ranks.push_back( std::pair<std::string, int>("Ace", 11) );
	//{
	//	{"Ace", 11}, {"King", 10}, {"Queen", 10}, {"Jack", 10}, 
	//	{"Ten", 10}, {"Nine", 9}, {"Eight", 8}, {"Seven", 7},
	//	{"Six", 6}, {"Five", 5}, {"Four", 4}, {"Three", 3}, {"Two", 2}
	//};

	for( int x = 0; x < c; x++ ) {
		for( int y = 0; y < 4; y++ ) {
			for( size_t z = 0; z < ranks.size(); z++ ) {
				deck.push_back(Card( suits[y], ranks[z].first,  ranks[z].second));
			}
		}
	}
	std::srand ( unsigned ( std::time(0) ) );
	std::random_shuffle( deck.begin(), deck.end(), myRand );
}

//name: Draw 
//purpose: a card is picked from the deck and is properly set in the correct lists 
//so that we properly keep track of cards in play, and discarded cards. 
Card Shoe::Draw() {
	if( deck.size() > 0 )
	{
		std::random_shuffle( deck.begin(), deck.end() );
		Card c = deck.back();
		deck.pop_back();
		inPlay.push_back(c);
		return c;
	}
	else
	{
		// Reset the deck from the discarded cards
		deck.insert( discarded.end(), discarded.begin(), discarded.end() );
		discarded.clear();
		std::random_shuffle( deck.begin(), deck.end() );

		Card c = deck.back();
		deck.pop_back();
		inPlay.push_back(c);
		return c;
	}	
}

//name:Discard 
//purpose: when a card is finished with it is added to the discarded list. 
void Shoe::Discard() {
	discarded.insert( inPlay.end(), inPlay.begin(), inPlay.end() );
	inPlay.clear();
}