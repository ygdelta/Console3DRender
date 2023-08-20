#include <iostream>
#include "ConsoleRender.h"
using namespace std;

class Demo : public ConsoleRender {
private:
public:
	Demo() {}

	virtual bool OnUserCreate() {
		return true;
	}

	virtual bool OnUserUpdate(float elapsedTime) {
		return true;
	}
};

int main() {
	Demo renderTest;
	renderTest.ConstructConsole(160, 100, 8, 8);
	renderTest.Start();
}