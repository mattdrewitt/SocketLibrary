#include <TCPServer.hpp>
#include <iostream>
#include <map>
#include <thread>
#include <iterator>
#include <WinSock2.h>
#include <thread>
#include <future>
//#include <vector>
//#include <WS2tcpip.h>

//std::vector<SOCKET> TCPServer::clients;
//
//void TCPServer::Listen() {
//		if( listen( hListen, 1 ) == SOCKET_ERROR ) {
//			std::cerr << "Failed to listen" << std::endl;
//			throw "Failed to Listen";
//		}
//
//		std::cout << "Waiting for a connection" << std::endl;
//		SOCKET testSocket = SOCKET_ERROR;
//
//		std::thread th(AcceptThread, hListen);
//		th.join();			
//	}

void TCPServer::init() {
	iPort = DEFAULT_PORT; //port on server to connect to 
	bSendOnly = FALSE;       //send data only dont receive 
	clientCount = 0;
	// initialize WSA
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData);
	if( iResult != 0 ) {
		std::cerr << "WSAStartup failed." << std::endl;
		throw "Failed to Initialize WSA";
	}
	// create the socket
	hListen = socket( family, SOCK_STREAM, IPPROTO_TCP );
	if( hListen == INVALID_SOCKET ) {
		std::cerr << "Error: socket(): " << WSAGetLastError() << std::endl;
		throw "Failed to Create Socket";
		//return EXIT_FAILURE;
	}

	// Create the server address
	service.sin_family = family;
	service.sin_port = htons( port );
	service.sin_addr.s_addr = inet_addr( address.c_str() );

	// bind the port to the IP.  Not exclusive, but says we want to listen to info on that port
	if( bind( hListen, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
		std::cerr << "Failed to bind" << std::endl;
		int res = WSAGetLastError();
		std::cout << "Result: " << res << std::endl;
		throw "Failed to Bind Port";
	}

	std::cout << "TCP Server" << std::endl;
}