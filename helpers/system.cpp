#include "system.h"

wchar_t* System::getPath() {
	wchar_t buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return buffer;
}

std::string System::getUserName() {
	TCHAR buffer[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)buffer, &size);
	
	std::wstring wStr = buffer;
	std::string str = std::string(wStr.begin(), wStr.end());

	return str;
};

std::string System::getComputerName() {
	TCHAR buffer[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName(buffer, &size);

	std::wstring wStr = buffer;
	std::string str = std::string(wStr.begin(), wStr.end());

	return str;
};

std::string System::getTime() {
	time_t rawTime;
	struct tm timeInfo = {0};
	char buffer[80];

	time(&rawTime);
	localtime_s(&timeInfo,&rawTime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeInfo);
	std::string str(buffer);

	return str;
};