#include "Communication.h"


NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp){

	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("[+] CreateCall was called, connection enstablished!\n");

	return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp){

	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("[+] Connection Terminated!\n");

	return STATUS_SUCCESS;
}



NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp){
	UNREFERENCED_PARAMETER(DeviceObject);
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	ULONG ByteIO = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	if (ControlCode == IO_GET_ADD){

		P_KERNEL_ADD_REQUEST ADDInput = (P_KERNEL_ADD_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		ADDInput->Result = ADDInput->Operand1 + ADDInput->Operand2;
			DebugMessage("[+] Operand1 is %d, Operand2 is %d, the result is %d", ADDInput->Operand1, ADDInput->Operand2, ADDInput->Result);
		Status = STATUS_SUCCESS;
		ByteIO = sizeof(KERNEL_ADD_REQUEST);

	}else{
		ByteIO = 0;
	}

	Irp->IoStatus.Status = Status;
	Irp->IoStatus.Information = ByteIO;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return Status;
}

