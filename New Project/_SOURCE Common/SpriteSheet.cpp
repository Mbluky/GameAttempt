#include "../_SOURCE Common/SpriteSheet.h"
#include "../_SOURCE Common/Animations.h"

SpriteSheet::SpriteSheet(wchar_t* fileName, D2DGraphics* graphics, bool facingRight) 
{
	gfx = graphics;
	bmp = NULL;
	bmpFliped = NULL;
	HRESULT hr;
	m_facingRight = facingRight;
	if (facingRight)
	{
		IWICImagingFactory *wicFactory = NULL;
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&wicFactory
		);

		IWICBitmapDecoder* wicDecoder = NULL;

		hr = wicFactory->CreateDecoderFromFilename(
			fileName,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&wicDecoder);

		IWICBitmapFrameDecode* wicFrame = NULL;
		hr = wicDecoder->GetFrame(0, &wicFrame);

		IWICFormatConverter* wicConverter = NULL;
		hr = wicFactory->CreateFormatConverter(&wicConverter);

		hr = wicConverter->Initialize(
			wicFrame,
			GUID_WICPixelFormat32bppPRGBA,
			WICBitmapDitherTypeNone,
			NULL,
			0.0,
			WICBitmapPaletteTypeCustom);

		gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
			wicConverter,
			NULL,
			&bmp);

		if (wicFactory) { wicFactory->Release(); }
		if (wicConverter) { wicConverter->Release(); }
		if (wicFrame) { wicFrame->Release(); }
		if (wicDecoder) { wicDecoder->Release(); }

	}else
	{
		IWICImagingFactory *wicFactory = NULL;

		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&wicFactory
		);

		IWICBitmapDecoder* wicDecoder = NULL;

		hr = wicFactory->CreateDecoderFromFilename(
			fileName,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&wicDecoder);

		IWICBitmapFrameDecode* wicFrame = NULL;
		hr = wicDecoder->GetFrame(0, &wicFrame);

		IWICBitmapFlipRotator* flipRotator = NULL;
		hr = wicFactory->CreateBitmapFlipRotator(&flipRotator);

		hr = flipRotator->Initialize(
			wicFrame,
			WICBitmapTransformFlipHorizontal);
		IWICFormatConverter* wicConverter = NULL;
		hr = wicFactory->CreateFormatConverter(&wicConverter);

		hr = wicConverter->Initialize(
			wicFrame,
			GUID_WICPixelFormat32bppPRGBA,
			WICBitmapDitherTypeNone,
			NULL,
			0.0,
			WICBitmapPaletteTypeCustom);

		gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
			wicConverter,
			NULL,
			&bmpFliped);

		if (wicFactory) { wicFactory->Release(); }
		if (wicConverter) { wicConverter->Release(); }
		if (wicFrame) { wicFrame->Release(); }
		if (wicDecoder) { wicDecoder->Release(); }
	}
}


SpriteSheet::~SpriteSheet()
{
	if (bmp) { bmp->Release(); }
}

void SpriteSheet::Draw( int index, ANIMATION curentAnimation, int x, int y, float scale)
{
	D2D_RECT_F dest = D2D1::RectF(
		x, y,
		x + curentAnimation.spriteSizeX * scale,
		y + curentAnimation.spriteSizeY * scale);

	if (m_facingRight) 
	{
		D2D_RECT_F src = D2D1::RectF(
			(float)(index%curentAnimation.spritesAccross)*curentAnimation.spriteSizeX,
			(float)curentAnimation.startY,
			(float)(index%curentAnimation.spritesAccross)*curentAnimation.spriteSizeX + curentAnimation.spriteSizeX,
			(float)curentAnimation.startY + curentAnimation.spriteSizeY);

		gfx->GetRenderTarget()->DrawBitmap(
			bmp,
			dest,
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			src);
	}
	else 
	{
		D2D_RECT_F src = D2D1::RectF(
			bmpFliped->GetSize().width - ((float)(index%curentAnimation.spritesAccross)*curentAnimation.spriteSizeX),
			(float)curentAnimation.startY,
			bmpFliped->GetSize().width - ((float)(index%curentAnimation.spritesAccross)*curentAnimation.spriteSizeX + curentAnimation.spriteSizeX),
			(float)curentAnimation.startY + curentAnimation.spriteSizeY);

		gfx->GetRenderTarget()->DrawBitmap(
			bmpFliped,
			dest,
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			src);
	}
}