#include <UDPClient.hpp>
#include <TCPClient.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ostream>
#include <Windows.h>
#include <sstream>
using namespace std;



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
		string choice = "";
		cin >> choice;
		numCheck = checkForInt(choice);
		if(numCheck != 0){
			break;
		}
	}

	if(acceptedMoves.count(numCheck)== 1 ){
		return pair<int, string>(numCheck, acceptedMoves.find(numCheck)->second);
	}
	else{
		return pair<int, string>(0,"");
	}
	//now check if the number is in our map. 	
}


std::string acceptedMoveMessage = "";
TCPClient tcpclient;


BOOL WINAPI ConsoleHandler(DWORD CEvent)
{

	//in each of these cases we want to send a message to the server telling it to
	//kill our legacy. 
    switch(CEvent)
    {
    case CTRL_CLOSE_EVENT:
		tcpclient.Send("x");
        break;
    case CTRL_LOGOFF_EVENT:
        
        break;
    case CTRL_SHUTDOWN_EVENT:
       
        break;

    }
    return TRUE;
}

void ouputChoices(std::string choices) {
	//choices sperated based on "|"
	string word;
	stringstream stream(choices);
	acceptedMoveMessage = "Please Chose an option to procceed in the game:\n";
	int count = 0;
	while( getline(stream, word, '|') ){
		count++;
		acceptedMoveMessage +=	"Choose (" + std::to_string(count) + ") for " + word + "\n";
		acceptedMoves.insert(pair<int, string>(count, word));
	}
	cout << acceptedMoveMessage << endl;
	cout << "" << endl;
	cout << "Your Choice is: " << endl;
}



int main() {
	cout << "Client Blackjack" << endl;
	if (SetConsoleCtrlHandler(
    (PHANDLER_ROUTINE)ConsoleHandler,TRUE)==FALSE)
	{
		cout << "Unable to install handler!\n" << endl;
	}
	try
	{
		int credits = 0;
		bool betCorrectly = false;
		std::string revCommand = "";
		pair<int, string> choiceToSend;
		std::string choice;
		tcpclient = TCPClient("127.0.0.1", 80);
		//2) Client Connects 
		tcpclient.Connect();

		//4) Client Recvs Id. 	client.clientId
		int clientId = atoi((tcpclient.Recv()).c_str()); 
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

					credits = atoi((tcpclient.Recv()).c_str());
					//send that we are betting... 
					cout << "Please bet now: ";
					cin >> bet;	
					goodData = checkForInt(bet);
					while(betCorrectly == false){
						goodData = checkForInt(bet);
						if(goodData != 0 && goodData < credits){
							betCorrectly = true;
						}
						else if( goodData != 0 && goodData > credits) {
							cout << "You dont have enough money, bet again." << endl;
						}
						else{
							cout << "\nIncorrect bet, please bet again: ";
						}
						bet = "";
						cin >> bet;
					}//end while. 

						tcpclient.Send(bet);
					break;
				case 't': 
					choice = tcpclient.Recv();
					ouputChoices(choice);
					choiceToSend = ProcessChoice();
					
					if(choiceToSend.second == "hit"){
						tcpclient.Send("h");
					}
					else if(choiceToSend.second == "stand"){
						tcpclient.Send("s");
						revCommand = tcpclient.Recv();
						if(revCommand == "success"){
							cout << "Successful Stand." << endl;
						}
					}
					else if(choiceToSend.second == "double down"){
						tcpclient.Send("d");
					}
					else if(choiceToSend.second == "split"){
						tcpclient.Send("p");
					}
					break;
				case 'm': //msg
					messageData = tcpclient.Recv();
					cout << messageData << "\n" << endl;
					break;
				}
			}
		}
	}
	catch (...) {
	}


	cout << "sever send me something..." << endl;
	system("pause");

}



	


