#pragma warning (disable : 4267 )
#pragma warning (disable : 4244 )

#pragma once

#define  WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <filesystem>
#include <string>
#include <chrono>
#include <Lmcons.h>

class System {
public:
	static wchar_t* getPath();
	std::string getUserName();
	std::string getComputerName();
	std::string getTime();
};