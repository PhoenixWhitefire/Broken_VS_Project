#include"Debug.h"

std::string Debug::ProgramLog = "";

//TODO: should probs move this somewhere else, literally nothing to do with debugging
int Debug::ShowPrompt(const char* Title, const char* Text, UINT Options, bool ExitOnOptionNoSelected) {
	const char* MessageTitle = "";

	if (Title != NULL) {
		MessageTitle = Title;
	}
	else {
		MessageTitle = "Debug";
	}

	int Response = MessageBoxA(
		0,
		Text,
		Title,
		Options
	);

	Debug::Log("[Debug::ShowPrompt]: Prompted user");

	if (Response == IDNO && ExitOnOptionNoSelected) {
		printf("Debug library forcibly closed program\n");

		Debug::Log("[Debug::ShowPrompt]: User selected 'No', function caller specified 'ExitOnOptionNoSelected' as true, exiting program");
		Debug::Close();

		exit(-1);
	}
	else {
		return Response;
	}
}

void Debug::Close() {
	Debug::Log("Application closing");

	FileIO::WriteFile("PROGRAMLOG.txt", Debug::ProgramLog, true);
}

void Debug::Log(std::string Message) {
	Debug::ProgramLog += Message + "\n";
}
