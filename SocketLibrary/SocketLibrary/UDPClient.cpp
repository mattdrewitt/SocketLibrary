#include <UDPClient.hpp>
#include <iostream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

void UDPClient::Connect() {
	// message loop
	std::string line;

	while( std::getline(std::cin,line) ) {
		sendto( hSocket, line.c_str(), line.size(), 0, (sockaddr*)&service, sizeof(service) );

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

int UDPClient::Recv(std::string& r) {
	int const MAXLINE = 256;
	char recvLine[MAXLINE + 1];
	int i = recvfrom( hSocket, recvLine, MAXLINE, 0, NULL, NULL );
	recvLine[min(i,255)] = 0;
	r = recvLine;

	return i;
}

void UDPClient::Send(std::string m) {
	sendto( hSocket, m.c_str(), m.size(), 0, (sockaddr*)&service, sizeof(service) );
}

void UDPClient::shutdown() {
	closesocket( hSocket );
	WSACleanup();
}