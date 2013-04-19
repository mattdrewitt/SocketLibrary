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

bool checkForGarbage(std::string toCheck, std::string expected){


}

int main() {
	ClientData client;
	TCPClient tcpclient("127.0.0.1", 80);
	//2) Client Connects 
	tcpclient.Connect();

	//4) Client Recvs Id. 	client.clientId
	client.clientId = atoi((tcpclient.Recv()).c_str()); 

	//Recv again.....
	for(;;){
		char command = (tcpclient.Recv())[0];

		//every time we recieve from the server we want to push ourselves into a switch to read the given commands 
		if(command == 'q'){
			break;
		}
		else {
			switch (command)
			{
				case 'b':
					   //send that we are betting... 
					    cout << "Please bet now..... " << endl;
						int bet;
						cin >> bet;
						tcpclient.Send("bet");
						tcpclient.Send(std::to_string(bet));
						
					  break;
				case 't':
					  break;
				case 'm':
					  break;
				case 'f':
					  break;
				case 's':
					  break;
			}
		}
	}
	

	cout << "sever send me something..." << endl;
	system("pause");

}

