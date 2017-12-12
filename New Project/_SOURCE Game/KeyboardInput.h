#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <WinUser.h>

struct KeyState 
{
	bool up, down, left, right, jump, action, run, menu;
};

class KeyBoard 
{
	DWORD Up = 0x5A; // Z
	DWORD Down = 0x53; // S
	DWORD Left = 0x51; // Q
	DWORD Right = 0x44; // D
	DWORD Jump = 0x4B; // K
	DWORD Action = 0x45; // E
	DWORD Run = 0x4A; // J
	DWORD Menu = 0x1B; // ESC

public:
	KeyBoard() 
	{
	}
	
	KeyState getInputState()
	{
		KeyState inputState =
		{
			GetAsyncKeyState(Up),
			GetAsyncKeyState(Down),
			GetAsyncKeyState(Left),
			GetAsyncKeyState(Right),
			GetAsyncKeyState(Jump),
			GetAsyncKeyState(Action),
			GetAsyncKeyState(Run),
			GetAsyncKeyState(Menu)

		};
		
		return inputState;
	}

};

#endif //KEYBOARD_INPUT_H