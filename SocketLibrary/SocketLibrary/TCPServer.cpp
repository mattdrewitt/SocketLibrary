#include <TCPServer.hpp>

//std::map<unsigned int, SOCKET> TCPServer::clients;
//unsigned int TCPServer::clientsConnected = 0;
//
//DWORD WINAPI TCPServer::AcceptThread(SOCKET sockListen){
//	SOCKET sock;
//	char szBuff[DEFAULT_BUFFER];
//	while(1){
//		sockaddr_in _client;
//		int iAddrSize = sizeof(_client);
//		sock = accept( sockListen, (sockaddr *)&_client, &iAddrSize );
//		if(sock == INVALID_SOCKET) {
//			std::cout << "accept() failed.." << std::endl;
//			return 0;
//		}
//
//		clientsConnected++;
//		clients.insert(std::pair<unsigned int, SOCKET>(clientsConnected, sock));
//		std::cout << "client" << clientsConnected << " is now connected" << std::endl;
//		int const MAX = 256;
//		char buf[MAX];
//		std::string clientId = std::to_string(clientsConnected);
//		strcpy_s( buf, clientId.c_str() );
//		int bytesSent = send( sock, buf, strlen( buf ) + 1, 0 );
//		std::cout << "Server: Sent Id." << std::endl;
//	}
//	return 0;	
//}

   
void TCPServer::shutdown() {
		closesocket( hListen );
		closesocket( hClient );
		WSACleanup();
	}

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

void TCPServer::Listen() {
	if( listen( hListen, 1 ) == SOCKET_ERROR ) {
		std::cerr << "Failed to listen" << std::endl;
		throw "Failed to Listen";
	}

	std::cout << "Waiting for a connection" << std::endl;		
}

void TCPServer::Accept() {
	char szBuff[DEFAULT_BUFFER];
	sockaddr_in _client;
	int iAddrSize = sizeof(_client);
	hClient = accept( hListen, (sockaddr *)&_client, &iAddrSize );
	if(hClient == INVALID_SOCKET) {
		std::cout << "accept() failed.." << std::endl;
	}
}

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
	std::cout << "TCP Server" << std::endl;
}


void TCPServer::Bind() {
	
	if( bind( hListen, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
		std::cerr << "Failed to bind" << std::endl;
		int res = WSAGetLastError();
		std::cout << "Result: " << res << std::endl;
		throw "Failed to Bind Port";
	}
	else {
		std::cout << "Successful Bind." << std::endl;
	}
}


	std::string TCPServer::Recv() {
		int const MAX = 256;
		char buf[DEFAULT_BUFFER];
		int bytesRecv = recv( hClient, buf, MAX, 0 );
		//std::cout << "Server Received" << bytesRecv << " bytes" << std::endl;
		std::cout << "Server Msg: " << buf << std::endl;

		return buf;
	}

	void TCPServer::Send(std::string msg) {
		int const MAX = 256;
		char buf[MAX];
		std::map<unsigned int, SOCKET>::iterator map_it;
		strcpy_s( buf, msg.c_str() );
		int bytesSent = send( hClient, buf, strlen( buf ) + 1, 0 );
		std::cout << "Server Sent: " << buf << " to all." << std::endl;
	}
