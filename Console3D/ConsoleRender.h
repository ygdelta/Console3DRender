// Abstract class of render on console.
#pragma once
#include <string>
#include <Windows.h>
#include <atomic>

class ConsoleRender {
private:
	int consoleScreenWidth;
	int consoleScreenHeight;
	HANDLE console;
	HANDLE consoleIn;
	SMALL_RECT windowRectangle;
	CHAR_INFO* consoleBuffer;
	std::wstring appName;
public:
	ConsoleRender();
	//virtual bool OnUserCreate() = 0;
	//virtual bool OnUserUpdate(float elapsedTime) = 0;
	//virtual bool OnUserDestroy();
	int ConstructConsole(int width, int height, int fontWidth, int fontHeight);
	void Start();
};