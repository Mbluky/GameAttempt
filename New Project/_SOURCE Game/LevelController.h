#ifndef LEVEL_CONTROLLER_H
#define LEVEL_CONTROLLER_H

#include "../_SOURCE Game/GameLevel.h"
#include "../_SOURCE Common/D2DGraphics.h"
#include "../_SOURCE Common/HighPrecisionTimer.h"
#include "../_SOURCE Game/KeyboardInput.h"

class LevelController
{
	static GameLevel* CurentLevel;
	static HPTimer* Timer;
	static KeyBoard* keyboard;
	static KeyState keyState;
	static GameLevel* Levels[3];
	static int levelIndex;
	static int m_curentWorld, m_curentLevel;
public:

	static void init();

	static void LoadInitialLevel();
	static void SwitchLevel();

	static bool loading;

	static void update();
	static void render();

	static void updateStage(unsigned int world,unsigned int level);
};

#endif //LEVEL_CONTROLLER_H