#include <UDPServer.hpp>
#include <UDPClient.hpp>
#include <TCPServer.hpp>

using namespace std;

#pragma comment (lib, "socketLibrary-mt-sgd.lib")
int main() {
	/*UDPServer udpserver("127.0.0.1", 49154);
	udpserver.Accept();

	cout << "Shutting down.." << endl;*/

	UDPClient udpclient("127.0.0.1", 49153);
	udpclient.connect();

	cout << "Shutting Down..." << endl;

	//TCPServer tcpserver("127.0.0.1", 27016);
	//tcpserver.Listen();
	//tcpserver.Accept();
	//tcpserver.Recv();
	//tcpserver.Send("Gotcha!");

	//cout << "Shutting down.." << endl;
}