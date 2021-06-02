#pragma once
#define KEYPRESSED 2
#define KEYDOWN 1
#define KEYUP -1

class InputManager
{
public:
	static void UpdateKeyState();
	static int GetKeyState(int vk);
	static bool GetKeyDown(int vk);
	static bool GetKeyPressed(int vk);
	static bool GetKeyUp(int vk);

	static int GetMouseX();
	static int GetMouseY();

private:
	static bool lkey[256], rkey[256];
	static int mX, mY;
};

