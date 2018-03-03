#include "application.h"

Application* Application::gApp = NULL;

Application::Application()
	: mInstance(NULL)
{
	gApp = this;
	InitMemoryInstance();
	InitGdiplus();
}

Application::~Application()
{
	ReleaseGdiplus();
}

int Application::InitMemoryInstance()
{
	int result = 0;
	MEMORY_BASIC_INFORMATION memInfo{};
	static int address = 0;

	result = VirtualQuery(&address, &memInfo, sizeof(memInfo));
	if (result == ERROR_INVALID_PARAMETER) {
		MessageBox(NULL, TEXT("failed to find program instance memory address"), TEXT("Fatal"), MB_OK);
		result = 0;
	}

	//mInstance current program instance handle
	mInstance = (HINSTANCE)memInfo.AllocationBase;
	return result;
}

void Application::SetWindowMap(HWND handle, Window *window)
{
	std::map<HWND, Window*, CompareWindow>::const_iterator it;

	it = mWindowMap.find(handle);

	if (it != mWindowMap.end())
	{
		LOG << "has already" << ENDN;
	}
	else {
		LOG << "inssert " << window->GetWindowName() << ENDN;
		mWindowMap.insert(std::make_pair(handle, window));
	}
}

Window* Application::GetWindowFromMap(HWND handle)
{
	std::map<HWND, Window*, CompareWindow>::const_iterator it;

	it = mWindowMap.find(handle);
	if (it != mWindowMap.end()) {
		return it->second;
	}
	return NULL;
}

void Application::RemoveWindowFromMap(HWND handle)
{
	std::map<HWND, Window*, CompareWindow>::iterator it;

	for (it = mWindowMap.begin(); it != mWindowMap.end(); ++it)
	{
		if (handle == it->first) {
			mWindowMap.erase(it);
			break;
		}
	}
}

void Application::InitGdiplus()
{
	Gdiplus::GdiplusStartup(&mGdiplusTokken, &mGdiplusInput, NULL);
}

void Application::ReleaseGdiplus()
{
	Gdiplus::GdiplusShutdown(mGdiplusTokken);
}

int Application::Run()
{
	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.lParam;
}