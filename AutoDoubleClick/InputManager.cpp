#include "InputManager.h"
#include "Windows.h"

bool InputManager::lkey[256];
bool InputManager::rkey[256];
int InputManager::mX;
int InputManager::mY;

void InputManager::UpdateKeyState() {
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	mX = mousePosition.x;
	mY = mousePosition.y;

	for (int i = 0; i < 256; ++i) {
		lkey[i] = rkey[i];
		rkey[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

int InputManager::GetKeyState(int vk) {
	if (lkey[vk] && rkey[vk]) return KEYPRESSED; //Ű ������ ����
	if (!lkey[vk] && rkey[vk]) return KEYDOWN; //Ű ���� ����
	if (lkey[vk] && !rkey[vk]) return KEYUP; //Ű ��

	return 0;
}

bool InputManager::GetKeyDown(int vk) {
	return GetKeyState(vk) == KEYDOWN;
}

bool InputManager::GetKeyPressed(int vk) {
	return GetKeyState(vk) == KEYPRESSED;
}

bool InputManager::GetKeyUp(int vk) {
	return GetKeyState(vk) == KEYUP;
}

int InputManager::GetMouseX() {
	return mX;
}

int InputManager::GetMouseY() {
	return mY;
}