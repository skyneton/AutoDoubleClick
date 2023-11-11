#include "InputManager.h"
#include "Windows.h"
#include "stdio.h"
#include "thread"

void printfScreen(bool);
void init();

static bool macro = false;
static bool autoclick = false;

int main() {
	init();
	printfScreen(false);
	std::chrono::milliseconds wait = std::chrono::milliseconds(1);
	while (1) {
		InputManager::UpdateKeyState();

		if (InputManager::GetKeyState(VK_F8)) break;
		if (InputManager::GetKeyUp(VK_F4)) { macro = !macro; printfScreen(true); }
		if (InputManager::GetKeyUp(VK_F6)) { autoclick = !autoclick; printfScreen(true); }

		if (autoclick) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

		if (macro) {
			if (InputManager::GetKeyUp(VK_RBUTTON)) {
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			}
		}
		std::this_thread::sleep_for(wait);
	}
}

void printfScreen(bool state) {
	system("cls");
	if (!macro) puts("F4: 매크로 실행");
	else puts("F4: 매크로 중지");
	if (autoclick) puts("F6: 오토클릭 중지");
	else puts("F6: 오토클릭 실행");
	puts("F8: 매크로 종료");
	puts("");

	if (state) {
		if(macro) puts("매크로가 시작되었습니다.");
		else puts("매크로가 정지되었습니다.");
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