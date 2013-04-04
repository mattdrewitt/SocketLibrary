#include <UDPServer.hpp>
#include <TCPServer.hpp>

#if defined (_DEBUG) &&  !defined(_DLL)
#pragma comment (lib, "socketLibrary-mt-sgd.lib")
#elif !defined (_DEBUG) &&  !defined(_DLL)
#pragma comment (lib, "socketLibrary-mt-s.lib")
#elif defined (_DEBUG) &&  defined(_DLL)
#pragma comment (lib, "socketLibrary-mt-gd.lib")
#elif !defined (_DEBUG) &&  defined(_DLL)
#pragma comment (lib, "socketLibrary-mt.lib")
#endif

using namespace std;

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