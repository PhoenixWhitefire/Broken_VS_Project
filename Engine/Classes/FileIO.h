#ifndef FILE_IO
#define FILE_IO

#include<iostream>
#include<fstream>

#include"Debug.h"

class FileIO {
	public:
		static std::string ReadFile(const char* FilePath);

		static void WriteFile(const char* FilePath, std::string FileContents, bool InResourcesDirectory);
};

#endif

