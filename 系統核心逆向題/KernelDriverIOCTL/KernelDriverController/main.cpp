#include <stdio.h>
#include <Windows.h>
#include "Communication.hpp"
#include <string>

int main(int argc, char* argv[]) {

	if (argc != 3) {
		printf("Arguments: Operand1 Operand2.");
		return 0;
	}

	HANDLE hDriver = CreateFileA("\\\\.\\KernelDriverIOCTLExample", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (hDriver == INVALID_HANDLE_VALUE) {
		printf("Not found the driver.\n");
		return 0;
	}

	DWORD Bytes;
	KERNEL_ADD_REQUEST Request;
	Request.Operand1 = std::stoi(argv[1]);
	Request.Operand2 = std::stoi(argv[2]);
	Request.Result = 0;

	if (DeviceIoControl(hDriver, IO_GET_ADD, &Request, sizeof(Request), &Request, sizeof(Request), &Bytes, NULL)){
		printf("Operand1 is %d, Operand2 is %d, the result is %d.", Request.Operand1, Request.Operand2, Request.Result);
	}
	return 0;

}