//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#include <UDPClient.hpp>
#include <iostream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")


//name:Connect 
//purpose: This function continuously attempts to send and recieve to 
		// the server. it then displays messages to the console. 
void UDPClient::Connect() {
	// message loop
	std::string line;

	while( std::getline(std::cin,line) ) {
		sendto( hSocket, line.c_str(), static_cast<int>( line.size() ), 0, (sockaddr*)&service, sizeof(service) );

		// receive the reply
		std::string msg;

		int n = Recv( msg );
		if( n == -1 )
			std::cout << "no reply" << std::endl;
		else {
			msg[n] = 0;
			std::string const terminateMessage = "server exit";
			if( msg == terminateMessage ) {
				std::cout << "Server terminated" << std::endl;
				break;
			}
			std::cout << n << ": " << msg << std::endl;
		}
	}
}


//name: Recv
//purpose: to recieve data from the server 
//returns an integer that notifies us if we recieved successfully
int UDPClient::Recv(std::string& r) {
	int const MAXLINE = 256;
	char recvLine[MAXLINE + 1];
	int i = recvfrom( hSocket, recvLine, MAXLINE, 0, NULL, NULL );
	recvLine[min(i,255)] = 0;
	r = recvLine;

	return i;
}

//name:Connect 
//purpose: This function sends the given message to the server.  
void UDPClient::Send(std::string m) {
	sendto( hSocket, m.c_str(), static_cast<int>(m.size()), 0, (sockaddr*)&service, sizeof(service) );
}

//name: shutdown 
//purpose: This function appropriately closes the used socket and cleans up the WSA code. 
void UDPClient::shutdown() {
	closesocket( hSocket );
	WSACleanup();
}