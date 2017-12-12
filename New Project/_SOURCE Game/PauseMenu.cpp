#include "../_SOURCE Game/PauseMenu.h"

bool PauseMenu::m_paused = true;
bool PauseMenu::returnToMainMenu = false;
Phrase* PauseMenu::menuOptions[3]{ NULL, NULL, NULL };
Phrase* PauseMenu::m_PauseMenuTitle = NULL;
KeyState PauseMenu::m_keystate = { false, false, false, false, false, false, false, false };
KeyState PauseMenu::m_prevkeystate = { false, false, false, false, false, false, false, false };
SpriteSheet* PauseMenu::menuBorderSprite = NULL;
D2DGraphics* PauseMenu::m_gfx = NULL;
int PauseMenu::selection = 0;
int PauseMenu::subMenu = 0;

void PauseMenu::initGfx(D2DGraphics* gfx)
{
	m_gfx = gfx;
	menuBorderSprite = new SpriteSheet(L"_SOURCE Assets/PauseMenuFrame.png", gfx, true);
}

void PauseMenu::getInput(KeyState keystate)
{
	m_prevkeystate = m_keystate;
	m_keystate = keystate;
}


void PauseMenu::update()
{
	if (m_keystate.up && !m_prevkeystate.up)
	{
		menuOptions[selection]->getSelected(false);
		selection--;
		if (selection < 0)
		{
			selection = 2;
		}
		menuOptions[selection]->getSelected(true);
	}
	if (m_keystate.down && !m_prevkeystate.down)
	{
		menuOptions[selection]->getSelected(false);
		selection++;
		if (selection > 2)
		{
			selection = 0;
		}
		menuOptions[selection]->getSelected(true);
	}
	if (m_keystate.jump && !m_prevkeystate.jump)
	{
		select();
	}
}

void PauseMenu::draw()
{
	menuBorderSprite->Draw(1, { 80, 120, 0, 1, 1 }, 480, 120, 4);

	m_PauseMenuTitle->draw();
	menuOptions[0]->draw();
	menuOptions[1]->draw();
	menuOptions[2]->draw();
}

void PauseMenu::load()
{
	menuOptions[0] = new Phrase("resume", 536, 260, 4);
	menuOptions[1] = new Phrase("option", 536, 360, 4);
	menuOptions[2] = new Phrase("main menu", 492, 460, 4);

	m_PauseMenuTitle = new Phrase("Pause", 552, 132, 4);

	selection = 0;
	subMenu = 0;
	menuOptions[0]->getSelected(true);
}

void PauseMenu::unload()
{
	delete menuOptions[0];
	menuOptions[0] = NULL;
	delete menuOptions[1];
	menuOptions[1] = NULL;
	delete menuOptions[2];
	menuOptions[2] = NULL;
}

void PauseMenu::select()
{
	if (selection == 0)
	{
		m_paused = false;
	}else if (selection == 2)
	{
		returnToMainMenu = true;
	}
}

bool PauseMenu::quitToMainMenu()
{
	if(returnToMainMenu)
	{
		returnToMainMenu = false;
		return true;
	}
	else return false;
}

bool PauseMenu::resume()
{
	if (m_paused == false)
	{
		m_paused = true;
		return false;
	}
	else return true;
}
