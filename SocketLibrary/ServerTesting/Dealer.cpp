#include <string>
#include <map>
#include <TCPServer.hpp>
#include <vector>

#include "Shoe.hpp"
#include "Player.hpp"
#include "Hand.hpp"
#include "Card.hpp"
#include "Dealer.hpp"

void Dealer::Reset(Player p){
	//reset the players cards and the dealers cards. 
	p.bets.clear();
	p.hands.clear();
	dealerHand.clear();
	run(p); 
}


Player Dealer::SetupPlayer() {
	connection.Send("1");
	
	//setup player
	Player p = Player();
	p.Id = atoi("1");
	return p;
}

void Dealer::run(Player p) {
	p.credit = 1000;
	p.bets.push_back(0); //initialize this players bet info to 0. 
	Hand h;
	p.hands.push_back(h);
	dealerHand.push_back(h);

	// Request/set bet
	connection.Send("b");
	std::string command = connection.Recv();
	if(command == "x"){
		closesocket(connection.hClient);
		dealerHand.clear();
		playerList.clear();
	}
	else{
	std::string bet = connection.Recv();
	p.createBet(0, atoi(bet.c_str()));

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
	client();
	}
}

void Dealer::client() {
	for(;;){
		std::string command = connection.Recv();
		
		//every time we recieve from the client we want to push ourselves into a switch to read the given commands 
		char cmd = 'p';
		if( command == "split" )
			 cmd = 'p';			
		else
			 cmd = command[0];
		if(cmd == 'x'){
			//need to close the handle for the client and break.
			closesocket(connection.hClient);
			dealerHand.clear();
			playerList.clear();
			break;
		}
		switch (cmd)
		{
		case 's':
			connection.Send("success");
			break;
		case 'h':
			playerList[0].hands[0].cards.push_back(deck.Draw());

			if( playerList[0].hands[0].value() > 21 ){
				connection.Send("m");
				connection.Send("Sorry your hand went over 21. Dealer Wins.");
				Reset(playerList[0]);//reset?? 
			}
			else{
				connection.Send("m");
				connection.Send("Your new Hand: " + playerList[0].hands[0].to_string());
			}
			break;
		case 'd':
			playerList[0].hands[0].cards.push_back(deck.Draw());
			playerList[0].createBet(0, playerList[0].bets[0]);
			if( playerList[0].hands[0].value() > 21 )
				connection.Send("fail");
			else
				connection.Send("success");
			   
			break;
		case 'p':
			break;
		}

	}
}