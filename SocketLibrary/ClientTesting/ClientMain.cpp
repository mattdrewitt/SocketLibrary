#include <UDPClient.hpp>
#include <TCPClient.hpp>

using namespace std;

#if defined (_DEBUG) &&  !defined(_DLL)
#pragma comment (lib, "socketLibrary-mt-sgd.lib")
#elif !defined (_DEBUG) &&  !defined(_DLL)
#pragma comment (lib, "socketLibrary-mt-s.lib")
#elif defined (_DEBUG) &&  defined(_DLL)
#pragma comment (lib, "socketLibrary-mt-gd.lib")
#elif !defined (_DEBUG) &&  defined(_DLL)
#pragma comment (lib, "socketLibrary-mt.lib")
#endif
int main() {
	UDPClient udpclient("127.0.0.1", 49154);
	udpclient.connect();

	cout << "Shutting Down..." << endl;
}