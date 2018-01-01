#include "../_SOURCE Game/MainMenu.h"


void MainMenu::getInput(KeyState keyState)
{
	m_prevKeyState = m_keyState;
	m_keyState = keyState;
	
}

bool MainMenu::switchToOther()
{
	return switchingTrigger;
}

void MainMenu::Update()
{
	if(m_keyState.up && !m_prevKeyState.up)
	{
		if(selection==0)
		{
			play->getSelected(false);
			selection = 2;
			quit->getSelected(true);
		}else if (selection == 1)
		{
			option->getSelected(false);
			selection--;
			play->getSelected(true);
		}else
		{
			quit->getSelected(false);
			selection--;
			option->getSelected(true);
		}
	}
	else if(m_keyState.down && !m_prevKeyState.down)
	{
		if(selection == 2)
		{
			quit->getSelected(false);
			selection = 0;
			play->getSelected(true);
		}else if(selection == 1)
		{
			option->getSelected(false);
			selection++;
			quit->getSelected(true);
		}else
		{
			play->getSelected(false);
			selection++;
			option->getSelected(true);
		}
	}
	if (m_keyState.jump && !m_prevKeyState.jump)
	{
		if (selection == 0)
		{
			switchingTrigger = true;
		}
		if( selection == 2)
		{
			exit(EXIT_SUCCESS);
		}
	}
}


void MainMenu::Load()
{
	GameName = new Phrase((string)"Game Attempt", 0, 10, 4);
	mainMenu = new Phrase((string)"Main Menu", 260, 300, 8);
	play = new Phrase((string)"Play", 480, 440, 4);
	option = new Phrase((string)"Options", 480, 500, 4);
	quit = new Phrase((string)"Quit", 480, 560, 4);
	int selection = 0;
	m_keyState = { true, true, true, true, true, true ,true ,true };
	m_prevKeyState = { true, true, true, true, true, true ,true ,true };
	switchingTrigger = false;
	play->getSelected(true);

}

void MainMenu::Unload()
{
	delete GameName;
	delete mainMenu;
	delete play;
	delete option;
	delete quit;
}

void MainMenu::Render()
{
	gfx->clearScreen(0.0f, 0.0f, 0.0f);
	GameName->draw();
	mainMenu->draw();
	play->draw();
	option->draw();
	quit->draw();
}


