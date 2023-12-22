/*

Operations that are related to disks and their information

*/

#pragma once

#include <windows.h>
#include <memory>
#include <string>
#include <tuple>
#include <format>
#include <fstream>
#include <vector>


using namespace std;

class DiskInfo {
public:
    tuple<string,BOOLEAN,STORAGE_BUS_TYPE> getDriveInfo(const wchar_t* driveLetter);
    void getDrives();
private:
    vector <string> loggedDrives = {};
};