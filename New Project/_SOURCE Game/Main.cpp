#include <windows.h>
#include <windowsx.h>
#include <WinUser.h>
#include <d2d1.h>
#include <dinput.h>

#include "../_SOURCE Common/Win32Functions.h"
#include "../_SOURCE Game/LevelController.h"
#include "../_SOURCE Game/LevelOne.h"
#include "../_SOURCE Game/PlayerCharacter.h"
#include "../_SOURCE Common/D2DGraphics.h"
#include "../_SOURCE Game/TileManager.h"
#include "../_SOURCE Common/Letters.h"
#include "../_SOURCE Common/SpriteSheet.h"
#include "../_SOURCE Game/MainMenu.h"
#include "../_SOURCE Common/Doors.h"
#include "../_SOURCE Game/PauseMenu.h"

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

	RESOLUTION resolution; //creating the resulution from the adjusted rectangle

	//creating the window
	hWnd = CreateWindowEx(NULL,
                          "WindowClass1",    // name of the window class
                          "GAME",   // title of the window
						  WS_EX_TOPMOST | WS_POPUP, // window style
                          0,    // x-position of the window
                          0,    // y-position of the window
						  1280, // width of the window
						  720,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

	D2DGraphics* graphics = new D2DGraphics();
	if (!graphics->initD2D(hWnd))return 1;

	SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);

	TileManager::initGFX(graphics);
	Phrase::initSprites(graphics);
	DeathTrap::initGFX(graphics);
	PauseMenu::initGfx(graphics);
	Character::init(graphics);
	Door::initGFX(graphics);
	PlayerCharacter* PlayerOne = new PlayerCharacter();

	GameLevel::init(graphics);
	GameLevel::loadPCharacter(PlayerOne);

	ShowWindow(hWnd, nCmdShow);
	
	LevelController::init();
	LevelController::LoadInitialLevel();

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
		
		LevelController::update();

		//RENDER
		graphics->beguinDraw();
		LevelController::render();
		graphics->endDraw();
		
	}
}
