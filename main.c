#pragma warning (disable: 4047 4024 6011)
#include "main.h"
#include "messages.h"
#include "events.h"
#include "data.h"
#include "communication.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);

	pDriverObject->DriverUnload = UnloadDriver;
	DebugMessage("TEST ENTERED DRIVER\n");

	PsSetLoadImageNotifyRoutine(ImageLoadCallback);

	RtlInitUnicodeString(&dev, L"\\Device\\kernelmodelib");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\kernelmodelib");

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;


	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);
	DebugMessage("TEST UNLOAD DRIVER\n");

	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);

	return STATUS_SUCCESS;
}
