#ifndef LEVEL_CONTROLLER_H
#define LEVEL_CONTROLLER_H

#include "../_SOURCE LevelEdditor/GameLevel.h"
#include "../_SOURCE Common/D2DGraphics.h"
#include "../_SOURCE Common/HighPrecisionTimer.h"
#include "../_SOURCE LevelEdditor/KeyboardInput.h"

class E_LevelController
{
	E_LevelController();
	static E_GameLevel* CurentLevel;
	static HPTimer* Timer;
	static E_KeyBoard* keyboard;
	static E_KeyState keyState;
public:

	static void init();

	static void LoadInitialLevel(E_GameLevel* lev);
	static void SwitchLevel(E_GameLevel*lev);

	static bool loading;

	static void update();
	static void render();
};

#endif //LEVEL_CONTROLLER_H