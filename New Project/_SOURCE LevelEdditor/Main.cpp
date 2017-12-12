#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#include <dinput.h>

#include "../_SOURCE Common/Win32Functions.h"
#include "../_SOURCE LevelEdditor/LevelController.h"
#include "../_SOURCE LevelEdditor/LevelOne.h"
#include "../_SOURCE Common/Tiles.h"
#include "../_SOURCE Common/D2DGraphics.h"
#include "../_SOURCE Common/Doors.h"

//Main Function
int WINAPI WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nCmdShow)
{
	HWND hWnd; //the window

	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX)); //clearing the window class for initialisation

	wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW; // the style of the window
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance; //the window instance
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // the cursor
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //the background color
    wc.lpszClassName = "WindowClass1";

	RegisterClassEx(&wc); // registering the class

	RECT rect = { 0, 0, 1280, 720}; // creating the Window rectangle

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, NULL, WS_EX_OVERLAPPEDWINDOW); // adjusting the rectangle to an overlapped window

	RESOLUTION resolution; //creating the resulution from the adjusted rectangle

	resolution.width = rect.right - rect.left;
	resolution.height = rect.bottom - rect.top;

	//creating the window
	hWnd = CreateWindowEx(NULL,
                          "WindowClass1",    // name of the window class
                          "LevelEdditor",   // title of the window
                          WS_OVERLAPPEDWINDOW,    // window style
                          0,    // x-position of the window
                          0,    // y-position of the window
						  resolution.width, // width of the window
						  resolution.height,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL
	
	D2DGraphics* graphics = new D2DGraphics();
	if (!graphics->initD2D(hWnd))return 1;

	E_GameLevel::init(graphics);

	Door::initGFX(graphics);

	DeathTrap::initGFX(graphics);

	

	ShowWindow(hWnd, nCmdShow);
	
	E_LevelController::init();
	E_LevelController::LoadInitialLevel(new LevelEdditor);

	MSG message; //an empty message, used for message loop

	

	while (true)//infinite message loop
	{
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		if (message.message == WM_QUIT)
			break;

		//game code here
		

		//UPDATE
		
		E_LevelController::update();

		//RENDER
		graphics->beguinDraw();
		E_LevelController::render();
		graphics->endDraw();
		
	}
}
