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
private:
	std::vector<Player> playerList;
	Shoe deck;

	std::vector<Hand> dealerHand;
	void Reset(Player p);
	TCPServer connection;
	//unsigned int ClientReady(std::string clientMsg);
public:
	Dealer() {
		deck = Shoe(4);
		connection = TCPServer("127.0.0.1", 80);
		connection.Bind();
		connection.Listen();
		connection.Accept();
	}
	Player SetupPlayer();
	void run();
	void bets();
	void draw();
	void round();
	
};

#endif