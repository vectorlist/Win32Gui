#pragma once

namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <ObjIdl.h>
#include <gdiplus.h>
namespace gp = Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

typedef Gdiplus::Pen			GPen;
typedef Gdiplus::Brush			GBrush;
typedef Gdiplus::Color			GColor;
typedef Gdiplus::Point			GPoint;
typedef Gdiplus::PointF			GPointF;
typedef Gdiplus::Bitmap			GBitmap;
typedef Gdiplus::BitmapData		GBitmapDta;
typedef Gdiplus::Graphics		GGraphics;
typedef Gdiplus::GraphicsPath	GGraphicsPath;
typedef Gdiplus::Image			GImage;
typedef Gdiplus::TextureBrush	GTextureBrush;