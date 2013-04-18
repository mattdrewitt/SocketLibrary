//
#include <string>
#include <map>
#include <list>
#include <TCPServer.hpp>
#include <vector>
//
////ok so...should the objects go here or client side????
////dealer, player 
////numberdata --card, value, type

//Simply a data class.... 
class NumberData {
private:
	std::string card;
	unsigned int value;
	bool isFaceCard;
public:
	NumberData(std::string& c, unsigned int& val, bool& isFace) : card(c), value(val), isFaceCard(isFace){}
};


class Player {
private:
	double  playerBet;
	bool    isDealer;
	typedef NumberData Cards[3];  //each player never has more than 3 cards. 
	//std::map<unsigned int, Cards> playerHands; //each player may have more than 1 hand if they "split" 
public:
	
};


//Want the dealer to be like a singleton....not quite sure how to ensure that. 
class Dealer {
private:

	std::list<Player> playerList;
	void fillDecks(); //default to 3 decks....?
	std::vector<NumberData>  cards;
	std::vector<NumberData> discarded;
	unsigned int * SendClientInitialCards(); 
	//unsigned int ClientReady(std::string clientMsg);
public:
	Dealer() {
	TCPServer tcpserver(AF_INET, "127.0.0.1", 80);
	tcpserver.Listen();
	//tcpserver.Accept();  //want to pass an accept message? 
	}

};