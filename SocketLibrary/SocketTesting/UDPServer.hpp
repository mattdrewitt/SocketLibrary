#ifndef GUARD_UDPServer_hpp_
#define GUARD_UDPServer_hpp_

#include <iostream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

class UDPServer {
	WSADATA wsaData;
	SOCKET hSocket;
	sockaddr_in service;

	unsigned short const port;
	std::string const address;
public:
	UDPServer(std::string const a, unsigned short const p) : port(p), address(a) { 
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

		// bind the port to the IP.  Not exclusive, but says we want to listen to info on that port
		int res = bind( hSocket, (sockaddr*)&service, sizeof( sockaddr_in) );
		if( res == SOCKET_ERROR ) {
			std::cout << "Error on socket bind\n";
			res = WSAGetLastError();
			std::cout << "Result: " << res << std::endl;
			closesocket( hSocket );
			//return EXIT_FAILURE;
		}
	}
	~UDPServer() {
		shutdown();
	}

	void accept() {
		// message loop
		for(;;) {
			sockaddr	clientAddress;
			socklen_t	cbClientAddress = sizeof( clientAddress );
			int const MAXLINE = 256;
			char msg[MAXLINE];

			int n = recvfrom( hSocket, msg, MAXLINE, 0, &clientAddress, &cbClientAddress );
			msg[min(n,255)] = 0;

			std::cout << "Recv: " << msg << std::endl;
			if( !strcmp(msg, "!quit") ) {
				std::string const terminateMsg = "server exit";
				sendto( hSocket, terminateMsg.c_str(), terminateMsg.size(), 0, &clientAddress, cbClientAddress );
				break;
			}

			msg[0] = toupper( msg[0] );
			sendto( hSocket, msg, n, 0, &clientAddress, cbClientAddress );

		}
	}

	void shutdown() {
		closesocket( hSocket );
		WSACleanup();
	}
};

#endif