#include <string>
#include <map>
#include <TCPServer.hpp>
#include <vector>

#include "Shoe.hpp"
#include "Player.hpp"
#include "Hand.hpp"
#include "Card.hpp"
#include "Dealer.hpp"

void Dealer::run() {
	connection.Send("1");
	
	//setup player
	Player p = Player();
	p.credit = 1000;

	// Request/set bet
	connection.Send("b");
	std::string command = connection.Recv();
	p.createBet(0, atoi(command.c_str()));

	// Draw the cards
	p.hands[0].cards.push_back(deck.Draw());
	p.hands[0].cards.push_back(deck.Draw());
	connection.Send("m");
	connection.Send("Your Hand: " + p.hands[0].to_string());

	dealerHand[0].cards.push_back(deck.Draw());
	dealerHand[0].cards.push_back(deck.Draw());
	connection.Send("m");
	connection.Send("Dealers Hand: " + dealerHand[0].to_string());

	connection.Send("t");
	connection.Send("hit|stand|double down|split");

	playerList.push_back(p);

	connection.Send("t");
	client();
}

void Dealer::client() {
	for(;;){
		std::string command = connection.Recv();

		//every time we recieve from the client we want to push ourselves into a switch to read the given commands 
		char cmd;
		if( command == "split" )
			cmd = 'p';			
		else
			char cmd = command[0];

		switch (cmd)
		{
		case 'b':
			//request betting
			//int bet;
			//connection.Send("bet");
			//connection.Recv(std::to_string(bet));

			break;
		case 's':
			connection.Send("s");
			break;
		case 'h':
			playerList[0].hands[0].cards.push_back(deck.Draw());

			if( playerList[0].hands[0].value() > 21 )
				connection.Send("f");
			else
				connection.Send("s");
			break;
		case 'd':
			playerList[0].hands[0].cards.push_back(deck.Draw());
			playerList[0].createBet(0, playerList[0].bets[0]);
			if( playerList[0].hands[0].value() > 21 )
				connection.Send("f");
			else
				connection.Send("s");
			break;
		case 'p':
			break;
		}

	}
}