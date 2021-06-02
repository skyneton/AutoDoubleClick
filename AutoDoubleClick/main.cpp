#include "InputManager.h"
#include "Windows.h"
#include "stdio.h"

void printfScreen(bool);
void init();

static bool macro = false;

int main() {
	init();
	printfScreen(false);
	while (1) {
		InputManager::UpdateKeyState();

		if (InputManager::GetKeyState(VK_F8)) break;
		if (InputManager::GetKeyUp(VK_F4)) { macro = !macro; printfScreen(true);  }

		if (macro) {
			if (InputManager::GetKeyUp(VK_LBUTTON)) {
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
	}
}

void printfScreen(bool state) {
	system("cls");
	if (!macro) printf("F4: ��ũ�� ����\n");
	else printf("F4: ��ũ�� ����\n");
	printf("F8: ��ũ�� ����\n");
	printf("\n");

	if (state) {
		if(macro) printf("��ũ�ΰ� ���۵Ǿ����ϴ�.\n");
		else printf("��ũ�ΰ� �����Ǿ����ϴ�.\n");
	}
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