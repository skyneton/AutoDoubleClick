#include "InputManager.h"
#include "Windows.h"
#include "stdio.h"

void printfScreen();
void init();

int main() {
	init();
	printfScreen();

	bool macro = false;
	while (1) {
		InputManager::UpdateKeyState();

		if (InputManager::GetKeyState(VK_F8)) break;
		if (InputManager::GetKeyState(VK_F9) && macro) { macro = false; printfScreen(); printf("매크로가 정지되었습니다.\n"); }
		if (InputManager::GetKeyState(VK_F10) && !macro) { macro = true;  printfScreen(); printf("매크로가 시작되었습니다.\n"); }

		if (macro) {
			if (InputManager::GetKeyUp(VK_LBUTTON)) {
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
	}
}

void printfScreen() {
	system("cls");
	printf("F10: 매크로 실행\n");
	printf("F9: 매크로 정지\n");
	printf("F8: 매크로 종료\n");
	printf("\n");
}

void init() {
	system("mode con cols=30 lines=6 | title Auto Double Click");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO consoleCursor;
	consoleCursor.bVisible = 0;
	consoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &consoleCursor);

	DWORD prevMode = 0;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(handle, &prevMode);
	SetConsoleMode(handle, prevMode & ~ENABLE_QUICK_EDIT_MODE);
}