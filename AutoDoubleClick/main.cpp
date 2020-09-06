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
		if (InputManager::GetKeyState(VK_F9) && macro) { macro = false; printfScreen(); printf("��ũ�ΰ� �����Ǿ����ϴ�.\n"); }
		if (InputManager::GetKeyState(VK_F10) && !macro) { macro = true;  printfScreen(); printf("��ũ�ΰ� ���۵Ǿ����ϴ�.\n"); }

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
	printf("F10: ��ũ�� ����\n");
	printf("F9: ��ũ�� ����\n");
	printf("F8: ��ũ�� ����\n");
	printf("\n");
}