#ifndef _WINFUNCTIONS_H
#define _WINFUNCTIONS_H

#include <windows.h>

#include "../_SOURCE Common/D2DGraphics.h"

//structs and variables
struct RESOLUTION
{
	int width;
	int height;
	bool fullScreen;
};

//functions

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //the window procedure prototype

#endif // _WINFUNCTIONS_H