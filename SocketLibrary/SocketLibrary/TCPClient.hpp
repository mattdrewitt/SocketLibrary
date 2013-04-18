#ifndef GUARD_TCPClient_hpp_
#define GUARD_TCPClient_hpp_

#include <iostream>
#include <thread>
#include <map>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#define DEFAULT_BUFFER 2048
class TCPClient {
	WSADATA wsaData;
	SOCKET hSocket;
	sockaddr_in service;
	std::map<unsigned int, std::thread> clientThreads;
	unsigned int const family;
	unsigned short const port;
	std::string const address;
public:
	TCPClient(std::string const a, unsigned short const p) : family(AF_INET), address(a) , port(p) {
		init();
	}

	TCPClient(int const f, std::string const a, unsigned short const p) : family(f), address(a) , port(p) {
		init();
	}
	~TCPClient() {
		shutdown();
	}
private:
	void init() { 
		// initialize WSA
		int iResult = WSAStartup( MAKEWORD(2,2), &wsaData);
		if( iResult != 0 ) {
			std::cerr << "WSAStartup failed." << std::endl;
			throw "Failed to Initialize WSA";
			//return EXIT_FAILURE;
		}

		// create the socket
		hSocket = socket( family, SOCK_STREAM, IPPROTO_TCP );
		if( hSocket == INVALID_SOCKET ) {
			std::cerr << "Error: socket(): " << WSAGetLastError() << std::endl;
			throw "Failed to Create Socket";
			//return EXIT_FAILURE;
		}

		// Create the server address
		service.sin_family = family;
		service.sin_port = htons( port );
		service.sin_addr.s_addr = inet_addr( address.c_str() );
		//int exitCode = EXIT_SUCCESS;

		std::cout << "TCP Client" << std::endl;
	}
public:

	 void Connect() {
		if( connect( hSocket, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
			std::cerr << "Failed to bind" << std::endl;
			throw "Failed to Connect";
		}
	}
	
	void Recv() {
		unsigned int const MAX = 256;
		char buf[DEFAULT_BUFFER];
		int bytesRecv = recv( hSocket, buf, DEFAULT_BUFFER, 0 );
		std::cout << "Received" << bytesRecv << " bytes" << std::endl;
		std::cout << "Msg: " << buf << std::endl;
	}
	void Send(std::string msg) {
		unsigned int const MAX = 256;
		char buf[DEFAULT_BUFFER];
		strcpy_s( buf, msg.c_str() );
		int bytesSent = send( hSocket, buf, strlen( buf ) + 1, 0 );
		std::cout << "Sent: " << bytesSent << " bytes" << std::endl;
	}

	void shutdown() {
		closesocket( hSocket );
		WSACleanup();
	}
};

#endif