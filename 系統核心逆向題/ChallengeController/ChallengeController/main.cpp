#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <sstream>


typedef struct WRITE {
	int Index;
	BYTE Source;
};
int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Arguments: Index Source");
		return 0;
	}


	HANDLE hDriver = CreateFileA("\\\\.\\T5Camp2022", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (hDriver == INVALID_HANDLE_VALUE) {
		printf("Failed to open the driver");
		return 0;
	}
	WRITE Request;
	Request.Index = std::stoi(argv[1]);
	Request.Source = std::stoi(argv[2]);

	DeviceIoControl(hDriver, 0x222090, &Request, sizeof(Request), 0, 0, 0, 0);



	return 0;
}