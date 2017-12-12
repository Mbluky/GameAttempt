#ifndef D2DGRAPHICS_H
#define D2DGRAPHICS_H

#include <Windows.h>
#include <d2d1.h>

class D2DGraphics
{
	ID2D1Factory* factory; //D2DFactory COM interface, creates D2D Objects.
	ID2D1HwndRenderTarget* renderTarget; //D2D WND target, shows the program the window to render in.
public:
	D2DGraphics();//constructor.
	~D2DGraphics();//destructor.

	ID2D1RenderTarget* GetRenderTarget() 
	{
		return renderTarget;
	}

	bool initD2D(HWND wHandle);

	void beguinDraw (){renderTarget->BeginDraw();}
	void endDraw () {renderTarget->EndDraw();}

	void clearScreen (float r, float g, float b);
};

#endif //D2DGRAPHICS_H