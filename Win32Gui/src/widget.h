#pragma once

#include <config.h>
#include <layout.h>

class WinObject
{
public:
	WinObject(HWND parent) : mHandle(NULL), mParent(parent){}

	HWND GetHandle() { return mHandle; }
	HWND GetParent() { return mParent; }
	void SetHandle(HWND handle) { mHandle = handle; }
	operator HWND() { return mHandle; }
private:
	HWND mHandle;
	HWND mParent;
};

class Widget : public WinObject
{
public:
	Widget(int width, int height, const std::wstring &title = TEXT("none"), HWND parent = NULL);
	~Widget();

	void Update();
	void CreateClass(HWND parent);
	void CreateWidget(HWND parent);
	/*void SetLayout(Layout* layout);*/
	Layout* GetLayout() { return mLayout.get(); };
protected:
	static LRESULT CALLBACK GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	std::unique_ptr<Layout>		mLayout;
	const wchar_t*				mTitle;
	int							mWidth;
	int							mHeight;
};

