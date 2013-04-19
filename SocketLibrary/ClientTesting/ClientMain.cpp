#include <UDPClient.hpp>
#include <TCPClient.hpp>
#include <vector>
#include <string>
using namespace std;


class ClientData {
public:
	unsigned int clientId;
	vector<string> clientOptions;
	unsigned int clientBet;
	string clientStatus;  //Ready, not ready, not in 
	ClientData() {}


};


int main() {
	ClientData client;
	TCPClient tcpclient("127.0.0.1", 80);
	//2) Client Connects 
	tcpclient.Connect();

	//4) Client Recvs Id. 	client.clientId
	client.clientId = atoi((tcpclient.Recv()).c_str()); 

	//Recv again.....
	std::string command = tcpclient.Recv();

	

	cout << "sever send me something..." << endl;
	system("pause");
}

