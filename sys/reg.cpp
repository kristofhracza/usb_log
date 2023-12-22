#include "reg.h"

wchar_t * RegistryHandler::getRegistryValue(const wchar_t* registry, const wchar_t* value) {
	wchar_t regData[MAX_PATH] = {0};
	DWORD regDataSize = sizeof(regData);
	
	RegGetValue(HKEY_CURRENT_USER, registry, value, RRF_RT_REG_SZ, nullptr, regData,&regDataSize);
	return regData;
};


void RegistryHandler::setRegistryValue(const wchar_t* registry,wstring value, const wchar_t* name) {
	HKEY regKey;

	LSTATUS s = RegOpenKeyEx(HKEY_CURRENT_USER, registry, 0, KEY_SET_VALUE, &regKey);
	RegSetValueEx(regKey,name, 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()), (DWORD)(value.size() + 1) * sizeof(wchar_t));
	RegCloseKey(regKey);
};