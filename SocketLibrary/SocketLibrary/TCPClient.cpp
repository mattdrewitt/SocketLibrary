#include <TCPClient.hpp>


void TCPClient::init() { 
		
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


	 void TCPClient::Connect() {
		if( connect( hSocket, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
			std::cerr << "Failed to bind" << std::endl;
			throw "Failed to Connect";
		}
		else{
			char buf[DEFAULT_BUFFER];
			int bytesRecv = recv( hSocket, buf, DEFAULT_BUFFER, 0 );
			std::cout << "Received ID" << buf << std::endl;
			Id = atoi(buf);
		}
	}
	
	void TCPClient::Recv() {
		unsigned int const MAX = 256;
		char buf[DEFAULT_BUFFER];
		int bytesRecv = recv( hSocket, buf, DEFAULT_BUFFER, 0 );
		std::cout << "Received" << bytesRecv << " bytes" << std::endl;
		std::cout << "Msg: " << buf << std::endl;
	}
	void TCPClient::Send(std::string msg) {
		unsigned int const MAX = 256;
		char buf[DEFAULT_BUFFER];
		strcpy_s( buf, msg.c_str() );
		int bytesSent = send( hSocket, buf, strlen( buf ) + 1, 0 );
		std::cout << "Sent: " << bytesSent << " bytes" << std::endl;
	}

	void TCPClient::shutdown() {
		closesocket( hSocket );
		WSACleanup();
	}