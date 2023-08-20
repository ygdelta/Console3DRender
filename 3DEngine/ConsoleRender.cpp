#include "ConsoleRender.h"
#include <Windows.h>
#include <thread>

ConsoleRender::ConsoleRender() {
	screenWidth = 1120;
	screenHeight = 930;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleIn = GetStdHandle(STD_INPUT_HANDLE);
	appName = L"Default";
}

bool ConsoleRender::OnUserDestroy() {
	return true;
}

int ConsoleRender::ConstructConsole(int width, int height, int fontWidth, int fontHeight) {
	screenWidth = width;
	screenHeight = height;

	// Set Console Info
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontWidth;
	cfi.dwFontSize.Y = fontHeight;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
}

void ConsoleRender::Start() {
	atomActive = true;
	// std::thread t = std::thread(&ConsoleRender::RenderThread, this);
}