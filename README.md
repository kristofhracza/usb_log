# USB logging
Finds all USB devices and makes a log of them.

## Intended use case
The main purpose of this program is to log all known drives.       
This can be done by plugging all of the USB devices into the PC and store their ID in a log file.       
Later, if a USB drive is inserted and is not in the logs, it should be blacklisted.


## How it works
It looks at all drives on the PC, if a drive is identified as a USB, the program will get its information *(that information can be used anywhere later)*.        
During the program's runtime each device's serial number is stored in an array, hence it won't be logged twice.

### Information stored
By default, the program will get the device's **serial number**, **media type** and **bus type**.       

For this, the program uses `STORAGE_DEVICE_DESCRIPTOR`:        
[https://learn.microsoft.com/en-us/windows/win32/api/winioctl/ns-winioctl-storage_device_descriptor](https://learn.microsoft.com/en-us/windows/win32/api/winioctl/ns-winioctl-storage_device_descriptor)
```cpp
    STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(pOutBuffer.get());
```

 From the above descriptor, the following data are taken:
 ```cpp
    const DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;
    const char* serialNumber = reinterpret_cast<const char*>(pOutBuffer.get() + dwSerialNumberOffset);
    const BOOLEAN boRemovableMedia = pDeviceDescriptor->RemovableMedia;
    const STORAGE_BUS_TYPE  busType = pDeviceDescriptor->BusType
```

### On boot
The program adds an entry named `Pendrive` to `SOFTWARE\Microsoft\Windows\CurrentVersion\Run`  registry so, that on start-up the program will run automatically.

### Background process
The program's window is hidden, therefore acts like a background process.