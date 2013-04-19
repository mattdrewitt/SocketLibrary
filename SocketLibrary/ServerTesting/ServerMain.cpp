#include <UDPServer.hpp>
#include <TCPServer.hpp>

#include "Dealer.hpp"
using namespace std;






int main() {
	Dealer dealer = Dealer();

	dealer.run();
	//TCPServer tcpserver(AF_INET, "127.0.0.1", 80);
	//Create the Dealer. 

	//1)Server Listens 
	//tcpserver.Listen();

	//3)Server Accepts 
	//tcpserver.Accept();

	//4)Server Sends Client Id....how to do this externally.  
	//tcpserver.Send("all"); 

	//6)Server recieves status 

	//7)if status is ready, server sends total money 

	//9) server recieves bet. 

	//10) Server sends cards message somehow...
			//-need to send client other clients cards and dealers cards and betting options. 

	system("pause");
}