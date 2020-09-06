#include "InputManager.h"
#include "Windows.h"
#include "stdio.h"

void printfScreen();

int main() {
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