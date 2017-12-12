#include "../_SOURCE Common/Letters.h"

SpriteSheet* Phrase::LetterSprites;
SpriteSheet* Phrase::selectedLetterSprites;
D2DGraphics* Phrase::gfx;


Phrase::Phrase(string _PhraseString, int x, int y, int scale)
{
	PhraseString = _PhraseString;
	m_x = x;
	m_y = y;
	this->scale = scale;
	int c = 0;
	while (c < 100)
	{
		PhraseCharacters[c].index = -1;
		c++;
	}
	c = 0;
	while (c < PhraseString.size())
	{
		if(PhraseString[c] == 'a' || PhraseString[c] == 'A')
		{
			PhraseCharacters[c].index = 0;
		}
		else if (PhraseString[c] == 'b' || PhraseString[c] == 'B')
		{
			PhraseCharacters[c].index = 1;
		}
		else if (PhraseString[c] == 'c' || PhraseString[c] == 'C')
		{
			PhraseCharacters[c].index = 2;
		}
		else if (PhraseString[c] == 'd'|| PhraseString[c] == 'D')
		{
			PhraseCharacters[c].index = 3;
		}
		else if (PhraseString[c] == 'e' || PhraseString[c] == 'E')
		{
			PhraseCharacters[c].index = 4;
		}
		else if (PhraseString[c] == 'f' || PhraseString[c] == 'F')
		{
			PhraseCharacters[c].index = 5;
		}
		else if (PhraseString[c] == 'g' || PhraseString[c] == 'G')
		{
			PhraseCharacters[c].index = 6;
		}
		else if (PhraseString[c] == 'h' || PhraseString[c] == 'H')
		{
			PhraseCharacters[c].index = 7;
		}
		else if (PhraseString[c] == 'i' || PhraseString[c] == 'I')
		{
			PhraseCharacters[c].index = 8;
		}
		else if (PhraseString[c] == 'j' || PhraseString[c] == 'J')
		{
			PhraseCharacters[c].index = 9;
		}
		else if (PhraseString[c] == 'k' || PhraseString[c] == 'K')
		{
			PhraseCharacters[c].index = 10;
		}
		else if (PhraseString[c] == 'l' || PhraseString[c] == 'L')
		{
			PhraseCharacters[c].index = 11;
		}
		else if (PhraseString[c] == 'm' || PhraseString[c] == 'M')
		{
			PhraseCharacters[c].index = 12;
		}
		else if (PhraseString[c] == 'n' || PhraseString[c] == 'N')
		{
			PhraseCharacters[c].index = 13;
		}
		else if (PhraseString[c] == 'o' || PhraseString[c] == 'O')
		{
			PhraseCharacters[c].index = 14;
		}
		else if (PhraseString[c] == 'p' || PhraseString[c] == 'P')
		{
			PhraseCharacters[c].index = 15;
		}
		else if (PhraseString[c] == 'q' || PhraseString[c] == 'Q')
		{
			PhraseCharacters[c].index = 16;
		}
		else if (PhraseString[c] == 'r' || PhraseString[c] == 'R')
		{
			PhraseCharacters[c].index = 17;
		}
		else if (PhraseString[c] == 's' || PhraseString[c] == 'S')
		{
			PhraseCharacters[c].index = 18;
		}
		else if (PhraseString[c] == 't' || PhraseString[c] == 'T')
		{
			PhraseCharacters[c].index = 19;
		}
		else if (PhraseString[c] == 'u' || PhraseString[c] == 'U')
		{
			PhraseCharacters[c].index = 20;
		}
		else if (PhraseString[c] == 'v' || PhraseString[c] == 'V')
		{
			PhraseCharacters[c].index = 21;
		}
		else if (PhraseString[c] == 'w' || PhraseString[c] == 'W')
		{
			PhraseCharacters[c].index = 22;
		}
		else if (PhraseString[c] == 'x' || PhraseString[c] == 'X')
		{
			PhraseCharacters[c].index = 23;
		}
		else if (PhraseString[c] == 'y' || PhraseString[c] == 'Y')
		{
			PhraseCharacters[c].index = 24;
		}
		else if (PhraseString[c] == 'z' || PhraseString[c] == 'Z')
		{
			PhraseCharacters[c].index = 25;
		}
		else if (PhraseString[c] == '0')
		{
			PhraseCharacters[c].index = 26;
		}
		else if (PhraseString[c] == '1')
		{
			PhraseCharacters[c].index = 27;
		}
		else if (PhraseString[c] == '2')
		{
			PhraseCharacters[c].index = 28;
		}
		else if (PhraseString[c] == '3')
		{
			PhraseCharacters[c].index = 29;
		}
		else if (PhraseString[c] == '4')
		{
			PhraseCharacters[c].index = 30;
		}
		else if (PhraseString[c] == '5')
		{
			PhraseCharacters[c].index = 31;
		}
		else if (PhraseString[c] == '6')
		{
			PhraseCharacters[c].index = 32;
		}
		else if (PhraseString[c] == '7')
		{
			PhraseCharacters[c].index = 33;
		}
		else if (PhraseString[c] == '8')
		{
			PhraseCharacters[c].index = 34;
		}
		else if (PhraseString[c] == '9')
		{
			PhraseCharacters[c].index = 35;
		}
		else if (PhraseString[c] == '-')
		{
			PhraseCharacters[c].index = 36;
		}
		else if (PhraseString[c] == '/')
		{
			PhraseCharacters[c].index = 37;
		}else 
		{
			PhraseCharacters[c].index = 38;
		}

		PhraseCharacters[c].animetion.startY = (PhraseCharacters[c].index * 8);
		PhraseCharacters[c].animetion.spritesAccross = 1;
		PhraseCharacters[c].animetion.spriteSizeX = 8;
		PhraseCharacters[c].animetion.spriteSizeY = 8;
		PhraseCharacters[c].animetion.FPS = 1;

		c++;
	}
	c = 0;

	while (c < PhraseString.size())
	{
		PhraseCharacters[c].posY = m_y;
		if (c == 0)
		{
			PhraseCharacters[c].posX = m_x;
			
		}else if(PhraseCharacters[(c-1)].index == 38)
		{
			PhraseCharacters[c].posX = PhraseCharacters[c - 1].posX + (3*scale);
			
		}else
		{
			PhraseCharacters[c].posX = PhraseCharacters[c - 1].posX + (9*scale);
			
		}
		c++;
	}
	isHighlighted = false;
}

Phrase::~Phrase()
{
	
}

void Phrase::draw()
{
	{

		int c = 0;
		while (c < PhraseString.size())
		{
			if (PhraseCharacters[c].index != 38)
			{
				if (isHighlighted)
				{
					selectedLetterSprites->Draw(1,
						PhraseCharacters[c].animetion,
						PhraseCharacters[c].posX, PhraseCharacters[c].posY, scale);
				}
				else
				{
					LetterSprites->Draw(1,
						PhraseCharacters[c].animetion,
						PhraseCharacters[c].posX, PhraseCharacters[c].posY, scale);
				}

			}
			c++;
		}
	}
}


void Phrase::getSelected(bool selected)
{
	isHighlighted = selected;
}

void Phrase::initSprites(D2DGraphics* GFX)
{
	gfx = GFX;
}

void Phrase::load()
{
	LetterSprites = new SpriteSheet(L"_SOURCE Assets/GameFont.png", gfx, true);
	selectedLetterSprites = new SpriteSheet(L"_SOURCE Assets/GameFontSelected.png", gfx, true);
}
