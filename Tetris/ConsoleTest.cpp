#include <iostream>
#include <Windows.h>

int main() {

	std::cout << "This is just a test, do not scare" << std::endl;

	_SMALL_RECT readRect;
	_SMALL_RECT writeRect;
	COORD bufferCoordinate;
	COORD bufferSize; // col-row size of buffer
	CHAR_INFO charBuffer[180]; // Define as [90]*[2]
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE screenBuffer = CreateConsoleScreenBuffer(
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);

	if (outputHandle == INVALID_HANDLE_VALUE || screenBuffer == INVALID_HANDLE_VALUE) {
		printf("Create console screen buffer failed - %d\n", GetLastError());
		return 1;
	}

	if (!SetConsoleActiveScreenBuffer(screenBuffer)) {
		printf("Set console active screen buffer failed - %d\n", GetLastError());
		return 1;
	}

	// Set source read rectangle
	readRect.Top = 0;
	readRect.Left = 0;
	readRect.Right = 89;
	readRect.Bottom = 1;

	bufferCoordinate.X = 0;
	bufferCoordinate.Y = 0;

	bufferSize.X = 90;
	bufferSize.Y = 2;

	bool isReadSuccess = ReadConsoleOutput(outputHandle, charBuffer, bufferSize, bufferCoordinate, &readRect);
	if (!isReadSuccess) {
		printf("Read console output failed - %d", GetLastError());
		return 1;
	}

	// Set source write rectangle
	writeRect.Top = 10;    // top lt: row 10, col 0
	writeRect.Left = 0;
	writeRect.Bottom = 11; // bot. rt: row 11, col 79
	writeRect.Right = 79;

	bool isWriteSuccess = WriteConsoleOutput(screenBuffer, charBuffer, bufferSize, bufferCoordinate, &writeRect);
	if(!isWriteSuccess) {
		printf("Write console output fail - %d", GetLastError());
		return 1;
	}
	Sleep(10000);
	return 0;
}