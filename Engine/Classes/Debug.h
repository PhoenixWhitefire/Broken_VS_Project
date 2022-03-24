#ifndef DEBUG
#define DEBUG

#define _WINSOCKAPI_ //have to define this so that the legacy winsock (aka version 1 'winsock.h') doesn't load
//for some reason, Windows.h automatically loads winsock.h, which causes errors because we're also including WinSock2.h

#include<Windows.h>
#include<WinSock2.h>
#include<WinUser.h>
#include<iostream>

#include"FileIO.h"

class Debug {
	public:
		static void Log(std::string Message);

		static int ShowPrompt(const char* Title, const char* Text, UINT Options, bool ExitOnOptionNoSelected);

		static void Close();

		static std::string ProgramLog;
};

#endif
