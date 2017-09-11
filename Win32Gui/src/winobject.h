#pragma once
#include <config.h>

struct CreateSizeInfo
{
	CreateSizeInfo() : x(0),y(0), w(0), h(0){}
	CreateSizeInfo(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
	CreateSizeInfo(const CreateSizeInfo& info) { *this = info; }
	int x, y, w, h;
};

class WinObject
{
public:
	WinObject(HWND parent);
	virtual~WinObject();

	void			Show();
	void			Hide();
	void			SetWindowName(const std::string &name);
	std::wstring	GetWideWindowName() const;
	std::string     GetWindowName() const;
	Rect			GetRect() const;
	Rect			GetWindowRect() const;
	HWND			GetHandle() const;

	void			SetFocus();
	void			SetGeometry(int x, int y, int w, int h);

	int				GetX() const;
	int				GetY() const;
	int				Width() const;
	int				Height() const;

	/*------------------- transform -------------------*/
	void			Move(int x, int y, int w, int h, bool bRepaint = true);
	void			Move(const Point &pos, int w, int h, bool bRepaint = true);
	void			Move(const Point &pos, const Size &size, bool bRepaint = true);
	void			Move(const Rect &rect, bool bRepaint = true);
	void			SetPos(const Point& pos);
	void			SetPos(int w, int h);
	Point			GetPos() const;
	Size			GetSize() const;

	Brush&			GetBrush();
	void			SetBrush(const Brush& brush);

	void			PostWndMessage(UINT msg, WPARAM wp = NULL, LPARAM lp = NULL) const;
	int				SendWndMessage(UINT msg, WPARAM wp = NULL, LPARAM lp = NULL) const;

	void			InvalidateRect(bool bRepaint = TRUE);
	void			InvalidateALL(bool bRepaint = TRUE);

	bool			GetTrackMouseEnable() const;
	void			SetTrackMouseEnable(bool enable);

	void			SetParentWindow(HWND parent);
	
	operator HWND() { return mHandle; }

	virtual bool	IsSplitter();
protected:
	virtual Rect	GetActiveRect();
	HWND			mHandle;
	HWND			mParent;
	
	CreateSizeInfo  mSizeInfo;
private:
	std::string		mWindowName;
	/*Point			mPos;
	Size			mSize;*/
	Brush			mBrush;
	bool			mEnableTrackMouse;
};