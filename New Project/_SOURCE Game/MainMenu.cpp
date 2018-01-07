#include "../_SOURCE Game/MainMenu.h"
#include "../_SOURCE Game/LevelController.h"
#include <tchar.h>
#include <Windows.h>


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
	if (subMenu == 0)
	{
		if (m_keyState.up && !m_prevKeyState.up)
		{
			if (selection == 0)
			{
				play->getSelected(false);
				selection = 2;
				quit->getSelected(true);
			}
			else if (selection == 1)
			{
				option->getSelected(false);
				selection--;
				play->getSelected(true);
			}
			else
			{
				quit->getSelected(false);
				selection--;
				option->getSelected(true);
			}
		}
		else if (m_keyState.down && !m_prevKeyState.down)
		{
			if (selection == 2)
			{
				quit->getSelected(false);
				selection = 0;
				play->getSelected(true);
			}
			else if (selection == 1)
			{
				option->getSelected(false);
				selection++;
				quit->getSelected(true);
			}
			else
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
				selection = 0;
				play->getSelected(false);
				WorldList[0]->getSelected(true);
				subMenu = 1;
			}
			if (selection == 2)
			{
				Unload();
				exit(EXIT_SUCCESS);
			}
		}
	}else if(subMenu == 1)
	{
		if (m_keyState.down && !m_prevKeyState.down)
		{
			if (selection  >= 9)
			{
				WorldList[9]->getSelected(false);
				selection = 0;
				WorldList[0]->getSelected(true);
			}else
			{
				WorldList[selection]->getSelected(false);
				selection++;
				WorldList[selection]->getSelected(true);
			}
		}
		else if (m_keyState.up && !m_prevKeyState.up)
		{
			if(selection <= 0)
			{
				WorldList[0]->getSelected(false);
				selection = 9;
				WorldList[9]->getSelected(true);
			}else
			{
				WorldList[selection]->getSelected(false);
				selection--;
				WorldList[selection]->getSelected(true);
			}
		}
		else if (m_keyState.jump && !m_prevKeyState.jump)
		{
			selectedWorld = selection;
			WorldList[selection]->getSelected(false);
			LevelList[0]->getSelected(true);
			selection = 0;
			subMenu = 2;
		}
	}
	else if (subMenu == 2)
	{
		if(m_keyState.down && !m_prevKeyState.down)
		{
			if(selection >= 9)
			{
				LevelList[9]->getSelected(false);
				selection = 0;
				LevelList[0]->getSelected(true);
			}else
			{
				LevelList[selection]->getSelected(false);
				selection++;
				LevelList[selection]->getSelected(true);
			}
		}
		else if (m_keyState.up && !m_prevKeyState.up)
		{
			if(selection <= 0)
			{
				LevelList[0]->getSelected(false);
				selection = 9;
				LevelList[selection]->getSelected(true);
			}else
			{
				LevelList[selection]->getSelected(false);
				selection--;
				LevelList[selection]->getSelected(true);
			}
		}else if(m_keyState.jump && !m_prevKeyState.jump)
		{
			LevelController::updateStage(selectedWorld, selection);
			switchingTrigger = true;
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

	string WorldName("World ");
	string StageName("Level ");
	int j = 0;

	for (int i = 0; i < 10; i++)
	{
		j = i + 1;
		WorldName += std::to_string(j);
		WorldList[i] = new Phrase(WorldName, 138*4, (40 + (i*14))*4, 4);
		WorldName = ("World ");
	}

	for (int i = 0; i < 10; i++)
	{
		j = i + 1;
		StageName += std::to_string(j);
		LevelList[i] = new Phrase(StageName, 138*4, (40 +(i*14))*4, 4);
		StageName = ("Level ");
	}
	selection = 0;
	subMenu = 0;
	m_keyState = { true, true, true, true, true, true ,true ,true };
	m_prevKeyState = { true, true, true, true, true, true ,true ,true };
	switchingTrigger = false;
	play->getSelected(true);

	TCHAR * fileName = _TEXT("Funky.wav");

	MenuMusic = new Sound(fileName);

	MenuMusic->Play(1.0f, 0.5f);

}

void MainMenu::Unload()
{
	delete GameName;
	delete mainMenu;
	delete play;
	delete option;
	delete quit;
	delete MenuMusic;
	for (int i = 0; i < 10; i++)
	{
		delete WorldList[i];
		WorldList[i] = NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		delete LevelList[i];
		LevelList[i] = NULL;
	}
}

void MainMenu::Render()
{
	gfx->clearScreen(0.0f, 0.0f, 0.0f);
	if (subMenu == 0)
	{
		GameName->draw();
		mainMenu->draw();
		play->draw();
		option->draw();
		quit->draw();
	}else if (subMenu == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			WorldList[i]->draw();
		}
	}else if(subMenu == 2)
	{
		for (int i = 0; i < 10; i++)
		{		
			LevelList[i]->draw();
		}
	}
}