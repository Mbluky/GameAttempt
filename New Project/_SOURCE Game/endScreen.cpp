#include "endScreen.h"

void EndScreen::Load()
{
	timer = 0;
	congratulations = new Phrase("Congratulations", 144, 20, 8);
	characterAnimation = new Phrase("Character Animation", 320, 204, 4);
	mrBlooper = new Phrase("MRBLOOPER", 484, 330, 4);
	mrBlooper->getSelected(true);
	everythingElse = new Phrase("everything else", 388, 466, 4);
	pyroMab = new Phrase("PyroMab", 516, 592, 4);
	pyroMab->getSelected(true);
}

void EndScreen::Unload()
{
	delete congratulations;
	congratulations = NULL;
	delete characterAnimation;
	characterAnimation = NULL;
	delete mrBlooper;
	mrBlooper = NULL;
	delete everythingElse;
	everythingElse = NULL;
	delete pyroMab;
	pyroMab = NULL;
}

void EndScreen::Update()
{
	timer+=1;
}

void EndScreen::Render()
{
	gfx->clearScreen(0.0f, 0.0f, 0.0f);
	congratulations->draw();
	characterAnimation->draw();
	mrBlooper->draw();
	everythingElse->draw();
	pyroMab->draw();
}

bool EndScreen::switchToOther()
{
	if (timer > 1200)
	{
		return true;
	}
	return false;
}

void EndScreen::getInput(KeyState keystate)
{
}
