#include "DXApp.h"

namespace{//Used for forwarding messages(Close window, minimize, ect)
	//Used to forward messages to user def proc function
	DXApp* g_pApp = nullptr;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){//Forwards messages(Close window, minimize, ect)
	if (g_pApp){
		return g_pApp->MsgProc(hwnd, msg, wParam, lParam);
	}
	else{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

DXApp::DXApp(HINSTANCE hInstance)//Init vars
{
	m_hAppInstance = hInstance;//Handle to win32 app
	m_hAppWnd = NULL;
	//m_ClientWidth = 800;//Width
	//m_ClientHeight = 600;//Height
	m_AppTitle = "DirectX11 App";//App Title
	m_WndStyle = WS_OVERLAPPEDWINDOW;//Window style, includes basic window styles(3 buttons on top, reizable, ect)
	g_pApp = this;

	m_pDevice = nullptr;
	m_pImmediateContext = nullptr;
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;

	dt = 0.0f;
}


DXApp::~DXApp()//Destructor
{
	//Switch to windowed mod
	m_pSwapChain->SetFullscreenState(FALSE, NULL);//switch to windowed mode, input 1 is the mode you want to switch to(FALSE = windowed, TRUE = fullscreen)

	//Cleanup directx
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	Memory::SafeRelease(m_pRenderTargetView);
	Memory::SafeRelease(m_pSwapChain);
	Memory::SafeRelease(m_pImmediateContext);
	Memory::SafeRelease(m_pDevice);

	//Clean up buffers
	Memory::SafeRelease(pVS);
	Memory::SafeRelease(pPS);
}

int DXApp::Run(){//Main loop
	//Main msg loop
	MSG msg = { 0 };//Init empty array?

	while (WM_QUIT != msg.message){//Runs basic app loop while the message to close the app hasnt been called
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)){//Looks at the next message, stores it, deletes it. 
			//^^Unlike getMessage() it doesn't wait for a message(So we can do other things while waiting)
			TranslateMessage(&msg);//Translate to keystrokes
			DispatchMessage(&msg);//Send message to messageProc to be dealt with
		}
		else{
			//Update
			Update(dt);//Updates all game logic, difined in winmain.cpp

			//Render
			Render(dt);//Render, Directx part
		}
	}

	return static_cast<int>(msg.wParam);//I belive this is a way of doing a for loop, if it returns WM_QUIT then the next iteration will quit
}

bool DXApp::Init(){//Init everything, first run
	if (!InitWindow()){//Init win32 window
		return false;//Exit if window isnt created
	}

	if (!InitDirect3D()){//Init Direct X
		return false;//Exit if Direct is properly setup
	}

	if (!InitPipeline()){//Init render pipeline
		return false;//Exit if Render pipeline isn't created correctly
	}

	return true;//If everything goes well then return true
}

bool DXApp::InitWindow(){//Shows win32 window
	//Create window class
	//Below a contructor for a window is created, defines how window is created, a class of a window, a definition of how it is displayed
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = m_hAppInstance;
	wcex.lpfnWndProc = MainWndProc;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	//^^Commented out for full screen mode
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "Hello_DirectX11";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)){//Registers preset for how window should be displayed
		OutputDebugString("\nFailed to create window class\n");//Tells user error
		return false;//If the window display preset cannot be created
	}

	//Adjust height to acomidate top bar
	RECT r = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&r, m_WndStyle, FALSE);
	UINT width = r.right - r.left;
	UINT height = r.bottom - r.top;
	//The inner window area is smaller than the width and height(b/c of the top bar and borders)

	//Center window
	UINT x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	UINT y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

	//Create window will all properties defined above
	m_hAppWnd = CreateWindow(
		"Hello_DirectX11",
		m_AppTitle.c_str(),
		m_WndStyle,
		x,
		y,
		width,
		height,
		NULL,
		NULL,
		m_hAppInstance,
		NULL);
		
	if (!m_hAppWnd){//Checking if pointer to window was made, this most likely means that the window failed to be created
		OutputDebugString("\nFailed to create window\n");//Informs user if pointer to window was not made
		return false;//Exits program if pointer to window was not made
	}

	ShowWindow(m_hAppWnd, SW_SHOW);//Show the window

	return true;//Return true if everything is succefull
}

