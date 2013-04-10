#ifndef GUARD_TCPClient_hpp_
#define GUARD_TCPClient_hpp_

#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

class TCPClient {
	WSADATA wsaData;
	SOCKET hSocket;
	sockaddr_in service;

	unsigned short const port;
	std::string const address;
public:
	TCPClient(std::string const a, unsigned short const p) : port(p), address(a) { 
		// initialize WSA
		int iResult = WSAStartup( MAKEWORD(2,2), &wsaData);
		if( iResult != 0 ) {
			std::cerr << "WSAStartup failed." << std::endl;
			throw "Failed to Initialize WSA";
			//return EXIT_FAILURE;
		}

		// create the socket
		hSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( hSocket == INVALID_SOCKET ) {
			std::cerr << "Error: socket(): " << WSAGetLastError() << std::endl;
			throw "Failed to Create Socket";
			//return EXIT_FAILURE;
		}

		// Create the server address
		service.sin_family = AF_INET;
		service.sin_port = htons( port );
		service.sin_addr.s_addr = inet_addr( address.c_str() );
		//int exitCode = EXIT_SUCCESS;

		std::cout << "TCP Client" << std::endl;
	}
	~TCPClient() {
		shutdown();
	}
	void Connect() {
		if( connect( hSocket, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
			std::cerr << "Failed to bind" << std::endl;
			throw "Failed to Connect";
			//exitCode = EXIT_FAILURE;
			//goto close;
		}
		std::cout << "Client connected" << std::endl;
	}
	
	void Recv() {
		unsigned int const MAX = 256;
		char buf[MAX];
		int bytesRecv = recv( hSocket, buf, MAX, 0 );
		std::cout << "Received" << bytesRecv << " bytes" << std::endl;
		std::cout << "Msg: " << buf << std::endl;
	}
	void Send(std::string msg) {
		unsigned int const MAX = 256;
		char buf[MAX];
		strcpy( buf, msg.c_str() );
		int bytesSent = send( hSocket, buf, strlen( buf ) + 1, 0 );
		std::cout << "Sent: " << bytesSent << " bytes" << std::endl;
	}

	void shutdown() {
		closesocket( hSocket );
		WSACleanup();
	}
};

#endif