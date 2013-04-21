//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 
#ifndef GUARD_Dealer_hpp_
#define GUARD_Dealer_hpp_

#include <string>
#include <map>
#include <TCPServer.hpp>
#include <vector>

#include "Shoe.hpp"
#include "Player.hpp"
#include "Hand.hpp"
#include "Card.hpp"

//purpose: The dealer class's purpose is to act like a singleton and take care of all players, decks, 
//and TCPServer connection information. 
class Dealer {
public:
	std::vector<Player> playerList;
	Shoe deck;

	std::vector<Hand> dealerHand;
	void Reset(Player p);
	TCPServer connection;

	Dealer() {
		deck = Shoe(4);
	}
	void start();
	Player SetupPlayer();
	void bets();
	void draw();
	void round();
	
};

#endif