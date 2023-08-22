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

	if(console == INVALID_HANDLE_VALUE) {
		printf("Invalid handle value");
		return 1;
	}

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

	COORD consoleSize = { (short)consoleScreenWidth, (short)consoleScreenHeight };
	if (!SetConsoleScreenBufferSize(console, consoleSize)) {
		printf("Set console screen buffer size failed");
		return 1;
	}
	if(!SetConsoleActiveScreenBuffer(console)) {
		printf("Set active screen buffer failed");
		return 1;
	}

	if (!SetCurrentConsoleFontEx(console, false, &cfi)){
		printf("Set current console font ex failed");
		return 1;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(console, &csbi)) {
		printf("Get console screen info failed");
		return 1;
	}
	if (consoleScreenWidth > csbi.dwMaximumWindowSize.X || consoleScreenHeight > csbi.dwMaximumWindowSize.Y) {
		printf("Console size is too big");
		return 1;
	}

	windowRectangle = { 0, 0, (short)(consoleScreenWidth - 1), (short)(consoleScreenHeight - 1) };
	if(!SetConsoleWindowInfo(console, TRUE, &windowRectangle)) {
		printf("Reset console window info failed");
		return 1;
	}
	if(!SetConsoleMode(consoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT)) {
		printf("Set console mode failed");
		return 1;
	}

	consoleBuffer = new CHAR_INFO[consoleScreenWidth * consoleScreenHeight];
	memset(consoleBuffer, 0, sizeof(CHAR_INFO) * consoleScreenWidth * consoleScreenHeight);

	// Need to set console ctrl handler
	// SetConsoleCtrlHandler()
	return 0;
}