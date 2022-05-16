#pragma warning (disable: 4047 4024)
#include "main.h"
#include "messages.h"
#include "events.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);

	pDriverObject->DriverUnload = UnloadDriver;
	DebugMessage("TEST ENTERED DRIVER\n");

	PsSetLoadImageNotifyRoutine(ImageLoadCallback);

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);
	DebugMessage("TEST UNLOAD DRIVER\n");

	//PsRemoveImageNotifyRoutine(ImageLoadCallback);

	return STATUS_SUCCESS;
}
