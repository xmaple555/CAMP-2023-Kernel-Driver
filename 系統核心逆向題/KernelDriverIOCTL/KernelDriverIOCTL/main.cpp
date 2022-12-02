#include <ntifs.h>
#include "message.h"
#include "Communication.h"

UNICODE_STRING dev, dos;
PDEVICE_OBJECT pDeviceObject;

static void UnloadDriver(PDRIVER_OBJECT pDriverObject){

    UNREFERENCED_PARAMETER(pDriverObject);
    DebugMessage("[+] UnloadDriver\n");
	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);
}


extern "C" NTSTATUS  DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath) {
   
    UNREFERENCED_PARAMETER(pRegistryPath);
    pDriverObject->DriverUnload = UnloadDriver;

	RtlInitUnicodeString(&dev, L"\\Device\\KernelDriverIOCTLExample");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\KernelDriverIOCTLExample");

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

    DebugMessage("[+] DriverEntry\n");

    return STATUS_SUCCESS;
}