#include "../_SOURCE Game/LevelOne.h"
#include "../_SOURCE Game/LevelController.h"
#include "../_SOURCE Game/TileManager.h"
#include "../_SOURCE Game/PauseMenu.h"

int LevelOne::world = 0;
int LevelOne::level = 0;
int LevelOne::nextMode = 0;

void LevelOne::Load()
{
	isPaused = false;
	PlayerOne->load(50.0f, 456.0f);
	TileManager::loadStageTiles(world, level);
	PauseMenu::load();
}

void LevelOne::Unload()
{
	PlayerOne->unload();
	PauseMenu::unload();
}

void LevelOne::Update()
{
	if (!isPaused)
	{
		PlayerOne->update();
		TileManager::checkColition(PlayerOne);
	}else
	{
		if(quitToMenu)
		{
			nextMode = 1;
		}
	}
}

void LevelOne::Render()
{
	gfx->clearScreen(0.05f, 0.05f, 0.07f);
	TileManager::drawTiles();
	PlayerOne->draw();
	if(isPaused)
	{
		PauseMenu::draw();
	}
}

void LevelOne::getInput(KeyState keystate)
{
	if(keystate.menu)
	{
		isPaused = true;
	}
	if (!isPaused)
	{
		PlayerOne->checkKeyPress(keystate);
	}else
	{
		PauseMenu::getInput(keystate);
		PauseMenu::update();
		isPaused = PauseMenu::resume();
		quitToMenu = PauseMenu::quitToMainMenu();
	}
}

bool LevelOne::switchToOther()
{
	return PlayerOne->endCurentStage();
}

void LevelOne::getCurrentLevel(int currentWorld, int currentLevel)
{
	level = currentLevel;
	world = currentWorld;
}

int LevelOne::changeMode()
{
	if (nextMode == 1)
	{
		nextMode = 0;
		return 1;
	}
}
