#include <vector>
#include <string>
#include <algorithm>
#include "Card.hpp"


class Shoe {
	std::vector<Card> deck;
	std::vector<Card> discarded;
	std::vector<Card> inPlay;
public:
	Shoe( int c ) {
		init(c);
	}

	Shoe() {
		init(1);
	}

	void init( int c ) {
		std::string suits[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };
		std::vector<std::string, int> ranks = {
			{"Ace", 11}, {"King", 10}, {"Queen", 10}, {"Jack", 10}, 
			{"Ten", 10}, {"Nine", 10}, {"Eight", 10}, {"Seven", 10},
			{"Six", 10}, {"Five", 10}, {"Four", 10}, {"Three", 10}, {"Two", 10}
		};
		
		for( int x = 0; x < c; x++ ) {
			for( int y = 0; y < 4; y++ ) {
				for( int z = 0; z < ranks.size(); z++ ) {
					deck.push_back(Card( suits[y], ranks[z][0],  ranks[z][1]));
				}
			}
		}

		std::random_shuffle( deck.begin(), deck.end() );
	}

	Card Draw() {
		if( deck.size() > 0 )
		{
			Card c = deck.back();
			deck.pop_back();
			inPlay.push_back(c);
			return c;
		}
		else
		{
			deck.insert( discarded.end(), discarded.begin(), discarded.end() );
			discarded.clear();
		}	
	}

	void Discard() {
		discarded.insert( inPlay.end(), inPlay.begin(), inPlay.end() );
		inPlay.clear();
	}
};