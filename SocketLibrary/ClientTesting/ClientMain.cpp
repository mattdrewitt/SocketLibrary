//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 
#include <crtdbg.h>
#include <UDPClient.hpp>
#include <TCPClient.hpp>
#include <string>
#include <algorithm>
#include <map>
#include <Windows.h>
#include <sstream>
#include <iostream>
using namespace std;

//******************Global Variables********************************** 
map<int, string> acceptedMoves;
std::string acceptedMoveMessage = "";
TCPClient tcpclient;
//*********************************************************************


//********************Helper Functions********************************* 

//name:checkForInt
//purpose: checks to see if the inputed string contains only digits. 
int checkForInt(std::string bet){
	bool check = std::all_of(bet.begin(), bet.end(), ::isdigit);
	if(check){
		return atoi(bet.c_str());
	}
	else{
		return 0;
	}
}




//name:ProcessChoise
//purpose: checks to see if the chosen digit for turn based action is infact a number,
		  //and is contained in our acceptedMoves function.
pair<int, string> ProcessChoice(){
	bool acceptedChoice = false;
	int numCheck = 0;
	std::string choice = "";
	while(acceptedChoice == false){
		cin >> choice;
		cout << endl;
		numCheck = checkForInt(choice);
		if(numCheck == 0){
			cout << "Incorrect choice. please chose again." << endl;
		}
		if(acceptedMoves.count(numCheck)== 1 ){
			acceptedChoice = true;
		}

		else{
			cout << "Incorrect choice, please choose again." << endl;
		}
	}
	return pair<int, string>(numCheck, acceptedMoves.find(numCheck)->second);	
	//now check if the number is in our map. 	
}




//name:ConsoleHandler
//purpose: This function listens to the console and ensures that if a close event occurs, 
			//we send the proper closing information to the server 
			//avoids memory leaks server side. 
BOOL WINAPI ConsoleHandler(DWORD CEvent)
{

	//in each of these cases we want to send a message to the server telling it to
	//kill our legacy. 
    switch(CEvent)
    {
    case CTRL_CLOSE_EVENT:
		try{
		tcpclient.Send("x");
		}
		catch(...){
			cout << "Error closing socket information for this client." << endl;
		}
        break;
    case CTRL_LOGOFF_EVENT:
        
        break;
    case CTRL_SHUTDOWN_EVENT:
       
        break;

    }
    return TRUE;
}



//name:outputChoices
//purpose: This function shows the correct turn action information based on the list of accepted moves
		//it is then displayed to the console.
void ouputChoices(std::string choices, int credit, int bet) {
	//choices sperated based on "|"
	string word;
	stringstream stream(choices);
	acceptedMoveMessage = "Please choose an option to procceed in the game:\n";
	int count = 0;
	while( getline(stream, word, '|') ){
		if( (word == "double down" || word == "split") )
		{
			if(  (credit - (bet * 2)) > 0 )
			{
				count++;
				acceptedMoveMessage +=	"Choose (" + std::to_string(count) + ") for " + word + "\n";
				acceptedMoves.insert(pair<int, string>(count, word));
			}
		}
		else
		{
			count++;
			acceptedMoveMessage +=	"Choose (" + std::to_string(count) + ") for " + word + "\n";
			acceptedMoves.insert(pair<int, string>(count, word));
		}
	}
	cout << endl << acceptedMoveMessage << endl;
	cout << "Your Choice is: ";
}

//***************************************************************************

int main() {
	cout << "*****************Client Blackjack******************" << endl;
	// For when the 2 projects start together
	Sleep(1000);
	//set the handler to ensure that on close we properly clean up our socket handle.
	if (SetConsoleCtrlHandler(
    (PHANDLER_ROUTINE)ConsoleHandler,TRUE)==FALSE)
	{
		cout << "Unable to install handler!\n" << endl;
	}

	try
	{
		int credits = 0;
		std::string bet;
		bool betCorrectly = false;
		std::string revCommand = "";
		pair<int, string> choiceToSend;
		std::string choice = "";
		string messageData = "";
		int goodData = 0;

		//connect to the server 
		tcpclient = TCPClient("127.0.0.1", 80);
		tcpclient.Connect();
		int clientId = atoi((tcpclient.Recv()).c_str()); 


	   //we now want to constantly recieve from the server and evaluate in a switch statement 
		for(;;){
			char command = (tcpclient.Recv())[0];
 
			if(command == 'q'){
				break;
			}
			else {
				switch (command)
				{
				case 'b':
					bet = "";
					//protocol: if server sends 'b', we then know to recieve how much credits we have
					//then we send our bet if the credits allow for it. 
					credits = atoi((tcpclient.Recv()).c_str());
					cout << endl << "Please bet now: ";
					cin >> bet;	
					while(betCorrectly == false){
						goodData = checkForInt(bet);
						if(goodData != 0 && goodData <= credits){
							betCorrectly = true;
						}
						else if( goodData != 0 && goodData > credits) {
							cout << "You dont have enough money, bet again: ";
							bet = "";
							cin >> bet;
						}
						else{
							cout << "\nIncorrect bet, please bet again: ";
							bet = "";
							cin >> bet;
						}
						
					}//end while.

						tcpclient.Send("b");
						cout << "You Bet " << bet << " credits.\n" << endl; 
						tcpclient.Send(bet);
					break;
				case 't':   //if the server sends the client 't' the client then knows it is there turn 
					//to either hit, stand, double down, or split. They may only split if their cards allow it. 
					//we then send the server our choice.
					choice = tcpclient.Recv();
					ouputChoices(choice, credits, stoi(bet));
					choiceToSend = ProcessChoice();
					
					if(choiceToSend.second == "hit"){
						tcpclient.Send("h");
					}
					else if(choiceToSend.second == "stand"){
						tcpclient.Send("s");
					}
					else if(choiceToSend.second == "double down"){
						tcpclient.Send("d");
					}
					else if(choiceToSend.second == "split"){
						tcpclient.Send("p");
					}
					break;
				case 'm': //any time we recieve an 'm' from the server we know we are next recieving a message 
					//that we are to print to the screen. 
					messageData = tcpclient.Recv();
					cout << messageData << endl;
					break;
				}
			}
		}
	}
	catch (...) {
		//many things could go wrong during the process of all of these send and recives 
		//best to be safe with a catch all. 
		cout << "We are sorry something went wrong during the blackjack player creation process.." << endl;
	}

}
