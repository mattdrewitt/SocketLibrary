//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#include <UDPServer.hpp>
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")


//name:Accept 
//purpose: this function accepts clients and loops endlessly to recieve data from clients until they would like to quit.
void UDPServer::Accept() {
	// message loop
	for(;;) {
		std::string msg;
		Recv( msg );

		if( msg == "!quit" ) {
			Send("server exit");
			break;
		}

		msg[0] = toupper( msg[0] );
		std::cout << "Sending: " << msg << std::endl;
		Send( msg );

	}
}


//name:Recv
//purpose: this function recieves data from clients  
void UDPServer::Recv(std::string& m) {
	cbClientAddress = sizeof( clientAddress );
	int const MAXLINE = 256;
	char msg[MAXLINE];

	int n = recvfrom( hSocket, msg, MAXLINE, 0, &clientAddress, &cbClientAddress );
	msg[min(n,255)] = 0;
	std::cout << "Recv: " << msg << std::endl;
	m = msg;
}


//name:Send
//purpose: This function Sends data to clients based on the given string 
void UDPServer::Send(std::string const m) {
	cbClientAddress = sizeof( clientAddress );
	sendto( hSocket, m.c_str(), static_cast<int>(m.size()), 0, &clientAddress, cbClientAddress );
}


//name:shutdown
//purpose: this function closes the correct socket and cleans up WSA code. 
void UDPServer::shutdown() {
	closesocket( hSocket );
	WSACleanup();
}