#ifndef CLASS_NETWORKING
#define CLASS_NETWORKING

#define SOCKET_BUFFER_SIZE 1024

#include<tchar.h>
#include<WinSock2.h>
#include<string.h>
#include<string>
#include<ws2tcpip.h>

#include"Debug.h"

class Websocket {
	public:
		Websocket(int Port, std::string ServerIP, int ServerPort);

		bool Send(std::string Data);
		const char* Poll();

		SOCKADDR_IN ServerAddress;
		WSADATA WinsockData;

		SOCKET Socket;

		char Buffer[SOCKET_BUFFER_SIZE];
		char Message[SOCKET_BUFFER_SIZE];

		int Flags;

		SOCKADDR_IN ClientIn;
};

#endif
