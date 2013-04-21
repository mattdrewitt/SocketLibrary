#include <TCPServer.hpp>

#include "Dealer.hpp"
using namespace std;



int main() {

	Dealer dealer = Dealer();
	Player p = dealer.SetupPlayer();//want to do this once per player when they join 
	dealer.run(); //run the game

	cout << endl << "Game over.  Server shutting Down" << endl;
	system("pause");
}