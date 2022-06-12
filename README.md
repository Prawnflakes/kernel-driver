# Windows Kernel Driver to Read/Write Memory Regions
Windows kernel driver that can read and write memory regions of any process using an undocumented Windows function. 
The kernel driver can be communicated via IOCTL codes from the user space. The user space application can issue 
IOCTL commands to read or write to any memory region. Because the read and write operations are performed 
using the kernel level driver, the restrictions that an application may have in place for the user-space interactions can be bypassed.

## Abstract
This project provides an example that detects the launch of a specific base application by watching for its base image using the 
`ImageLoadCallback` and comparing a specific string with the image base name.

When the targeted proccess is launched the kernel driver will record it's base addrress and store it. Later, the user-space application 
can call the appropriate functions to receive this base address from the kernel driver. This base address is required to read or write 
a specific regions of the targeted applications memory. The kernel driver is installed as a new device by default.

## Project Structure
```
ROOT
│   .gitattributes
│   .gitignore
│   kernel-mode-lib.inf
│   kernel-mode-lib.sln
│   kernel-mode-lib.vcxproj
│   kernel-mode-lib.vcxproj.filters
│   kernel-mode-lib.vcxproj.user
│
├─── src
│       communication.c -- Allows communication with the user-space application using Win32 functions
│       communication.h -- Defines IOCTL codes for various functions
│       data.h          -- Defines various variables that hold data that might be queried by the user-space application
│       events.c        -- Uses the "ImageLoadCallback" to detect the start of the targeted process
│       events.h        -- Basic header file with function definitions
│       main.c          -- Defines the entry point for the driver, creates a device, and defines major functions for IO
│       main.h          -- Basic header file with function definitions
│       memory.c        -- Defines functions that read and write a given region of the memory from the kernel level.
│       memory.h        -- Declares the un-documented MmCopyVirtualMemory function that is used for memory read/write
│       messages.h      -- Define easy to write debug prints. Write whatever you want to the kernel logs
```

## How to start
Finding workable examples for Windows kernel driver development is much harder compared to Linux driver development. Luckily the 
documentation that Microsoft provides is easy to follow. A good place to start is the 
[Write a Hello World Windows Driver](https://docs.microsoft.com/en-us/windows-hardware/drivers/gettingstarted/writing-a-very-small-kmdf--driver)
guide of the Microsoft. 

After following that you would want to either use a VM or a whole another machine to debug your kernel driver. While it is possible to some 
extent to debug your drivers on your development machine it will limit your options severly since debugging a kernel driver is basically 
debugging the whole machine. I suggest you to use a whole seperate machine but in case it is not possible, you can also setup a VM and set it 
up for deployment. For setting up a Visual Studio project for remote deployment; follow 
[Provision a computer for driver deployment and testing](https://docs.microsoft.com/en-us/windows-hardware/drivers/gettingstarted/provision-a-target-computer-wdk-8-1)

## Disclaimer

The projcet currently implements the mostly needed functionalities but does no such thing to hide what it is doing. Just because you are on the kernel-level 
doesn't mean you can do anything to any process and no one will know. On the contrary most operations that you do are very much visible to other apps that have 
access to the kernel-level. While it is possible to hide your existence in the kernel-level by removing your entries from `PiDDBCacheTable` and `MmUnloadedDrivers` 
it is generally harder to hide the operations you do because there is no standard way of detecting such things therefore you would need to reverse engineer 
your enemy to find out what they are looking for and take actions to bypass these checks or fake the data that they are getting by hooking them etc.

This project is shared only to lend a helping hand to the starters as educational content. It can be taken as an example but should not be deployed 
in a real world envoirment.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change. 


## License

MIT
