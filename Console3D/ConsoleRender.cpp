#include "ConsoleRender.h"
#include <Windows.h>

ConsoleRender::ConsoleRender() {
	consoleScreenWidth = 1120;
	consoleScreenHeight = 930;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleIn = GetStdHandle(STD_INPUT_HANDLE);
	appName = L"Default";
}

int ConsoleRender::ConstructConsole(int width, int height, int fontWidth, int fontHeight) {

	consoleScreenWidth = width;
	consoleScreenHeight = height;

	// Set Console Info
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontWidth;
	cfi.dwFontSize.Y = fontHeight;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");

	windowRectangle = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(console, TRUE, &windowRectangle);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(console, &csbi)) {
		printf("Get console screen info failed");
		return 1;
	}
	if (consoleScreenWidth > csbi.dwMaximumWindowSize.X || consoleScreenHeight > csbi.dwMaximumWindowSize.Y) {
		printf("Console size is too big");
		return 1;
	}
}