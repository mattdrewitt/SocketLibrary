#include <UDPServer.hpp>
#include <iostream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

void UDPServer::Accept() {
	// message loop
	for(;;) {
		/*int const MAXLINE = 256;
		char msg[MAXLINE];*/
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

void UDPServer::Recv(std::string& m) {
	cbClientAddress = sizeof( clientAddress );
	int const MAXLINE = 256;
	char msg[MAXLINE];

	int n = recvfrom( hSocket, msg, MAXLINE, 0, &clientAddress, &cbClientAddress );
	msg[min(n,255)] = 0;
	std::cout << "Recv: " << msg << std::endl;

	//set the passed param to the received value

	m = msg;
}

void UDPServer::Send(std::string const m) {
	cbClientAddress = sizeof( clientAddress );
	sendto( hSocket, m.c_str(), m.size(), 0, &clientAddress, cbClientAddress );
}


void UDPServer::shutdown() {
	closesocket( hSocket );
	WSACleanup();
}