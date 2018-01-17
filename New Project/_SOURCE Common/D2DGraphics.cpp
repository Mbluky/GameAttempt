#include "../_SOURCE Common/D2DGraphics.h"

D2DGraphics::D2DGraphics()
{
	factory = NULL;
	renderTarget = NULL;
}

D2DGraphics::~D2DGraphics()
{
	if(factory) factory->Release();
	if(renderTarget) renderTarget->Release();
}

bool D2DGraphics::initD2D(HWND wHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&factory);
	if (res != S_OK) return false;

	RECT rect;

	GetClientRect(wHandle, &rect);
	
	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), 
									D2D1::HwndRenderTargetProperties(wHandle,D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top), D2D1_PRESENT_OPTIONS_IMMEDIATELY),
									&renderTarget);
	if (res != S_OK) return false;

	return true;
}

void D2DGraphics::clearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}