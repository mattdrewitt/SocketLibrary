//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#include <TCPClient.hpp>

//name: init 
//purpose: this function initializes the WSA information, creates the socket and sets up its vital information 
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

		//std::cout << "TCP Client" << std::endl;
	}


//name: ConnectAndRecvId
//purpose: this function contains a connect that immediately expects to recieve an Id from the server 
void TCPClient::ConnectAndRecvId() {
		if( connect( hSocket, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
			std::cerr << "Failed to bind" << std::endl;
			throw "Failed to Connect";
		}
		else{
			char buf[DEFAULT_BUFFER];
			int bytesRecv = recv( hSocket, buf, DEFAULT_BUFFER, 0 );
			//std::cout << "Received ID" << buf << std::endl;
			Id = atoi(buf);
		}
	}
	
//name: Connect 
//purpose: this function connects the client to the server 
  void TCPClient::Connect() {
		if( connect( hSocket, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
			std::cerr << "Failed to connect" << std::endl;
			throw "Failed to Connect";
		}
	}

//name:Recv
//purpose: accepts the reieved data from the sever and returns it 
  std::string TCPClient::Recv() {
		unsigned int const MAX = 256;
		char buf[DEFAULT_BUFFER];
		int bytesRecv = recv( hSocket, buf, DEFAULT_BUFFER, 0 );
		return buf;
	}


 //name: Send 
//purpose: sends accepted data from the client to the server 
void TCPClient::Send(std::string msg) {
		unsigned int const MAX = 256;
		char buf[DEFAULT_BUFFER];
		strcpy_s( buf, msg.c_str() );
		int bytesSent = send( hSocket, buf, static_cast<int>(strlen(buf)) + 1, 0 );
	}


//name:shutdown 
//purpose:properly closes the socket and shuts down the WSA code 
void TCPClient::shutdown() {
		closesocket( hSocket );
		WSACleanup();
	}