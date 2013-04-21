//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#include <TCPServer.hpp>


//name: shutdown 
//purpose: This function properly closes the sockets and shuts down the WSA information 
void TCPServer::shutdown() {
		closesocket( hListen );
		closesocket( hClient );
		WSACleanup();
	}


//name:ListenAndAccept 
//purpose: This function is not implemented but will listen and accept clients on a sperate thread 
void TCPServer::ListenAndAccept() {
		/*if( listen( hListen, 1 ) == SOCKET_ERROR ) {
			std::cerr << "Failed to listen" << std::endl;
			throw "Failed to Listen";
		}

		std::cout << "Waiting for a connection" << std::endl;
		SOCKET testSocket = SOCKET_ERROR;

		std::thread th(AcceptThread, hListen);
		th.join();	*/		
	}


//name:Listen 
//purpose: This function listens for clients to connect. 
void TCPServer::Listen() {
	if( listen( hListen, 1 ) == SOCKET_ERROR ) {
		std::cerr << "Failed to listen" << std::endl;
		throw "Failed to Listen";
	}
}


//name: Accept 
//purpose: This function accepts a client 
void TCPServer::Accept() {
	
	sockaddr_in _client;
	int iAddrSize = sizeof(_client);
	hClient = accept( hListen, (sockaddr *)&_client, &iAddrSize );
	if(hClient == INVALID_SOCKET) {
		std::cout << "accept() failed.." << std::endl;
	}
}


//name: init 
//purpose: this function sets up the intitial WSA info and socket information 
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
	}

	// Create the server address
	service.sin_family = family;
	service.sin_port = htons( port );
	service.sin_addr.s_addr = inet_addr( address.c_str() );

}


//name: Bind 
//purpose: This function nicely binds the hListen socket to the server 
void TCPServer::Bind() {
	if( bind( hListen, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
		std::cerr << "Failed to bind" << std::endl;
		int res = WSAGetLastError();
		std::cout << "Result: " << res << std::endl;
		throw "Failed to Bind Port";
	}
}


//name: Recv
//purpose This function receives data from the client 
std::string TCPServer::Recv() {
		int const MAX = 256;
		char buf[DEFAULT_BUFFER];
		int bytesRecv = recv( hClient, buf, MAX, 0 );
		std::cout << "Server Received" << bytesRecv << " bytes" << std::endl;
		std::cout << "Server Msg: " << buf << std::endl;

		return buf;
	}


//name: Send 
//purpose: This function sends data to the client. 
void TCPServer::Send(std::string msg) {
		int const MAX = 256;
		char buf[MAX];
		std::map<unsigned int, SOCKET>::iterator map_it;
		strcpy_s( buf, msg.c_str() );
		int bytesSent = send( hClient, buf, static_cast<int>(strlen( buf )) + 1, 0 );
		std::cout << "Server Sent: " << buf << " to all." << std::endl;
	}
