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
#include <WinSock2.h>
#include <ostream>
#include<sstream>
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
	unsigned int Id;
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
	void init();
public:

	void Connect();

	void Recv();

	void Send(std::string msg);

	void shutdown();
};

#endif