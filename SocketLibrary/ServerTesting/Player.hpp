//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#ifndef GUARD_Player_hpp_
#define GUARD_Player_hpp_

#include <vector>
#include "Hand.hpp"
#include "Card.hpp"

//purpose: This class's purpose is to keep track of player information in a game 
		// a few helper functions give us info about the players data when necessary. 
class Player {
public:
	Player() {
		ready = true;
	}
	int credit;
	int Id;
	bool ready;
	// A hand and its bet
	std::vector<Hand> hands;
	std::vector<int> bets;

	bool createBet( int h, int b );
	void winBet( int h );
	void loseBet( int h );
	void tieBet( int h );
};

#endif