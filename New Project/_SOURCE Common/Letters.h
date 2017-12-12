#ifndef LETTER_HEADER_H
#define LETTER_HEADER_H

#include <string>
#include "../_SOURCE Common/SpriteSheet.h"

struct LETTER
{
	float posX;
	float posY;
	int index;
	ANIMATION animetion;
};

class Phrase
{
	static SpriteSheet* LetterSprites;
	static SpriteSheet* selectedLetterSprites;
	static D2DGraphics* gfx;
	string PhraseString;
	LETTER PhraseCharacters[100];
	bool isHighlighted;
	int m_x, m_y, scale;
public:

	Phrase(string _PhraseString, int x, int y, int scale = 1);
	~Phrase();
	void draw();
	void getSelected(bool selected);
	static void initSprites(D2DGraphics* GFX);
	static void load();
	
};

#endif // !LETTER_HEADER_H