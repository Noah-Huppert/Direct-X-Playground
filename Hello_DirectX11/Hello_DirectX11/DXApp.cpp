#include "DXApp.h"


DXApp::DXApp(HINSTANCE hInstance)
{
	m_hAppInstance = hInstance;
	m_hAppWnd = NULL;
	m_ClientWidth = 800;
	m_ClientHeight = 600
}


DXApp::~DXApp()
{
}
