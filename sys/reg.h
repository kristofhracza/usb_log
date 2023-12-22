#pragma once

#define  WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>

using namespace std;

class RegistryHandler {
public:
	wchar_t * getRegistryValue(const wchar_t* registry, const wchar_t* value);
	void setRegistryValue(const wchar_t* registry, wstring value, const wchar_t* name);
};
