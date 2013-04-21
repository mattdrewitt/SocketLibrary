#include <TCPServer.hpp>

#include "Dealer.hpp"
using namespace std;
#include <crtdbg.h>
Dealer dealer;
mutex wakeMutex;
condition_variable wakeCond;

void game() {
	//{ unique_lock<mutex> lk( wakeMutex );
	//	wakeCond.wait( lk ); }
	//dealer.SetupPlayer();
	Hand h;
	dealer.dealerHand.push_back(h);
	// Game loop
	for(;;) {
		if( dealer.playerList.size() > 0 )
		{
		// Accept all the bets
		dealer.bets();

		// Draw and announce everyones cards
		dealer.draw();

		// Run through everyones turn
		dealer.round();
		}
		else {
			break;
		}
	}
}

void start() {
	dealer.start();
	//wakeCond.notify_all();
}

int main() {
	dealer = Dealer();

	//thread th(start);
	//thread th2(game);
	start();
	game();

	//th.join();
	//th2.join();
	//dealer.run(); //run the game

	cout << endl << "Game over.  Server shutting Down" << endl;
	system("pause");
}