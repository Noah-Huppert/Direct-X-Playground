#pragma once
#define WIN32_LEAN_AND_MEAN

#include "DXUtil.h"

#include "Entity.h"
#include "RenderController.h"

//Define screen res
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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


protected://Internal Vars
	//WIN32 Attrs
	HWND			m_hAppWnd;
	HINSTANCE		m_hAppInstance;
	UINT			m_ClientWidth;
	UINT			m_ClientHeight;
	std::string		m_AppTitle;
	DWORD			m_WndStyle;

	//Directx Attr
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pImmediateContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView*	m_pRenderTargetView;
	D3D_DRIVER_TYPE			m_DriverType;
	D3D_FEATURE_LEVEL		m_FeatureLevel;
	D3D11_VIEWPORT			m_Viewport;

	//Pipeline
	WCHAR* shaderPath = L"shaders.hlsl";//Path of shader file
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;//Flags for compiling a shader

	ID3D10Blob *VS = nullptr;//Vertex shader pointer
	ID3D10Blob *PS = nullptr;//Pixel shader pointer
	ID3D11VertexShader *pVS = nullptr;//Vertex shader
	ID3D11PixelShader *pPS = nullptr;//Pixel shader


	ID3D11Buffer *pVBuffer;//Vertex buffer for copying over to graphics card
	D3D11_BUFFER_DESC bd;//Vertex buffer description
	D3D11_MAPPED_SUBRESOURCE ms;//Used to refur to buffer when mapped(Buffer must be mapped in order to work with, when unmapped gpu is allowed to work with it)
	
	ID3D11Buffer* p_dynamicVB;
	D3D11_BUFFER_DESC p_dynamicVBDesc;

	ID3D11InputLayout *pLayout;//Describing layout of vertex struct

	UINT stride;//Size of VERTEX struct
	UINT offset;//Sets the number of bytes into a VERTEX to start rendering

protected://Internal functions
	//Init window
	bool InitWindow();

	//Init Direct3D
	bool InitDirect3D();

	//Init Pipeline
	bool InitPipeline();
};