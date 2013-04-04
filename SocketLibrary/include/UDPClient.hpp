#ifndef GUARD_UDPClient_hpp_
#define GUARD_UDPClient_hpp_

#include <iostream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

class UDPClient {
	// Client vars
	WSADATA wsaData;
	SOCKET hSocket;
	sockaddr_in service;

	//Client connection config
	unsigned short const port;
	std::string const address;
public:
	UDPClient(std::string const a, unsigned short const p) : port(p), address(a) { 
		// initialize WSA
		int iResult = WSAStartup( MAKEWORD(2,2), &wsaData);
		if( iResult != 0 ) {
			std::cerr << "WSAStartup failed." << std::endl;
			//return EXIT_FAILURE;
		}

		hSocket = socket( AF_INET, SOCK_DGRAM, 0 );

		// Create the server address
		service.sin_family = AF_INET;
		service.sin_port = htons( port );
		service.sin_addr.s_addr = inet_addr( address.c_str() );

		std::cout << "UDP Client" << std::endl;
	}
	~UDPClient() {
		shutdown();
	}

	void connect() {
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

	int Recv(std::string& r) {
		int const MAXLINE = 256;
		char recvLine[MAXLINE + 1];
		int i = recvfrom( hSocket, recvLine, MAXLINE, 0, NULL, NULL );
		recvLine[min(i,255)] = 0;
		r = recvLine;

		return i;
	}

	void Send(std::string m) {
		sendto( hSocket, m.c_str(), m.size(), 0, (sockaddr*)&service, sizeof(service) );
	}

	void shutdown() {
		closesocket( hSocket );
		WSACleanup();
	}
};

#endif