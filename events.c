#pragma warning (disable: 4047)

#include "events.h"
#include "messages.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	//DebugMessage("Loaded image: %ls \n", FullImageName->Buffer);

	if (wcsstr(FullImageName->Buffer, L"\\AssaultCube\\bin_win32")) 
	{
		DebugMessage("Found Assault Cube \n");
		AssaultCubeBaseAddr = ImageInfo->ImageBase;

		DebugMessage("pid: %p \n", ProcessId);
	}
	return STATUS_SUCCESS;
}
