//implemented websockets wayyyy too early

//TODO: Implement, like, a Platform.h to make this engine compatible on Linux and Mac and stuff, currently uses WinSock2 which I believe only works on windows
#include"Networking.h"

WORD WinsockVersion = 0x202;

Websocket::Websocket(int ClientPort, std::string ServerIP, int ServerPort) {
	if (WSAStartup(WinsockVersion, &WinsockData)) {
		printf("WSAStartup failed: %d", WSAGetLastError());

		Debug::Log("[Networking::Websocket]: WSA startup failed: " + WSAGetLastError());

		Debug::Close();

		exit(-1);
	}

	std::string DebugLogMessage = "[Networking::Websocket]: Client connecting to websocket at client port " + std::to_string(ClientPort) + " to " + ServerIP + ":" + std::to_string(ServerPort) + "...";

	Debug::Log(DebugLogMessage);

	Websocket::ServerAddress.sin_family = AF_INET;
	Websocket::ServerAddress.sin_port = htons(ServerPort);

	//TODO: i hope _T("127.0.0.1") is the same as ((std::string)("127.0.0.1")).c_str()
	InetPtonA(AF_INET, ServerIP.c_str(), &Websocket::ServerAddress.sin_addr.S_un.S_addr);

	int Flags = 0;

	int AddressFamily = AF_INET;
	int SocketType = SOCK_DGRAM;
	int Protocol = IPPROTO_UDP;

	SOCKET WSAAPI socket( //why does windows make you do this...
		_In_ int af,
		_In_ int type,
		_In_ int protocol
	);

	Websocket::Socket = socket(AddressFamily, SocketType, Protocol);

	if (Websocket::Socket == INVALID_SOCKET) {
		printf("INVALID_SOCKET reponse from SocketAPI(), reason; %d\n", WSAGetLastError());

		Debug::Log("[Networking::Websocket]: Failed to create socket: " + WSAGetLastError());

		Debug::Close();

		exit(-1);
	}

	Websocket::ClientIn.sin_family = AF_INET;
	Websocket::ClientIn.sin_port = htons(ClientPort);
	Websocket::ClientIn.sin_addr.s_addr = INADDR_ANY;

	if (bind(Websocket::Socket, (SOCKADDR*)&ClientIn, sizeof(ClientIn)) == SOCKET_ERROR) {
		printf("SOCKET_ERROR response from bind(), reason; %d\n", WSAGetLastError());

		Debug::Log("[Networking::Websocket]: Failed to bind websocket: " + WSAGetLastError());

		Debug::Close();

		exit(-1);
	}

	Buffer[SOCKET_BUFFER_SIZE - 1] = { 0 };
	Message[SOCKET_BUFFER_SIZE - 1] = { 0 };

	Websocket::Flags = 0;

	Debug::Log("[Networking::Websocket]: Successfully connected to websocket!");
}

bool Websocket::Send(std::string Data) {
	strcpy_s(Message, Data.size() + 1, Data.c_str());

	int Response = sendto(
		Websocket::Socket,
		Message,
		strlen(Websocket::Message),
		0,
		(SOCKADDR*)&ServerAddress,
		sizeof(ServerAddress)
	);

	if (Response == SOCKET_ERROR) {
		printf("SOCKET_ERROR response from sendto(), reason; %d\n", WSAGetLastError());

		Debug::Log("[Networking::Websocket::Send]: Failed to send data over websocket: " + WSAGetLastError());

		return false;
	}

	return true;
}

const char* Websocket::Poll() {
	int SockSize = sizeof(Websocket::ClientIn);

	int BytesRecieved = recvfrom(Websocket::Socket, Buffer, SOCKET_BUFFER_SIZE, Websocket::Flags, (SOCKADDR*)&ClientIn, &SockSize);

	if (BytesRecieved == SOCKET_ERROR) {
		std::cout << "SOCK ERR: " << WSAGetLastError() << "\n";

		Debug::Log("[Networking::Websocket::Poll]: recvfrom returned SOCKET_ERROR, WSA error enum ID: " + std::to_string(WSAGetLastError()));

		//TODO: figure out if ít's a good idea to make this thing pop up...
		//Debug::ShowPrompt(
		//	"Engine/Networking/Websocket error",
		//	"An error occured while getting data from a websocket. Continue running program?",
		//	MB_ICONERROR | MB_YESNO | MB_DEFBUTTON2,
		//	true
		//);

		std::string StringErrorCode = (std::string)"E" + std::to_string(WSAGetLastError());

		const char* Error;

		Error = StringErrorCode.c_str();

		std::cout << "yes " << Error << " yaas\n"; //TODO: fix fecking null terminator missing

		return Error;
	}

	if (BytesRecieved < SOCKET_BUFFER_SIZE) {
		Buffer[BytesRecieved] = 0;

		auto FromIPAddress = ClientIn.sin_addr.S_un.S_un_b;

		std::string IPString = FromIPAddress.s_b1 + "." +
			FromIPAddress.s_b2 + (char)"." +
			(int)FromIPAddress.s_b3 + (char)"." +
			FromIPAddress.s_b4 + (char)":" +
			ClientIn.sin_port;

		return Buffer;
	}
	else {
		printf("Socket buffer overflow!");

		Debug::Log("[Networking::Websocket::Poll]: Server websocket response buffer overflow!");
	}

	return NULL;
}
