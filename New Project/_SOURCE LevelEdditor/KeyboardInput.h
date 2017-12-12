#ifndef KEYBOARD_INPUT_E_H
#define KEYBOARD_INPUT_E_H

#include <WinUser.h>

struct E_KeyState 
{
	bool up, down, left, right, changeMode, nextTile, previousTile, Place, Delete, Save, SwitchSpriteSheet;
};

class E_KeyBoard 
{
	DWORD Up = 0x5A; // Z
	DWORD Down = 0x53; // S
	DWORD Left = 0x51; // Q
	DWORD Right = 0x44; // D
	DWORD ChangeMode = 0x52; // R
	DWORD NextTile = 0x45; // E
	DWORD PreviousTile = 0x41; // A
	DWORD Place = 0x4C; // L
	DWORD Delete = 0x2E; // Delete
	DWORD Save = 0x4B; // K
	DWORD SwitchSpriteSheet = 0x4F; // O

public:
	E_KeyBoard() 
	{
	}
	
	E_KeyState getInputState()
	{
		E_KeyState inputState =
		{
			GetAsyncKeyState(Up),
			GetAsyncKeyState(Down),
			GetAsyncKeyState(Left),
			GetAsyncKeyState(Right),
			GetAsyncKeyState(ChangeMode),
			GetAsyncKeyState(NextTile),
			GetAsyncKeyState(PreviousTile),
			GetAsyncKeyState(Place),
			GetAsyncKeyState(Delete),
			GetAsyncKeyState(Save),
			GetAsyncKeyState(SwitchSpriteSheet)
		};
		
		return inputState;
	}

};

#endif //KEYBOARD_INPUT_E_H