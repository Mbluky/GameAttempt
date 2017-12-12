#include "../_SOURCE LevelEdditor/LevelController.h"
#include "../_SOURCE LevelEdditor/KeyboardInput.h"
#include "../_SOURCE LevelEdditor/GameLevel.h"

E_GameLevel* E_LevelController::CurentLevel;
bool E_LevelController::loading;
HPTimer* E_LevelController::Timer;
E_KeyBoard* E_LevelController::keyboard;
E_KeyState E_LevelController::keyState;

void E_LevelController::init() 
{
	loading = true;
	CurentLevel = 0;
	Timer = new HPTimer(60);
	keyboard = new E_KeyBoard();
}

void E_LevelController::LoadInitialLevel(E_GameLevel* lev) 
{
	loading = true;
	CurentLevel = lev;
	CurentLevel->Load();
	loading = false;
}

void E_LevelController::SwitchLevel(E_GameLevel* lev) 
{
	loading = true;
	CurentLevel->Unload();
	CurentLevel = lev;
	delete lev;
}

void E_LevelController::update()
{
	Timer->update();
	Timer->waitForFrame();
	CurentLevel->Update();
	keyState = keyboard->getInputState();
	CurentLevel->getInput(keyState);
}

void E_LevelController::render()
{
	CurentLevel->Render();
}
