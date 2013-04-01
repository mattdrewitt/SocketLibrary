#include <UDPServer.hpp>
#include <TCPServer.hpp>

using namespace std;

#pragma comment (lib, "socketLibrary-mt-sgd.lib")
int main() {
	UDPServer udpserver("127.0.0.1", 49154);
	udpserver.Accept();

	cout << "Shutting down.." << endl;

	//TCPServer tcpserver("127.0.0.1", 27016);
	//tcpserver.Listen();
	//tcpserver.Accept();
	//tcpserver.Recv();
	//tcpserver.Send("Gotcha!");

	//cout << "Shutting down.." << endl;
}