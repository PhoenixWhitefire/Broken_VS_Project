#include"FileIO.h"

std::string FileIO::ReadFile(const char* FilePath) {
	std::cout << "Loading file " << FilePath << "\n";

	std::ifstream File(FilePath, std::ios::binary);

	if (File) {
		std::string Contents;
		File.seekg(0, std::ios::end);

		Contents.resize(File.tellg());
		File.seekg(0, std::ios::beg);

		File.read(&Contents[0], Contents.size());

		File.close();

		return Contents;
	}
	else {
		std::cout << "Could not load file: " << FilePath << "\n";

		Debug::Log("Could not load file: " + (std::string)FilePath);

		return "";
	}
}

void FileIO::WriteFile(const char* FilePath, std::string FileContents, bool InResourcesDirectory) {
	std::string Path = FilePath;

	printf(("Saving file to: " + Path + "\n").c_str());

	Debug::Log("Writing file: " + Path);

	std::ofstream File(Path.c_str());

	File << FileContents;

	File.close();
}
