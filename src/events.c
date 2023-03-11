#pragma warning (disable: 4047 4311)

#include "events.h"
#include "messages.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	UNREFERENCED_PARAMETER(ImageInfo);

	//DebugMessage("Loaded image: %ls \n", FullImageName->Buffer);

	if (wcsstr(FullImageName->Buffer, L"\\AssaultCube 1.3.0.2\\bin_win32\\ac_client.exe")) 
	{
		DebugMessage("Target found! \n");
		BaseAddr = ImageInfo->ImageBase;
		ProcessID = (ULONG)ProcessId;

		DebugMessage("pid: %u \n", ProcessID);
		DebugMessage("BaseAddr: %X \n", BaseAddr);

	}
	return STATUS_SUCCESS;
}
