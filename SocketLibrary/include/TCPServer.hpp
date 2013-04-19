#ifndef GUARD_TCPServer_hpp_
#define GUARD_TCPServer_hpp_

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
#include <map>
#include <thread>
#include <iterator>
#include <WinSock2.h>
#include <thread>
#include <future>
#include <string>
#include <vector>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#define DEFAULT_BUFFER 2048
#define DEFAULT_COUNT 20
#define DEFAULT_PORT  5150
#define DEFAULT_MESSAGE "broadcasting test"

class TCPServer {
private:
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
    static std::map<unsigned int, SOCKET> clients;
	DWORD dwThreadId;
	unsigned const int family;
	unsigned short const port;
	std::string const address;
	static unsigned int clientsConnected;
public:
	TCPServer() : family(AF_INET), address("172.0.0.1") , port(80){
		init();
	}

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
	void init();
public:
	void ListenAndAccept();
	void Send(std::string msg);
	void Accept();
	void Listen();
	void Recv();

private:
	static DWORD WINAPI AcceptThread(SOCKET sockListen);

	static DWORD WINAPI SendThread(SOCKET sockListen, std::string msg);

	static DWORD WINAPI ClientThread(LPVOID lpParam){
		//clients.push_back(clientCount++);
		SOCKET sock=(SOCKET)lpParam;
		//clients.push_back(sock);
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
			//std::cout << "clientid: " << clientCount << std::endl;
			szBuff[ret] = '\0';
			//echo the data back. 
			nLeft = ret; 
			idx = 0;
			if(strcmp(szBuff,"done") == 0){
				std::cout << "sending to you now..";
				break;
			}
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
		}
		return 0;
	}


	void shutdown();
};

#endif