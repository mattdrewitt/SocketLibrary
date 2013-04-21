//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#ifndef GUARD_UDPServer_hpp_
#define GUARD_UDPServer_hpp_

#if defined (_DEBUG) &&  !defined(_DLL)
#pragma comment (lib, "socketLibrary-mt-sgd.lib")
#elif !defined (_DEBUG) &&  !defined(_DLL)
#pragma comment (lib, "socketLibrary-mt-s.lib")
#elif defined (_DEBUG) &&  defined(_DLL)
#pragma comment (lib, "socketLibrary-mt-gd.lib")
#elif !defined (_DEBUG) &&  defined(_DLL)
#pragma comment (lib, "socketLibrary-mt.lib")
#endif

#include <iostream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

class UDPServer {
	// Server vars
	WSADATA wsaData;
	SOCKET hSocket;
	sockaddr_in service;

	// Server address config
	unsigned short const port;
	std::string const address;

	// Server recv/send vars
	sockaddr	clientAddress;
	socklen_t	cbClientAddress;

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
		std::cout << "UDP Server" << std::endl;
	}
	
	~UDPServer() {
		shutdown();
	}

	void Accept();

	void Recv(std::string& m);

	void Send(std::string const m);

	void shutdown();

};

#endif