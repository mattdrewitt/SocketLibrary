#include <UDPClient.hpp>

using namespace std;

#pragma comment (lib, "socketLibrary-mt-sgd.lib")
int main() {
	UDPClient udpclient("127.0.0.1", 49154);
	udpclient.connect();

	cout << "Shutting Down..." << endl;
}