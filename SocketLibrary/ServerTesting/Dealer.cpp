//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#include <string>
#include <map>
#include <TCPServer.hpp>
#include <vector>

#include <thread>
#include <mutex>

#include "Shoe.hpp"
#include "Player.hpp"
#include "Hand.hpp"
#include "Card.hpp"
#include "Dealer.hpp"

using namespace std;

mutex playerMutex;
mutex setupMutex;
condition_variable setupCond;

//****Note: Attempted to add threads however they introduced an unexplainable memory leak
//left evidence commented out so you could see our attempt. 


//name:Reset 
//purpose:this function resets the players and the dealers hands. 
void Dealer::Reset(Player p){
	//reset the players cards and the dealers cards. 
	p.bets.clear();
	p.hands.clear();
	dealerHand.clear();
	//run(); 
}


//name:SetupPlayer 
//purpose: this function sets up a player in the dealer's player list. 
Player Dealer::SetupPlayer() {
	connection.Send("1");
	
	//setup player
	Player p = Player();
	p.Id = atoi("1");
	p.credit = 1000;
	Hand h;
	p.hands.push_back(h);
	p.bets.push_back(0);
	{ unique_lock<mutex> lk( setupMutex );
		setupCond.wait( lk ); }
	{ lock_guard<mutex> tl( playerMutex );
		playerList.push_back(p);
	}

	return p;
}


//name: start
//purpose: this function starts the connection to the TCP server
void Dealer::start() {
	connection = TCPServer("127.0.0.1", 80);
	connection.Bind();
	connection.Listen();
	connection.Accept();

	connection.Send("1");
	
	//setup player
	Player p = Player();
	p.Id = atoi("1");
	p.credit = 1000;
	Hand h;
	p.hands.push_back(h);
	p.bets.push_back(0);

	//{ lock_guard<mutex> tl( playerMutex );
		playerList.push_back(p);
	//}
}


//name: bets
//purpose: thus function tells players when to bet if they have enough credits. 
void Dealer::bets() {
	//setupCond.notify_all();
	cout << "Checking for new players..." << endl;
	//Sleep(2000);
	for( size_t i = 0; i < playerList.size(); i++ )
	{
		if( playerList[i].credit > 0 ) {
			connection.Send("m");
			connection.Send("\nYou currently have: " + std::to_string(playerList[i].credit) + " credits.");
			connection.Send("b");
			connection.Send(to_string(playerList[i].credit));

			char cmd = (connection.Recv())[0];

			switch( cmd ) {
			case 'x':
				closesocket(connection.hClient);
				playerList.erase(playerList.begin() + i);
				break;
			case 'b':
				std::string bet = connection.Recv();
				{ lock_guard<mutex> tl( playerMutex );
					playerList[i].createBet(0, atoi(bet.c_str()));
					cout << "Player " << i << " bet: " << playerList[i].bets[0] << endl;
				}
				break;
			}
		}
		else {
			connection.Send("m");
			connection.Send("You have ran out of credits. Game over.");
			connection.Send("q");
			//Add removal code
			{ lock_guard<mutex> tl( playerMutex );
				playerList.erase(playerList.begin() + i);
			}
			closesocket(connection.hClient);
		}
	}
}


//name: draw 
//purpose: this function draws from the correct players when they are ready 
			//and sends back a report message letting them know what cards they currently hold.
void Dealer::draw() {
	for( size_t i = 0; i < playerList.size(); i++ )
	{
		if( playerList[i].ready )
		{
			// Draw the cards
			{ lock_guard<mutex> tl( playerMutex );
				playerList[i].hands[0].cards.push_back(deck.Draw());
				playerList[i].hands[0].cards.push_back(deck.Draw());
				connection.Send("m");
				connection.Send("Your Hand: " + playerList[i].hands[0].to_string());
			}
		}
	}

	// Setup and announce dealers hand
	dealerHand[0].cards.push_back(deck.Draw());
	dealerHand[0].cards.push_back(deck.Draw());
	connection.Send("m");
	connection.Send("Dealers Hand: " + dealerHand[0].to_string());
}


