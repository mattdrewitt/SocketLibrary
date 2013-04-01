#ifndef GUARD_TCPClient_hpp_
#define GUARD_TCPClient_hpp_

#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

class TCPClient {
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKET hAccepted;
	sockaddr_in service;

	unsigned short const port;
	std::string const address;
public:
	TCPClient(std::string const a, unsigned short const p) : port(p), address(a) { 
		// initialize WSA
		int iResult = WSAStartup( MAKEWORD(2,2), &wsaData);
		if( iResult != 0 ) {
			std::cerr << "WSAStartup failed." << std::endl;
			//return EXIT_FAILURE;
		}

		// create the socket
		hSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( hSocket == INVALID_SOCKET ) {
			std::cerr << "Error: socket(): " << WSAGetLastError() << std::endl;
			//return EXIT_FAILURE;
		}

		// Create the server address
		service.sin_family = AF_INET;
		service.sin_port = htons( port );
		service.sin_addr.s_addr = inet_addr( address.c_str() );
		//int exitCode = EXIT_SUCCESS;

		// bind the port to the IP.  Not exclusive, but says we want to listen to info on that port
		if( bind( hSocket, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
			std::cerr << "Failed to bind" << std::endl;
			int res = WSAGetLastError();
			std::cout << "Result: " << res << std::endl;
			//exitCode = EXIT_FAILURE;
			//goto close;
		}

	}
	~TCPClient() {
		shutdown();
	}
	void Connect() {
		
	}

	void Recv() {
		int const MAX = 256;
		char buf[MAX];
		int bytesRecv = recv( hAccepted, buf, MAX, 0 );
		std::cout << "Received" << bytesRecv << " bytes" << std::endl;
		std::cout << "Msg: " << buf << std::endl;
	}
	void Send(std::string msg) {
		int const MAX = 256;
		char buf[MAX];
		strcpy( buf, msg.c_str() );
		int bytesSent = send( hAccepted, buf, strlen( buf ) + 1, 0 );
		std::cout << "Sent: " << bytesSent << " bytes" << std::endl;
	}

	void shutdown() {
		closesocket( hSocket );
		closesocket( hAccepted );
		WSACleanup();
	}
};

#endif