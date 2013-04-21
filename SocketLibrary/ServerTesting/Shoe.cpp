#include <vector>
#include <string>
#include <algorithm>
#include <ctime> 
#include "Card.hpp"
#include "Shoe.hpp"

// random generator:
int myRand (int i) { return std::rand()%i;}

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

//issue with draw: we start with the same cards every time, we need to shuffle before we 
//get a card....i dont think random shuffle works quite like we think. 
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

void Shoe::Discard() {
	discarded.insert( inPlay.end(), inPlay.begin(), inPlay.end() );
	inPlay.clear();
}