//Developers: Kayla Boyer and Matt Drewitt
//version: 1.0
//Date: April 21st 2012 

#ifndef GUARD_TCPClient_hpp_
#define GUARD_TCPClient_hpp_

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
#include <thread>
#include <map>
#include <string>
#include <WinSock2.h>
#include <ostream>
#include<sstream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#define DEFAULT_BUFFER 2048

//purpose: this class acts as a Facade for handling client side logic when dealing with tcp protocols. 
class TCPClient {
	WSADATA wsaData;
	SOCKET hSocket;
	sockaddr_in service;
	std::map<unsigned int, std::thread> clientThreads;
	unsigned int const family;
	unsigned short const port;
	std::string const address;
	unsigned int Id;
public:
	TCPClient() : family(AF_INET), address("127.0.0.1") , port(80) {
		init();
	}

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
	void init();
public:

	void ConnectAndRecvId();

	void Connect();

	std::string Recv();

	void Send(std::string msg);

	void shutdown();

	TCPClient& operator = (const TCPClient & rhs)
	{
		return *this; 
	}
};

#endif