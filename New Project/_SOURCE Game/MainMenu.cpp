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
			Change->Play(1.0, 0.5);
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
				quit->getSelected(true);
				option->getSelected(false);
				selection = 2;
			}
			else if(selection == 0)
			{
				play->getSelected(false);
				selection = 1;
				option->getSelected(true);
			}
			Change->Play(1.0f, 0.5f);
		}
		if (m_keyState.jump && !m_prevKeyState.jump)
		{
			Accept->Play(1.0f, 0.5f);
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
			if (selection  >= 4)
			{
				WorldList[4]->getSelected(false);
				selection = 0;
				WorldList[0]->getSelected(true);
			}else
			{
				WorldList[selection]->getSelected(false);
				selection++;
				WorldList[selection]->getSelected(true);
			}
			Change->Play(1.0f, 0.5f);
		}
		else if (m_keyState.up && !m_prevKeyState.up)
		{
			if(selection <= 0)
			{
				WorldList[0]->getSelected(false);
				selection = 4;
				WorldList[4]->getSelected(true);
			}else
			{
				WorldList[selection]->getSelected(false);
				selection--;
				WorldList[selection]->getSelected(true);
			}
			Change->Play(1.0f, 0.5f);
		}
		else if (m_keyState.jump && !m_prevKeyState.jump)
		{
			if (unlockedLevels[selection][0] == true)
			{
				selectedWorld = selection;
				WorldList[selection]->getSelected(false);
				LevelList[0]->getSelected(true);
				selection = 0;
				subMenu = 2;
				Accept->Play(1.0f, 0.5f);
			}
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
			Change->Play(1.0f, 0.5f);
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
			Change->Play(1.0f, 0.5f);
		}else if(m_keyState.jump && !m_prevKeyState.jump)
		{
			if (unlockedLevels[selectedWorld][selection]) 
			{
				Accept->Play(1.0f, 0.5f);
				LevelController::updateStage(selectedWorld, selection);
				switchingTrigger = true;
			}
		}
	}
}

void MainMenu::Load()
{
	GameName = new Phrase((string)"Normal Jumps 1", 0, 10, 4);
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

	
	int x = 0, y = 0;
	while(y < 10)
	{
		while(x<10)
		{
			unlockedLevels[x][y] = false;
			x++;
		}
		y++;
	}
	int lastUnlockedStage;
	unlockedLevels[0][0] = true;
	string saveFileLocation("Save//Save.txt");
	ifstream saveFile;
	saveFile.open(saveFileLocation.c_str());
	if(!saveFile)
	{
		saveFile.close();
		ofstream saveFileOut(saveFileLocation.c_str());
		saveFileOut.clear();
		saveFileOut << "0" << endl;
		saveFileOut.close();
	}else
	{
		saveFile >> lastUnlockedStage;
		saveFile.close();
	}
	
	int lastUnlockedWorld;
	int lastUnlockedLevelIndex;

	lastUnlockedWorld = ((int)(lastUnlockedStage / 10));
	lastUnlockedLevelIndex = lastUnlockedStage - (lastUnlockedWorld * 10);

	for (int w = 0; w <= lastUnlockedWorld; w++)
	{
		if (w == lastUnlockedWorld) 
		{
			for (int l = 0; l <= lastUnlockedLevelIndex; l++)
			{
				unlockedLevels[w][l] = true;
			}
		}
		else
		{
			for (int l = 0; l < 10; l++)
			{
				unlockedLevels[w][l] = true;
			}
		}
	}

	TCHAR * fileName = _TEXT("_SOURCE Sound//Funky.wav");
	MenuMusic = new Sound(fileName);

	fileName = _TEXT("_SOURCE Sound//Change.wav");
	Change = new Sound(fileName);
	
	fileName = _TEXT("_SOURCE Sound//accept.wav");
	Accept = new Sound(fileName);

	fileName = _TEXT("_SOURCE Sound//back.wav");
	Back = new Sound(fileName);

	MenuMusic->Play(1.0f, 0.5f);

	switchingTrigger = false;
}

void MainMenu::Unload()
{
	delete GameName;
	delete mainMenu;
	delete play;
	delete option;
	delete quit;
	delete MenuMusic;
	delete Change;
	delete Accept;
	delete Back;
	for (int i = 0; i < 5; i++)
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
		for (int i = 0; i < 5; i++)
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