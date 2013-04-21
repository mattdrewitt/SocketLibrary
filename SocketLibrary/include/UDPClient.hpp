//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#ifndef GUARD_UDPClient_hpp_
#define GUARD_UDPClient_hpp_

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

class UDPClient {
	WSADATA wsaData;
	SOCKET hSocket;
	sockaddr_in service;

	//Client connection configurations
	unsigned short const port;
	std::string const address;
public:
	UDPClient(std::string const a, unsigned short const p) : port(p), address(a) { 
		// initialize WSA
		int iResult = WSAStartup( MAKEWORD(2,2), &wsaData);
		if( iResult != 0 ) {
			std::cerr << "WSAStartup failed." << std::endl;
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

	void Connect();
	int Recv(std::string& r);
	void Send(std::string m);
	void shutdown();

};

#endif