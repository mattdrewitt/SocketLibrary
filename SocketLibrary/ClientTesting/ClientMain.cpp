#include <UDPClient.hpp>
#include <TCPClient.hpp>

using namespace std;

int main() {
	UDPClient udpclient("127.0.0.1", 49154);
	udpclient.connect();

	cout << "Shutting Down..." << endl;
}