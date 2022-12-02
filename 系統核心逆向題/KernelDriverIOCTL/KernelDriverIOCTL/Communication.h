#include"message.h"
#include <ntifs.h>

#define IO_GET_ADD CTL_CODE(FILE_DEVICE_UNKNOWN, 0x666, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp);


typedef struct _KERNEL_ADD_REQUEST
{
	int Operand1;
	int Operand2;
	int Result;

} KERNEL_ADD_REQUEST, * P_KERNEL_ADD_REQUEST;