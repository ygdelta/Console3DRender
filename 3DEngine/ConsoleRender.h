// Abstract class of render on console.
#pragma once
#include <string>
#include <Windows.h>
#include <atomic>

class ConsoleRender {
private:
	int screenWidth;
	int screenHeight;
	HANDLE console;
	HANDLE consoleIn;
	std::wstring appName;
	
	static std::atomic<bool> atomActive;
public:
	ConsoleRender();
	virtual bool OnUserCreate() = 0;
	virtual bool OnUserUpdate(float elapsedTime) = 0;
	virtual bool OnUserDestroy();
	int ConstructConsole(int width, int height, int fontWidth, int fontHeight);
	void Start();
};