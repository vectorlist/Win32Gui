#pragma once

struct Margin
{
	Margin(int spacing, int margin) : spacing(spacing), margin(margin) {}
	Margin() : spacing(4), margin(4){}

	int		GetSpacingMultiple() { return spacing * 2; };
	int		GetSpacing() { return spacing; }
	int		GetMarginMultiple() { return margin * 2; };
	int		GetMargin() { return margin; }
	void	SetSpacing(int spacing) { this->spacing = spacing; }
	void	SetMargin(int margin) { this->margin = margin; }
private:
	int spacing;
	int margin;
};

class Layout
{
public:
	Layout(HWND parent);
	virtual~Layout();

	bool CreateLayout(HWND parent = NULL);
	void SetRegisterClass();
	void CreateLayoutWindow(HWND parent);
	void Update();
	
	void AddWindow(HWND handle);
	void SetMargin(const Margin &margin) { mMargin = margin; };
	
	HWND GetHandle() { return mHandle; }
protected:
	virtual wchar_t*	GetLayoutClassName() const { return TEXT("Layout"); }
	virtual void		UpdateRect();

	static LRESULT WINAPI GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	HWND					mHandle;
	HWND					mParent;
	Margin					mMargin;
	std::vector<HWND>		mChilds;
};

class HLayout : public Layout
{
public:
	HLayout(HWND parent = NULL);
	virtual~HLayout();

protected:
	virtual void UpdateRect();
};