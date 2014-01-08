#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
class DXApp
{
public:
	DXApp(HINSTANCE hInstance);
	virtual ~DXApp();

	//Main app loop
	int Run();

	//Framework methods
	virtual bool Init();
	virtual void Update(float dt) = 0;//dt = delta time
	virtual void Render(float dt) = 0;//dt = delta time
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


protected:
	//WIN32 Attrs
	HWND			m_hAppWnd;
	HINSTANCE		m_hAppInstance;
	UINT			m_ClientWidth;
	UINT			m_ClientHeight;
	std::string		m_AppTitle;
	DWORD			m_WndStyle;
};

