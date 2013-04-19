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

	std::vector<Hand>  dealerHand;
	
	TCPServer connection;
	//unsigned int ClientReady(std::string clientMsg);
public:
	Dealer() {
		deck = Shoe(4);
		connection = TCPServer(AF_INET, "127.0.0.1", 80);
		connection.Listen();
		connection.Accept();
	}

	void run();
	void client();
};