bool DXApp::InitDirect3D(){//Setup DirectX 3D
	UINT createDeviceFlags = 0;

#ifdef _DEBUG//If debug is on then set special Direct X flag
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	D3D_DRIVER_TYPE driverTypes[] =//Used to tell Direct X exactly how it will be rendering(If you have a graphics card it does it one way, if you dont, another way)
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);//Used later in iterating though driver types

	D3D_FEATURE_LEVEL featureLevels[] =//List of different supported directX versions
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);//User later in iterating though DirectX versions

	DXGI_SWAP_CHAIN_DESC swapDesc;//Setting up buffer
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));//Make space for swapchain desc
	swapDesc.BufferCount = 1;//Double buffer(While 1 frame is being displayed render another) uses array counting where 0 = 1
	swapDesc.BufferDesc.Width = SCREEN_WIDTH;//Set up render width
	swapDesc.BufferDesc.Height = SCREEN_HEIGHT;//Set up render height
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//Set color endcoding(Or something like that)
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;//60 FPS
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;//Minimum FPS
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//Describes what to do w/ buffer, in this case render to window
	swapDesc.OutputWindow = m_hAppWnd;//Where to put the rendered content
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//What to do once a part of a buffer has been used(When the displayed image has been buffered it will detroy it)
	swapDesc.Windowed = true;//Sets render to windowed
	swapDesc.SampleDesc.Count = 1;//Only one multi sampling pass
	swapDesc.SampleDesc.Quality = 0;//Set quallity to 0, or just shutting it off, this is because this feature can slow down rendering
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //allows alt-enter fullscreen

	HRESULT result;//For errors?
	for (UINT i = 0; i < numDriverTypes; i++){//Loops though for each driver type finding the correct one
		result = D3D11CreateDeviceAndSwapChain(
			NULL,
			driverTypes[i],
			NULL, createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&swapDesc,
			&m_pSwapChain,
			&m_pDevice,
			&m_FeatureLevel,
			&m_pImmediateContext);

		if (SUCCEEDED(result)){
			m_DriverType = driverTypes[i];
			break;
		}
	}

	if (FAILED(result)){//If no driver types worked
		OutputDebugString("Failed to create device and swap chain");//Notifies user
		return false;//Exits program
	}

	//Create render target view
	ID3D11Texture2D*	m_pBackBufferTex = 0;//Virtual texture, swap chain displays an image, this is that image?
	HR(m_pSwapChain->GetBuffer(NULL, __uuidof(m_pBackBufferTex), reinterpret_cast<void**>(&m_pBackBufferTex)));//No clue
	HR(m_pDevice->CreateRenderTargetView(m_pBackBufferTex, NULL, &m_pRenderTargetView));//No clue
	Memory::SafeRelease(m_pBackBufferTex);

	//Bind render target view
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);//Make it so swapchain shows on window

	//Viewport creation
	//Create Direct X viewport on window
	m_Viewport.Width = static_cast<float>(SCREEN_WIDTH);//Sets viewport width
	m_Viewport.Height = static_cast<float>(SCREEN_HEIGHT);//Sets viewport height
	m_Viewport.TopLeftX = 0;//Sets viewport to start in left
	m_Viewport.TopLeftY = 0;//Sets viewport to start in top
	m_Viewport.MinDepth = 0.0f;//Min depth
	m_Viewport.MaxDepth = 1.0f;//Max depth

	//Bind viewport
	m_pImmediateContext->RSSetViewports(1, &m_Viewport);//Set viewport to display on win32 window
	return true;//If all succeeds return true
}

bool DXApp::InitPipeline(){//Init the render pipeline

	//Compile Vertex Shader
	HR(D3DCompileFromFile(
		shaderPath,
		nullptr,
		nullptr,
		"VShader",
		"vs_5_0",
		shaderFlags,
		0,
		&VS,
		nullptr
		));

	//Compile Pixel Shader
	HR(D3DCompileFromFile(
		shaderPath,
		nullptr,
		nullptr,
		"PShader",
		"ps_5_0",
		shaderFlags,
		0,
		&PS,
		nullptr
		));
	
	//Encapsulate both shaders in shader objects
	HR(m_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS));
	m_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	//Set the shader objects
	m_pImmediateContext->VSSetShader(pVS, 0, 0);
	m_pImmediateContext->PSSetShader(pPS, 0, 0);

	/*
	//Vertex buffer description
	ZeroMemory(&bd, sizeof(bd));//Reserve memory for Vertex buffer description
	bd.Usage = D3D11_USAGE_DYNAMIC;//Write access, access by CPU and GPU
	//Bellow * 18 secifies amount of veriteces. must use dymaminc buffer to change
	bd.ByteWidth = sizeof(VERTEX) * 18;//Size of vertex struct * 3(x3 b/c x,y,z)
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;//Use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//Allow CPU to write buffer

	m_pDevice->CreateBuffer(&bd, NULL, &pVBuffer);//Create vertex buffer
	*/
	D3D11_INPUT_ELEMENT_DESC ied[] =//Describe to CPU how data is stored
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	m_pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	m_pImmediateContext->IASetInputLayout(pLayout);//Set layout, aply
	
	return true;//Return true on success
}

LRESULT DXApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){//Recieving messages(Input) from os
	switch(msg){
		case WM_DESTROY://If X button is clicked
			PostQuitMessage(0);//But quit message in local q, that way game loop will not run
			return 0;//Exit main function

		default://Do nothing
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
