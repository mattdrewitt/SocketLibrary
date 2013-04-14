#ifndef GUARD_TCPServer_hpp_
#define GUARD_TCPServer_hpp_

#include <iostream>
#include <map>
#include <thread>
#include <iterator>
#include <WinSock2.h>
#include <thread>
#include <future>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#define DEFAULT_BUFFER 2048
#define DEFAULT_COUNT 20
#define DEFAULT_PORT  5150
#define DEFAULT_MESSAGE "broadcasting test"

class TCPServer {
	WSADATA wsaData;
	SOCKET hListen;
	SOCKET hClient;
	HANDLE hThread;
	int iAddrSize;
	unsigned int clientCount;
	sockaddr_in service;
	sockaddr_in client;
	char szServer[128],
		 szMessage[1024];
	int iPort; //= DEFAULT_PORT;
	DWORD dwCount; //= DEFAULT_COUNT;
	BOOL bSendOnly; //= FALSE;

	DWORD dwThreadId;
	std::map<unsigned int, SOCKET> clientSockets;
	unsigned const int family;
	unsigned short const port;
	std::string const address;
public:
	TCPServer(std::string const a, unsigned short const p) : family(AF_INET), address(a) , port(p) {
		init();
	}

	TCPServer(int const f, std::string const a, unsigned short const p) : family(f), address(a) , port(p) {
		init();
	}
	~TCPServer() {
		shutdown();
	}
private:
	void init() { 
		iPort = DEFAULT_PORT; //port on server to connect to 
		bSendOnly = FALSE;       //send data only dont receive 
		clientCount = 0;
		// initialize WSA
		int iResult = WSAStartup( MAKEWORD(2,2), &wsaData);
		if( iResult != 0 ) {
			std::cerr << "WSAStartup failed." << std::endl;
			throw "Failed to Initialize WSA";
			//return EXIT_FAILURE;
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
		//int exitCode = EXIT_SUCCESS;

		// bind the port to the IP.  Not exclusive, but says we want to listen to info on that port
		if( bind( hListen, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
			std::cerr << "Failed to bind" << std::endl;
			int res = WSAGetLastError();
			std::cout << "Result: " << res << std::endl;
			throw "Failed to Bind Port";
			//exitCode = EXIT_FAILURE;
			//goto close;
		}

		std::cout << "TCP Server" << std::endl;
	}
public:
	void Listen() {
		if( listen( hListen, 1 ) == SOCKET_ERROR ) {
			std::cerr << "Failed to listen" << std::endl;
			throw "Failed to Listen";
		}
	}

	static DWORD WINAPI ClientThread(LPVOID lpParam){
		SOCKET sock=(SOCKET)lpParam;
		char szBuff[DEFAULT_BUFFER];
		int		ret,
			    nLeft,
				idx;
		while(1){
			//perform a blocking revc() call....
			ret = recv(sock, szBuff, DEFAULT_BUFFER, 0);
			if(ret == 0){
				break;
			}
			else if(ret == SOCKET_ERROR){
				std::cout << "recv() failed" << std::endl;
				break;
			}
			std::cout << "bytes recv " << ret << std::endl;
			std::cout << "recv: " << szBuff << std::endl;
			szBuff[ret] = '\0';
			//echo the data back. 
			nLeft = ret; 
			idx = 0;
			while(nLeft > 0){
				ret = send(sock, &szBuff[idx], nLeft,0);
				if(ret == 0){
					break;
				}
				else if (ret == SOCKET_ERROR){
					std::cout << "Send Failed....tried to send back " << ret << std::endl;
					break;
				}
				nLeft -= ret;
				idx += ret;
			}

		   
			/*else
			{
				std::cout << "not sure whats going on...." << std::endl;
				break;
			}*/
		}
		return 0;
	}



	 void Accept() {
		
		std::cout << "Waiting for a connection" << std::endl;
		hClient = SOCKET_ERROR;
		//in a continuous loop we wait for incoming clients. 
		//once one is detected create a thread and padd the handle off to 
		//it 
		while(1){
			iAddrSize = sizeof(client);
			hClient = accept( hListen, (sockaddr *)&client, &iAddrSize );

			if(hClient == INVALID_SOCKET) {
				std::cout << "accept() failed.." << std::endl;
				break;

			}
			hThread = CreateThread(NULL,0, ClientThread,
				(LPVOID)hClient, 0, &dwThreadId);

		    std::cout << "Client connected" << std::endl;
			if(hThread == NULL){
				std::cout << "CreateThread() failed...." << std::endl;
				break;
			}
	
			CloseHandle(hThread);
			
		}
		closesocket(hListen);
	}

	//void Recv() {
	//	//std::map<unsigned int, SOCKET>::iterator it;
	//	//for(it = clientSockets.begin(); it != clientSockets.end(); it++){
	//		//if(it->first = clientId) 
	//		//{
	//	/*		char buf[DEFAULT_BUFFER];
	//			int bytesRecv = recv( hClient, buf, MAX, 0 );
	//			std::cout << "Received" << bytesRecv << " bytes" << std::endl;
	//			std::cout << "Msg: " << buf << std::endl;*/
	//			//break;
	//	//	}
	//	//}
	//}
	//void Send(std::string msg) {
	//	int const MAX = 256;
	//	char buf[MAX];
	//	strcpy_s( buf, msg.c_str() );
	//	int bytesSent = send( hClient, buf, strlen( buf ) + 1, 0 );
	//	std::cout << "Sent: " << bytesSent << " bytes" << std::endl;
	//}

	void closeCurrentConnection() {

	}

	void shutdown() {
		closesocket( hListen );
		closesocket( hClient );
		WSACleanup();
	}
};

#endif