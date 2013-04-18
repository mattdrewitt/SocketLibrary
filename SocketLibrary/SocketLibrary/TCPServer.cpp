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

//#if defined (_DEBUG) &&  !defined(_DLL)
//#pragma comment (lib, "socketLibrary-mt-sgd.lib")
//#elif !defined (_DEBUG) &&  !defined(_DLL)
//#pragma comment (lib, "socketLibrary-mt-s.lib")
//#elif defined (_DEBUG) &&  defined(_DLL)
//#pragma comment (lib, "socketLibrary-mt-gd.lib")
//#elif !defined (_DEBUG) &&  defined(_DLL)
//#pragma comment (lib, "socketLibrary-mt.lib")
//#endif


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