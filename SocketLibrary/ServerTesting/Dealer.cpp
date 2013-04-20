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
	connection.Send("m");
	connection.Send("You currently have: " + std::to_string(p.credit) + " credits.");
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


	playerList.push_back(p);
	client();
	}
}

void Dealer::client() {
	for( size_t i = 0; i < playerList.size(); i++ )
	{
		connection.Send("t");
		bool endTurn = false;
		//turn logic
		for(;;){
			std::string commands = "h|s|d";

			// If its the player hasn't had a turn, and they have 2 of the same card they can split
			if( playerList[i].hands[0].cards.size() == 2 )
			{
				if( playerList[i].hands[0].cards[0].rank == playerList[i].hands[0].cards[1].rank )
					commands += "|p";
			}

			connection.Send(commands);
			char cmd = (connection.Recv())[0];

			//every time we recieve from the client we want to push ourselves into a switch to read the given commands 
			switch (cmd)
			{
			case 's':
				connection.Send("s");
				endTurn = true;
				break;
			case 'h':
				playerList[i].hands[0].cards.push_back(deck.Draw());

				if( playerList[i].hands[0].value() > 21 ){
					connection.Send("m");
					connection.Send("Sorry your hand went over 21. Dealer Wins.");
					endTurn = true;
					//Reset(playerList[i]);//reset?? 
				}
				else{
					connection.Send("m");
					connection.Send("Your new Hand: " + playerList[i].hands[0].to_string());
				}
				break;
			case 'd':
				if( playerList[i].createBet(0, playerList[i].bets[0]) == false )
				{
					connection.Send("f");
				}
				else
				{
					playerList[i].hands[0].cards.push_back(deck.Draw());
					playerList[i].createBet(0, playerList[i].bets[0]);
					connection.Send("success");
					if( playerList[i].hands[0].value() > 21 ){
						connection.Send("m");
						connection.Send("Sorry your hand went over 21. Dealer Wins.");
						endTurn = true;
						//Reset(playerList[i]);//reset?? 
					}
					else{
						connection.Send("m");
						connection.Send("Your new Hand: " + playerList[i].hands[0].to_string());
					}
				}

				break;
			case 'p':
				// Create a new hand with the second card in the hand, and then pop it off
				playerList[i].hands[1] = Hand(playerList[i].hands[0].cards[1]);
				playerList[i].hands[0].cards.pop_back();
				for( size_t h = 0; h < 2; h++ )
				{
					connection.Send("m");
					connection.Send("Your current hand #" + std::to_string(h+1) + ": " + playerList[i].hands[h].to_string());
					bool endHand = false;
					//hand logic
					for(;;){
						std::string commands = "h|s|d";

						connection.Send(commands);
						char cmd = (connection.Recv())[0];

						//every time we recieve from the client we want to push ourselves into a switch to read the given commands 
						switch (cmd)
						{
						case 's':
							connection.Send("s");
							endHand = true;
							break;
						case 'h':
							playerList[i].hands[h].cards.push_back(deck.Draw());

							if( playerList[i].hands[h].value() > 21 ){
								connection.Send("m");
								connection.Send("Sorry your hand went over 21.");
								endHand = true;
								//Reset(playerList[i]);//reset?? 
							}
							else{
								connection.Send("m");
								connection.Send("Your new hand #" + std::to_string(h+1) + ": " + playerList[i].hands[h].to_string());
							}
							break;
						case 'd':
							if( playerList[i].createBet(0, playerList[i].bets[0]) == false )
							{
								connection.Send("f");
							}
							else
							{
								playerList[i].hands[h].cards.push_back(deck.Draw());
								playerList[i].createBet(h, playerList[i].bets[h]);
								connection.Send("s");
								if( playerList[i].hands[h].value() > 21 ){
									connection.Send("m");
									connection.Send("Sorry your hand #" + std::to_string(h+1) + " went over 21.");
									endHand = true;
									//Reset(playerList[i]);//reset?? 
								}
								else{
									connection.Send("m");
									connection.Send("Your new hand #" + std::to_string(h+1) + ": " + playerList[i].hands[h].to_string());
								}
							}

							break;
						case 'x':
							closesocket(connection.hClient);
							dealerHand.clear();
							playerList.clear();
							endHand = true;
							break;
						}

						if( endHand == true) {
							break;
						}
					}
				}
				break;
			case 'x':
				closesocket(connection.hClient);
				dealerHand.clear();
				playerList.clear();
				endTurn = true;
				break;
			}

			if( endTurn == true) {
				//connection.Send("e"); //end turn
				break;
			}
		}
	}
}