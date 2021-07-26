#include "MainUpdate.h"

int main(void) {

	system("mode con: cols=83 lines=23");
	SetConsoleTitle(TEXT("WayStar"));
	srand((unsigned int)GetTickCount64());

	MainUpdate Main;

	Main.Initialize();

	while (true)
	{
		Main.Update();
		Main.Render();
	}

	return 0;
}