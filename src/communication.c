#include "communication.h"
#include "messages.h"
#include "data.h"


NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    
    DebugMessage("Created Call \n");

    return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    
    DebugMessage("Closed Call \n");

    return STATUS_SUCCESS;
}

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    NTSTATUS Status = STATUS_UNSUCCESSFUL;
    ULONG ByteIO = 0;

    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

    ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;

    if (ControlCode == IO_GET_CLIENT_ADDRESS)
    {
        PULONG Output = (PULONG)Irp->AssociatedIrp.SystemBuffer;
        *Output = BaseAddr;

        DebugMessage("Client base addr requested \n");

        Status = STATUS_SUCCESS;
        ByteIO = sizeof(*Output);
    }

    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = ByteIO;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return Status;
}
