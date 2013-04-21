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

//Want the dealer to be like a singleton....not quite sure how to ensure that. 
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