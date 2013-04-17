#include <UDPServer.hpp>
#include <TCPServer.hpp>

using namespace std;




int main() {
	//UDPServer udpserver("127.0.0.1", 49154);
	//udpserver.Accept();

	//cout << "Shutting down.." << endl;

	TCPServer tcpserver(AF_INET, "127.0.0.1", 80);
	//tcpserver.Listen();
	//tcpserver.Accept();
	//tcpserver.Recv();
	//tcpserver.Send("Gotcha!");

	//cout << "Shutting down.." << endl;
}