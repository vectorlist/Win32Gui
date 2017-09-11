#pragma once

#include <button.h>

//hold USER type
class CustomButtom : public Button
{
public:
	CustomButtom(HWND parent,int x, int y ,int w, int h)
		: Button(parent, ButtonType::User)
	{
		/*auto rect = GetRect();*/

		Move(x, y, w, h);
		auto rect = GetRect();
		Show();
	}

protected:
	//TODO : image PNG, BMP, JPEG drawing
	virtual void DrawUser(Painter* painter)
	{
		LOG << "working ct button paint" << ENDN;
		Brush b(150, 150, 10);
		painter->SetBrush(b);
		painter->FillRect(GetRect());
	}
};