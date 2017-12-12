#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <wincodec.h>

#include "../_SOURCE Common/D2DGraphics.h"
#include "../_SOURCE Common/Animations.h"

class SpriteSheet
{
	D2DGraphics* gfx;
	ID2D1Bitmap* bmp;
	ID2D1Bitmap* bmpFliped;
	bool m_facingRight;
public:

	SpriteSheet(wchar_t* fileName, D2DGraphics* graphics, bool facingRight);
	~SpriteSheet();

	void Draw( int index, ANIMATION curentAnimation, int x, int y, float scale = 4);
};

#endif // !SPRITE_SHEET_H