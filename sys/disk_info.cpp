#pragma warning (disable : 4996 )

#include "disk_info.h"

/*

Get info of a specified drive

*/
tuple<string,BOOLEAN, STORAGE_BUS_TYPE> DiskInfo::getDriveInfo(const wchar_t * driveLetter) {
    // Input and output options
    STORAGE_PROPERTY_QUERY storagePropertyQuery{};
    storagePropertyQuery.PropertyId = StorageDeviceProperty;
    storagePropertyQuery.QueryType = PropertyStandardQuery;
    STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader{};

    //Handle physical drive
    HANDLE fileHandle = CreateFileW(driveLetter, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    std::unique_ptr<std::remove_pointer<HANDLE>::type, void(*)(HANDLE)> hDevice{fileHandle, [](HANDLE handle) {CloseHandle(handle); }};
    
    // Buffer operations
    DWORD dwBytesReturned = 0;
    DeviceIoControl(hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY), &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER), &dwBytesReturned, NULL);
    const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
    std::unique_ptr<BYTE[]> pOutBuffer{new BYTE[dwOutBufferSize]{}};

    // Get data
    DeviceIoControl(hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY), pOutBuffer.get(), dwOutBufferSize, &dwBytesReturned, NULL);

    // Output handling
    STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(pOutBuffer.get());
    //// Data needed
    const DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;
    const char* serialNumber = reinterpret_cast<const char*>(pOutBuffer.get() + dwSerialNumberOffset);
    const BOOLEAN boRemovableMedia = pDeviceDescriptor->RemovableMedia;
    const STORAGE_BUS_TYPE  busType = pDeviceDescriptor->BusType;

    return {serialNumber,boRemovableMedia,busType};
}

/*
* 
List all the drives and does main iteration

*/
void DiskInfo::getDrives() {
    
    wchar_t driveStrings[MAX_PATH] = { 0 };
    DWORD drives = ::GetLogicalDriveStrings(MAX_PATH, driveStrings);

    for (int i = 0; i < 26; i++){
        std::wstring wbuffer;
        format_to(std::back_inserter(wbuffer), L"\\\\.\\{}:", driveStrings[i]);
        if (isalpha(driveStrings[i])) {
            auto [dwSerialNumberOffset, boRemovableMedia, busType] = getDriveInfo(wbuffer.c_str());
            if (boRemovableMedia && busType == 7) {
                if (find(DiskInfo::loggedDrives.begin(), DiskInfo::loggedDrives.end(), dwSerialNumberOffset) == DiskInfo::loggedDrives.end()) {
                    DiskInfo::loggedDrives.push_back(dwSerialNumberOffset);
                }
            }

        }
    }
}