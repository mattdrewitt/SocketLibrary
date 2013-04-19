#include <UDPClient.hpp>
#include <TCPClient.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ostream>
#include <sstream>
using namespace std;


class ClientData {
public:
	unsigned int clientId;
	vector<string> clientOptions;
	unsigned int clientBet;
	string clientStatus;  //Ready, not ready, not in 
	ClientData() {}


};

int checkForInt(std::string bet){
	bool check = std::all_of(bet.begin(), bet.end(), ::isdigit);
	if(check){
		return atoi(bet.c_str());
	}
	else{
		return 0;
	}
}

map<int, string> acceptedMoves;

pair<int, string> ProcessChoice(){
	std::string choice;
	cin >> choice;
	int numCheck = checkForInt(choice);
	while(numCheck == 0){
		cout << "Incorrect choice. please chose again." << endl;
		choice = "";
		cin >> choice;
		numCheck = checkForInt(choice);
		if(numCheck != 0){
			break;
		}
	}
	
	if(acceptedMoves.count(numCheck)== 1 ){
		return pair<int, string>(numCheck, choice);
	}
	else{
		return pair<int, string>(0,"");
	}
	//now check if the number is in our map. 	
}


std::string acceptedMoveMessage = "";
	
void ouputChoices(std::string choices) {
	//choices sperated based on "|"
	string word;
	stringstream stream(choices);
	acceptedMoveMessage = "Please Chose an option to procceed in the game:\n";
	int count = 0;
    while( getline(stream, word, '|') ){
		count++;
		acceptedMoveMessage +=	"Choose" + std::to_string(count) + " for " + word + "\n";
		acceptedMoves.insert(pair<int, string>(count, word));
	}
	cout << "" << endl;
	cout << "Your Choice is: " << endl;
}

int main() {
	pair<int, string> choiceToSend;
	ClientData client;
	std::string choice;
	TCPClient tcpclient("127.0.0.1", 80);
	//2) Client Connects 
	tcpclient.Connect();

	//4) Client Recvs Id. 	client.clientId
	client.clientId = atoi((tcpclient.Recv()).c_str()); 
	 string messageData = "";
	 int goodData = 0;
	//Recv again.....
	for(;;){
		char command = (tcpclient.Recv())[0];
		std::string bet;

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
						cin >> bet;	
						goodData = checkForInt(bet);
						while(goodData == 0 ){
							bet = "";
							cout << "Please Bet again, incorrect bet." << endl;
							cin >> bet;
							goodData = checkForInt(bet);
							if(goodData != 0){
								break;
							}
						}			
						tcpclient.Send("b");
						tcpclient.Send(bet);
						
					  break;
				case 't': 
						//s(stand), h(hit), d(double down), p (split)
						choice = tcpclient.Recv();
						ouputChoices(choice);
						choiceToSend = ProcessChoice();
						//check out what the choice is and send the correct letter depending.
						
					  break;
				case 'm': //msg
						messageData = tcpclient.Recv();
						//now we want to split the data on "|"
						//then cout to the screen. 
					  break;
			}
		}
	}
	

	cout << "sever send me something..." << endl;
	system("pause");

}