//name:round 
//purpose: this function lets every player have 1 turn per round. 
void Dealer::round() {
	// Every Players turn
	for( size_t i = 0; i < playerList.size(); i++ )
	{
		if( playerList[i].ready )
		{
			if( playerList[i].hands[0].value() == 21 ) {
				connection.Send("m");
				connection.Send("\nCongratulations you got 21!");
			}
			else {
				connection.Send("t");
				bool endTurn = false;
				for(;;){
					std::string commands = "hit|stand|double down";

					// If its the player hasn't had a turn, and they have 2 of the same card they can split
					if( playerList[i].hands[0].cards.size() == 2 )
					{
						if( playerList[i].hands[0].cards[0].value == playerList[i].hands[0].cards[1].value )
							commands += "|split";
					}

					connection.Send(commands);
					char cmd = (connection.Recv())[0];

					// Every time we recieve from the client we want to push ourselves into a switch to read the given commands 
					switch (cmd)
					{
					case 's':
						endTurn = true;
						break;
					case 'h':
						{ lock_guard<mutex> tl( playerMutex );
							playerList[i].hands[0].cards.push_back(deck.Draw());
						}
						if( playerList[i].hands[0].value() > 21 ){
							connection.Send("m");
							connection.Send("Your new hand: " + playerList[i].hands[0].to_string());
							connection.Send("m");
							connection.Send("Sorry your hand went over 21.\n");
							endTurn = true;
						}
						else if( playerList[i].hands[0].value() == 21 ){
							connection.Send("m");
							connection.Send("Your new hand: " + playerList[i].hands[0].to_string());
							connection.Send("m");
							connection.Send("Congratulations you got 21!\n");
							endTurn = true;
						}
						else{
							connection.Send("m");
							connection.Send("Your new Hand: " + playerList[i].hands[0].to_string());
							connection.Send("t");
						}
						break;
					case 'd':
						{ lock_guard<mutex> tl( playerMutex );
							playerList[i].createBet(0, playerList[i].bets[0]);
							connection.Send("m");
							connection.Send("You hand is now worth: " + to_string(playerList[i].bets[0]));
							playerList[i].hands[0].cards.push_back(deck.Draw());
						}
						if( playerList[i].hands[0].value() > 21 ){
							connection.Send("m");
							connection.Send("Your new hand: " + playerList[i].hands[0].to_string());
							connection.Send("m");
							connection.Send("Sorry your hand went over 21.");
							endTurn = true;
						}
						else{
							connection.Send("m");
							connection.Send("Your new Hand: " + playerList[i].hands[0].to_string());
							endTurn = true;
						}

						break;
					case 'p':
						// Create a new hand with the second card in the hand, and then pop it off
						{ lock_guard<mutex> tl( playerMutex );
							playerList[i].hands.push_back(Hand(playerList[i].hands[0].cards[1]));
							playerList[i].hands[0].cards.pop_back();
							playerList[i].hands[0].cards.push_back(deck.Draw());
							playerList[i].hands[1].cards.push_back(deck.Draw());
							playerList[i].createBet(1, playerList[i].bets[0]);
						}
						for( size_t h = 0; h < 2; h++ )
						{
							connection.Send("m");
							connection.Send("Your current hand #" + std::to_string(h+1) + ": " + playerList[i].hands[h].to_string());
							bool endHand = false;
							connection.Send("t");
							//hand logic
							for(;;) {
								cout << h;
								std::string commands = "hit|stand|double down";

								connection.Send(commands);
								char cmd = (connection.Recv())[0];

								//every time we recieve from the client we want to push ourselves into a switch to read the given commands 
								switch (cmd)
								{
								case 's':
									endHand = true;
									break;
								case 'h':
									{ lock_guard<mutex> tl( playerMutex );
										playerList[i].hands[h].cards.push_back(deck.Draw());
									}
									if( playerList[i].hands[h].value() > 21 ){
										connection.Send("m");
										connection.Send("Your new hand #" + std::to_string(h+1) + ": " + playerList[i].hands[h].to_string());
										connection.Send("m");
										connection.Send("Sorry your hand went over 21.");
										endHand = true;
									}
									else{
										connection.Send("m");
										connection.Send("Your new hand #" + std::to_string(h+1) + ": " + playerList[i].hands[h].to_string());
										connection.Send("t");
									}
									break;
								case 'd':
									{ lock_guard<mutex> tl( playerMutex );
										playerList[i].createBet(static_cast<int>(h), playerList[i].bets[h]);
										connection.Send("m");
										connection.Send("You hand is now worth: " + to_string(playerList[i].bets[h]));
										playerList[i].hands[h].cards.push_back(deck.Draw());
									}
									if( playerList[i].hands[h].value() > 21 ) {
										connection.Send("m");
										connection.Send("Your new hand #" + std::to_string(h+1) + ": " + playerList[i].hands[h].to_string());
										connection.Send("m");
										connection.Send("Sorry your hand went over 21.");
										endHand = true;
									}
									else {
										connection.Send("m");
										connection.Send("Your new hand #" + std::to_string(h+1) + ": " + playerList[i].hands[h].to_string());
										endHand = true;
									}
									break;
								case 'x':
									closesocket(connection.hClient);
									{ lock_guard<mutex> tl( playerMutex );
										playerList.erase(playerList.begin() + i);
									}
									endHand = true;
									break;
								}

								if( endHand == true ) {
									break;
								}
							}
						}
						endTurn = true;
						break;
					case 'x':
						closesocket(connection.hClient);
						playerList.erase(playerList.begin() + i);
						endTurn = true;
						break;
					}

					if( endTurn == true)
						break;
				}
			}
		}
	}

	// Dealers turn
	while( dealerHand[0].value() < 17 ) {
		dealerHand[0].cards.push_back(deck.Draw());
		connection.Send("m");
		connection.Send("Dealer hits.\nDealers Hand: " + dealerHand[0].to_string());
		Sleep(1000); //Sleep for a couple seconds so we dont just spam
	}
	if( dealerHand[0].value() < 21 )
	{
		connection.Send("m");
		connection.Send("Dealer Stands.\nDealers Hand: " + dealerHand[0].to_string());
	}
	else if( dealerHand[0].value() == 21 )
	{
		connection.Send("m");
		connection.Send("Dealer got 21!");
	}
	else
	{
		connection.Send("m");
		connection.Send("Dealer Busts.");
	}

	// Evaluate hands and see who won/lost/tied
	for( size_t i = 0; i < playerList.size(); i++ )	{
		if( playerList[i].ready )
		{
			for( size_t h = 0; h < playerList[i].hands.size(); h++ ) {
				if( ( playerList[i].hands[h].value() > 21 && dealerHand[0].value() <= 21 ) || ( playerList[i].hands[h].value() < dealerHand[0].value() && dealerHand[0].value() <= 21 ) ) {
					connection.Send("m");
					connection.Send("\nYou lose hand #" + std::to_string(h+1) + ": -" + to_string(playerList[i].bets[h]) + " credits.");
					{ lock_guard<mutex> tl( playerMutex );
						playerList[i].loseBet(static_cast<int>(h));
					}
				}
				else if( ( playerList[i].hands[h].value() == dealerHand[0].value() ) || ( playerList[i].hands[h].value() > 21 && dealerHand[0].value() > 21 ) )
				{
					connection.Send("m");
					connection.Send("\nYou tie hand #" + std::to_string(h+1) + ".");
					{ lock_guard<mutex> tl( playerMutex );
						playerList[i].tieBet(static_cast<int>(h));
					}
				}
				else
				{
					connection.Send("m");
					connection.Send("\nYou win hand #" + std::to_string(h+1) + ": +" + to_string(playerList[i].bets[h]) + " credits.");
					{ lock_guard<mutex> tl( playerMutex );
						playerList[i].winBet(static_cast<int>(h));
					}
				}
			}
			// Clear the bets and hands
			{ lock_guard<mutex> tl( playerMutex );
				playerList[i].bets.clear();
				playerList[i].hands.clear();
				playerList[i].bets.push_back(0); //initialize this players bet info to 0. 
				Hand h;
				playerList[i].hands.push_back(h);
			}
		}
	}

	// Refresh the dealers hand
	dealerHand.clear();
	Hand h;
	dealerHand.push_back(h);
}