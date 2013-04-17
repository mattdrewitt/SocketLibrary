
#include <string>
#include <map>

//ok so...should the objects go here or client side????
//dealer, player 
//numberdata --card, value, type

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
	typedef NumberData Cards[3];  //each player never has more than 3 cards. 
	//std::map<unsigned int, Cards> playerHands; //each player may have more than 1 hand if they "split" 
public:
	
};


//Want the dealer to be like a singleton....not quite sure how to ensure that. 
class Dealer {
private:

public:
	Dealer() {}
};