#include <UDPServer.hpp>
#include <TCPServer.hpp>

#include "Dealer.hpp"
using namespace std;






int main() {

		Dealer dealer = Dealer();
		Player p = dealer.SetupPlayer();//want to do this once per player when they join 
		dealer.run(p); //want to do this once per player every round. 


	system("pause");
}