#include "../_SOURCE Game/LevelController.h"
#include "../_SOURCE Game//KeyboardInput.h"
#include "../_SOURCE Game/MainMenu.h"
#include "../_SOURCE Common/Letters.h"
#include "../_SOURCE Game/LevelOne.h"
#include "../_SOURCE Game/TransitionMenu.h"

GameLevel* LevelController::CurentLevel;
bool LevelController::loading;
HPTimer* LevelController::Timer;
KeyBoard* LevelController::keyboard;
KeyState LevelController::keyState;
GameLevel* LevelController::Levels[3]{ new MainMenu(), new LevelOne(), new T_Menu()};
int LevelController::levelIndex;
int LevelController::m_curentWorld = 0;
int LevelController::m_curentLevel = 0;

void LevelController::init() 
{
	loading = true;
	CurentLevel = 0;
	Timer = new HPTimer(60);
	keyboard = new KeyBoard();
	Phrase::load();
}

void LevelController::LoadInitialLevel() 
{
	loading = true;
	levelIndex = 0;
	CurentLevel = Levels[levelIndex];
	CurentLevel->Load();
	loading = false;
}

void LevelController::SwitchLevel() 
{
	CurentLevel->Unload();
	if (levelIndex == 0)
	{
		levelIndex = 1;
		CurentLevel = Levels[levelIndex];
		LevelOne::getCurrentLevel(m_curentWorld, m_curentLevel);
	}else if (levelIndex == 1)
	{
		levelIndex = 2;
		CurentLevel = Levels[levelIndex];
		T_Menu::getCurrentLevel(m_curentWorld, m_curentLevel);
		m_curentLevel++;
		if(m_curentLevel > 9)
		{
			m_curentLevel = 0;
			m_curentWorld++;
		}
	}else if (levelIndex == 2)
	{
		levelIndex = 1;
		CurentLevel = Levels[levelIndex];
		LevelOne::getCurrentLevel(m_curentWorld, m_curentLevel);
	}
	CurentLevel->Load();
}

void LevelController::update()
{
	if(CurentLevel->switchToOther())
	{
		SwitchLevel();
	}else if(LevelOne::changeMode() == 1)
	{
		CurentLevel->Unload();
		levelIndex = 0;
		CurentLevel = Levels[levelIndex];
		CurentLevel->Load();
	}
	Timer->update();
	CurentLevel->getInput(keyboard->getInputState());
	CurentLevel->Update();
	Timer->waitForFrame();
}

void LevelController::render()
{
	CurentLevel->Render();
}
