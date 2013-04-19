#include <UDPServer.hpp>
#include <TCPServer.hpp>

using namespace std;






int main() {

	//Create a dealer. 

	//UDPServer udpserver("127.0.0.1", 49154);
	//udpserver.Accept();

	//cout << "Shutting down.." << endl;

	TCPServer tcpserver(AF_INET, "127.0.0.1", 80);
	tcpserver.Listen();
	tcpserver.Send("all");
	//tcpserver.Accept();
	//as soon as we accept we have a client who is ready for cards 
	//dealer.SendUpClient. 

	//tcpserver.Recv();
	//tcpserver.Send("Gotcha!");

	//cout << "Shutting down.." << endl;
	system("pause");
}