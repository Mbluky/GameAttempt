#include "../_SOURCE LevelEdditor/LevelOne.h"
#include "../_SOURCE LevelEdditor/LevelController.h"
#include "../_SOURCE LevelEdditor/GameLevel.h"

void LevelEdditor::Load()
{
	tilePlacer = new TilePlacer();
	tilePlacer->getGFX(gfx);
	
}

void LevelEdditor::Unload()
{
}


void LevelEdditor::Update()
{
	tilePlacer->moveCursor();
	tilePlacer->chackInput();
}

void LevelEdditor::Render()
{
	gfx->clearScreen(0.05f, 0.05f, 0.07f);
	tilePlacer->drawStageTiles();
	tilePlacer->draw();

}

void LevelEdditor::getInput(E_KeyState keystate)
{
	tilePlacer->getInput(keystate);
}




