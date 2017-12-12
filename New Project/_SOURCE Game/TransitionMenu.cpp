#include "TransitionMenu.h"

int T_Menu::m_World = 0;
int T_Menu::m_Level = 0;

void T_Menu::Load()
{
	m_keyState = { false, false, false, false, false, false, false, false };
	m_prevKeyState = m_keyState;
	countDown = 180;
	string sLevelName("Level ");
	sLevelName += std::to_string(m_World + 1);
	sLevelName += '-';
	sLevelName += std::to_string(m_Level + 1);
	levelName = new Phrase(sLevelName, 300, 300, 8);
	clear = new Phrase("Clear", 300, 380, 8);
}

void T_Menu::Unload()
{
	delete levelName;
	delete clear;
}

void T_Menu::Update()
{
	countDown--;
	if(countDown <= 0)
	{
		loadNextStage = true;
		countDown = 180;
	}
}

void T_Menu::Render()
{
	gfx->clearScreen(0.0f, 0.0f, 0.0f);
	levelName->draw();
	clear->draw();
}

void T_Menu::getInput(KeyState keystate)
{
	m_prevKeyState = m_keyState;
	m_keyState = keystate;
}

bool T_Menu::switchToOther()
{
	return loadNextStage;
}

void T_Menu::getCurrentLevel(int World, int Level)
{
	m_World = World;
	m_Level = Level;
}